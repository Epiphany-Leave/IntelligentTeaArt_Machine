#include "lcd_bsp.h"


#define ST7735_SLPOUT   0x11
#define ST7735_FRMCTR1  0xB1
#define ST7735_FRMCTR2  0xB2
#define ST7735_FRMCTR3  0xB3
#define ST7735_INVCTR   0xB4
#define ST7735_PWCTR1   0xC0
#define ST7735_PWCTR2   0xC1
#define ST7735_PWCTR3   0xC2
#define ST7735_PWCTR4   0xC3
#define ST7735_PWCTR5   0xC4
#define ST7735_VMCTR1   0xC5
#define ST7735_COLMOD   0x3A
#define ST7735_GMCTRP1  0xE0
#define ST7735_GMCTRN1  0xE1
#define ST7735_NORON    0x13
#define ST7735_DISPON   0x29
#define ST7735_CASET    0x2A
#define ST7735_RASET    0x2B
#define ST7735_RAMWR    0x2C
#define ST7735_INVOFF   0x20
#define ST7735_INVON    0x21

#define ST7735_MADCTL     0x36
#define ST7735_MADCTL_MX  0x40
#define ST7735_MADCTL_MY  0x80
#define ST7735_MADCTL_MV  0x20

//管理LCD重要参数
//默认为竖屏
_lcd_dev lcddev;

//画笔颜色,背景颜色
u16 POINT_COLOR = 0x0000,BACK_COLOR = 0xFFFF;  
u16 DeviceCode;	 


///*****************************************************************************
// * @name       :u8 SPI_WriteByte(SPI_TypeDef* SPIx,u8 Byte)
// * @date       :2018-08-09 
// * @function   :Write a byte of data using STM32's hardware SPI
// * @parameters :SPIx: SPI type,x for 1,2,3
//                Byte:Data to be written
// * @retvalue   :Data received by the bus
//******************************************************************************/
////u8 SPI_WriteByte(SPI_TypeDef* SPIx,u8 Byte)
////{
////	while((SPIx->SR&SPI_FLAG_TXE)==RESET);		//等待发送区空	  
////	SPIx->DR=Byte;	 	//发送一个byte   
////	while((SPIx->SR&SPI_FLAG_RXNE)==RESET);//等待接收完一个byte  
////	return SPIx->DR;          	     //返回收到的数据			
////} 
//u8 SPI_WriteByte(SPI_TypeDef* SPIx,u8 Byte)
//{
//	HAL_SPI_Transmit(&hspi1,&Byte,1,10);
//	return SPIx->DR;          	     //返回收到的数据			
//} 


///*****************************************************************************
// * @name       :void SPI_SetSpeed(SPI_TypeDef* SPIx,u8 SpeedSet)
// * @date       :2018-08-09 
// * @function   :Set hardware SPI Speed
// * @parameters :SPIx: SPI type,x for 1,2,3
//                SpeedSet:0-high speed
//												 1-low speed
// * @retvalue   :None
//******************************************************************************/
//void SPI_SetSpeed(SPI_TypeDef* SPIx,u8 SpeedSet)
//{
//	SPIx->CR1&=0XFFC7;
//	if(SpeedSet==1)//高速
//	{
//		SPIx->CR1|=SPI_BAUDRATEPRESCALER_2;//Fsck=Fpclk/2	
//	}
//	else//低速
//	{
//		SPIx->CR1|=SPI_BAUDRATEPRESCALER_32; //Fsck=Fpclk/32
//	}
//	SPIx->CR1|=1<<6; //SPI设备使能
//} 

///*****************************************************************************
// * @name       :void SPI2_Init(void)	
// * @date       :2018-08-09 
// * @function   :Initialize the STM32 hardware SPI2
// * @parameters :None
// * @retvalue   :None
//******************************************************************************/
//void SPI_Init(void)	
//{
//	__HAL_SPI_ENABLE(&hspi1);
//}

/*****************************************************************************
 * @name       :void  SPIv_WriteData(u8 Data)
 * @date       :2018-08-09 
 * @function   :Write a byte of data using STM32's Software SPI
 * @parameters :Data:Data to be written
 * @retvalue   :None
******************************************************************************/
void  SPIv_WriteData(u8 Data)
{
	unsigned char i=0;
	for(i=8;i>0;i--)
	{
	  if(Data&0x80)	
	  SPI_MOSI_SET; //输出数据
      else SPI_MOSI_CLR;
	   
      SPI_SCLK_CLR;       
      SPI_SCLK_SET;
      Data<<=1; 
	}
}

/*****************************************************************************
 * @name       :void LCD_WR_REG(u8 data)
 * @date       :2018-08-09 
 * @function   :Write an 8-bit command to the LCD screen
 * @parameters :data:Command value to be written
 * @retvalue   :None
******************************************************************************/
void LCD_WR_REG(u8 data)
{ 
   LCD_CS_CLR;     
	 LCD_RS_CLR;	  
//   SPI_WriteByte(SPI1,data);
	SPIv_WriteData(data);
   LCD_CS_SET;	
}

/*****************************************************************************
 * @name       :void LCD_WR_DATA(u8 data)
 * @date       :2018-08-09 
 * @function   :Write an 8-bit data to the LCD screen
 * @parameters :data:data value to be written
 * @retvalue   :None
******************************************************************************/
void LCD_WR_DATA(u8 data)
{
   LCD_CS_CLR;
	 LCD_RS_SET;
//   SPI_WriteByte(SPI1,data);
	SPIv_WriteData(data);
   LCD_CS_SET;
}



/*****************************************************************************
 * @name       :void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue)
 * @date       :2018-08-09 
 * @function   :Write data into registers
 * @parameters :LCD_Reg:Register address
                LCD_RegValue:Data to be written
 * @retvalue   :None
******************************************************************************/
void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue)
{	
	LCD_WR_REG(LCD_Reg);  
	LCD_WR_DATA(LCD_RegValue);	    		 
}	   

/*****************************************************************************
 * @name       :void LCD_WriteRAM_Prepare(void)
 * @date       :2018-08-09 
 * @function   :Write GRAM
 * @parameters :None
 * @retvalue   :None
******************************************************************************/	 
void LCD_WriteRAM_Prepare(void)
{
	LCD_WR_REG(lcddev.wramcmd);
}	 

/*****************************************************************************
 * @name       :void Lcd_WriteData_16Bit(u16 Data)
 * @date       :2018-08-09 
 * @function   :Write an 16-bit command to the LCD screen
 * @parameters :Data:Data to be written
 * @retvalue   :None
******************************************************************************/	 
void Lcd_WriteData_16Bit(u16 Data)
{	
   LCD_CS_CLR;
   LCD_RS_SET;  
//   SPI_WriteByte(SPI1,Data>>8);
//	 SPI_WriteByte(SPI1,Data);
	SPIv_WriteData(Data>>8);
	SPIv_WriteData(Data);
   LCD_CS_SET;
}

/*****************************************************************************
 * @name       :void LCD_DrawPoint(u16 x,u16 y)
 * @date       :2018-08-09 
 * @function   :Write a pixel data at a specified location
 * @parameters :x:the x coordinate of the pixel
                y:the y coordinate of the pixel
 * @retvalue   :None
******************************************************************************/	
void LCD_DrawPoint(u16 x,u16 y)
{
	LCD_SetCursor(x,y);//设置光标位置 
	Lcd_WriteData_16Bit(POINT_COLOR); 
}

/*****************************************************************************
 * @name       :void LCD_Clear(u16 Color)
 * @date       :2018-08-09 
 * @function   :Full screen filled LCD screen
 * @parameters :color:Filled color
 * @retvalue   :None
******************************************************************************/	
void LCD_Clear(u16 Color)
{
  unsigned int i,m;  
	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);   
	LCD_CS_CLR;
	LCD_RS_SET;
	for(i=0;i<lcddev.height;i++)
	{
    for(m=0;m<lcddev.width;m++)
    {	
			Lcd_WriteData_16Bit(Color);
		}
	}
	 LCD_CS_SET;
} 



/*****************************************************************************
 * @name       :void LCD_RESET(void)
 * @date       :2018-08-09 
 * @function   :Reset LCD screen
 * @parameters :None
 * @retvalue   :None
******************************************************************************/	
void LCD_RESET(void)
{
	LCD_RST_CLR;
	HAL_Delay(100);	
	LCD_RST_SET;
	HAL_Delay(50);
}

/*****************************************************************************
 * @name       :void LCD_Init(void)
 * @date       :2018-08-09 
 * @function   :Initialization LCD screen
 * @parameters :None
 * @retvalue   :None
******************************************************************************/	 	 
void LCD_Init(void)
{  
//	SPI_Init();
	//LCD GPIO初始化	
 	LCD_RESET(); //LCD 复位
//************* ST7735S初始化**********//	
	LCD_WR_REG(ST7735_SLPOUT);
	HAL_Delay(120);
	LCD_WR_REG(ST7735_FRMCTR1);
	LCD_WR_DATA(0x01);
	LCD_WR_DATA(0x2C);
	LCD_WR_DATA(0x2D);
	LCD_WR_REG(ST7735_FRMCTR2);
	LCD_WR_DATA(0x01);
	LCD_WR_DATA(0x2C);
	LCD_WR_DATA(0x2D);
	LCD_WR_REG(ST7735_FRMCTR3);
	LCD_WR_DATA(0x01);
	LCD_WR_DATA(0x2C);
	LCD_WR_DATA(0x2D);
	LCD_WR_DATA(0x01);
	LCD_WR_DATA(0x2C);
	LCD_WR_DATA(0x2D);
	LCD_WR_REG(ST7735_INVCTR);
	LCD_WR_DATA(0x07);
	LCD_WR_REG(ST7735_PWCTR1);
	LCD_WR_DATA(0xA2);
	LCD_WR_DATA(0x02);
	LCD_WR_DATA(0x84);
	LCD_WR_REG(ST7735_PWCTR2);
	LCD_WR_DATA(0xC5);
	LCD_WR_REG(ST7735_PWCTR3);
	LCD_WR_DATA(0x0A);
	LCD_WR_DATA(0x00);
	LCD_WR_REG(ST7735_PWCTR4);
	LCD_WR_DATA(0x8A);
	LCD_WR_DATA(0x2A);
	LCD_WR_REG(ST7735_PWCTR5);
	LCD_WR_DATA(0x8A);
	LCD_WR_DATA(0xEE);
	LCD_WR_REG(ST7735_VMCTR1);
	LCD_WR_DATA(0x0E);
	LCD_WR_REG(ST7735_INVERSE ? ST7735_INVON : ST7735_INVOFF);
	LCD_WR_REG(ST7735_COLMOD);
	LCD_WR_DATA(0x05);
	LCD_WR_REG(ST7735_CASET);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x7F);
	LCD_WR_REG(ST7735_RASET);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x9F);
	LCD_WR_REG(ST7735_GMCTRP1);
	LCD_WR_DATA(0x02);
	LCD_WR_DATA(0x1C);
	LCD_WR_DATA(0x07);
	LCD_WR_DATA(0x12);
	LCD_WR_DATA(0x37);
	LCD_WR_DATA(0x32);
	LCD_WR_DATA(0x29);
	LCD_WR_DATA(0x2D);
	LCD_WR_DATA(0x29);
	LCD_WR_DATA(0x25);
	LCD_WR_DATA(0x2B);
	LCD_WR_DATA(0x39);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x01);
	LCD_WR_DATA(0x03);
	LCD_WR_DATA(0x10);
	LCD_WR_REG(ST7735_GMCTRN1);
	LCD_WR_DATA(0x03);
	LCD_WR_DATA(0x1D);
	LCD_WR_DATA(0x07);
	LCD_WR_DATA(0x06);
	LCD_WR_DATA(0x2E);
	LCD_WR_DATA(0x2C);
	LCD_WR_DATA(0x29);
	LCD_WR_DATA(0x2D);
	LCD_WR_DATA(0x2E);
	LCD_WR_DATA(0x2E);
	LCD_WR_DATA(0x37);
	LCD_WR_DATA(0x3F);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x02);
	LCD_WR_DATA(0x10);
	LCD_WR_REG(ST7735_NORON);
	HAL_Delay(10);
	LCD_WR_REG(ST7735_DISPON);
	HAL_Delay(10);
	
	LCD_WR_REG(0x3A); //65k mode 
	LCD_WR_DATA(0x05); 
	LCD_WR_REG(0x29);//Display on
	
	LCD_direction(USE_HORIZONTAL);//设置LCD显示方向
	LCD_LED;//点亮背光	 
	LCD_Clear(WHITE);//清全屏白色
}
 
/*****************************************************************************
 * @name       :void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd)
 * @date       :2018-08-09 
 * @function   :Setting LCD display window
 * @parameters :xStar:the bebinning x coordinate of the LCD display window
								yStar:the bebinning y coordinate of the LCD display window
								xEnd:the endning x coordinate of the LCD display window
								yEnd:the endning y coordinate of the LCD display window
 * @retvalue   :None
******************************************************************************/ 
void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd)
{	
	LCD_WR_REG(lcddev.setxcmd);	
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(xStar);		
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(xEnd);

	LCD_WR_REG(lcddev.setycmd);	
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(yStar);		
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(yEnd);

	LCD_WriteRAM_Prepare();	//开始写入GRAM			
}   

/*****************************************************************************
 * @name       :void LCD_SetCursor(u16 Xpos, u16 Ypos)
 * @date       :2018-08-09 
 * @function   :Set coordinate value
 * @parameters :Xpos:the  x coordinate of the pixel
								Ypos:the  y coordinate of the pixel
 * @retvalue   :None
******************************************************************************/ 
void LCD_SetCursor(u16 Xpos, u16 Ypos)
{	  	    			
	LCD_SetWindows(Xpos,Ypos,Xpos,Ypos);	
} 

/*****************************************************************************
 * @name       :void LCD_direction(u8 direction)
 * @date       :2018-08-09 
 * @function   :Setting the display direction of LCD screen
 * @parameters :direction:0-0 degree
                          1-90 degree
													2-180 degree
													3-270 degree
 * @retvalue   :None
******************************************************************************/ 
void LCD_direction(u8 direction)
{ 
			lcddev.setxcmd=0x2A;
			lcddev.setycmd=0x2B;
			lcddev.wramcmd=0x2C;
	switch(direction){		  
		case 0:						 	 		
			lcddev.width=LCD_W;
			lcddev.height=LCD_H;		
			LCD_WriteReg(0x36,(0<<3)|(1<<6)|(1<<7));//BGR==1,MY==0,MX==0,MV==0
		break;
		case 1:
			lcddev.width=LCD_H;
			lcddev.height=LCD_W;
			LCD_WriteReg(0x36,(0<<3)|(1<<7)|(1<<5));//BGR==1,MY==1,MX==0,MV==1
		break;
		case 2:						 	 		
			lcddev.width=LCD_W;
			lcddev.height=LCD_H;	
			LCD_WriteReg(0x36,(0<<3)|(0<<6)|(0<<7));//BGR==1,MY==0,MX==0,MV==0
		break;
		case 3:
			lcddev.width=LCD_H;
			lcddev.height=LCD_W;
			LCD_WriteReg(0x36,(0<<3)|(0<<7)|(1<<6)|(1<<5));//BGR==1,MY==1,MX==0,MV==1
		break;	
		default:break;
	}		
}








