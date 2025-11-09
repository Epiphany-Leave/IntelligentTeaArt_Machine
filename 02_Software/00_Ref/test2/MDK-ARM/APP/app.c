#include "app.h"

static void fun_a1();
static void fun_b1();
static void fun_c1();
static void fun_d1();
static void fun_a21();

/* LCD多级菜单 */
LCD_TABLE table[30]=
{
	//第0层
//	{0,0,0,1,(*fun_0)},
	
    //第1层
	{1,4,2, 5,(*fun_a1)},
	{2,1,3, 9,(*fun_b1)},
	{3,2,4,13,(*fun_c1)},		
	{4,3,1, 0,(*fun_d1)},
	
    //第2层
	{5,8,6,17,(*fun_a21)},					
//	{6,5,7,18,(*fun_a22)},
//	{7,6,8,19,(*fun_a23)},						                	
//	{8,7,5, 1,(*fun_a24)},
//	
//	{ 9,12,10,20,(*fun_b21)},					
//	{10, 9,11,21,(*fun_b22)},
//	{11,10,12,22,(*fun_b23)},						                	
//	{12,11, 9, 2,(*fun_b24)},
//	
//	{13,16,14,23,(*fun_c21)},					
//	{14,13,15,24,(*fun_c22)},				                	
//	{15,14,16,25,(*fun_c23)},				                	
//	{16,15,13, 3,(*fun_c24)},
//	
//    //第3层
//	{17,17,17,5,(*fun_a31)},			                	
//	{18,18,18,6,(*fun_a32)},		                	
//	{19,19,19,7,(*fun_a33)},
//	
//	{20,20,20, 9,(*fun_b31)},				                	
//	{21,21,21,10,(*fun_b32)},			                	
//	{22,22,22,11,(*fun_b33)},
//	
//	{23,23,23,13,(*fun_c31)},			                	
//	{24,24,24,14,(*fun_c32)},			                	
//	{25,25,25,15,(*fun_c33)},								
};

/*********第1层***********/
static void fun_a1()   
{	
	LCD_ShowString(0,16,">", LBBLUE, LGRAYBLUE, 16, 0);
	LCD_ShowString(16,16,"[1]Weather", LBBLUE, LGRAYBLUE, 16, 0);
	LCD_ShowString(16,32,"[2]Music", LBBLUE, LGRAYBLUE, 16, 0);
	LCD_ShowString(16,48,"[3]Device Info", LBBLUE, LGRAYBLUE, 16, 0);
	LCD_ShowString(16,64,"<--", LBBLUE, LGRAYBLUE, 16, 0);																					
}

static void fun_b1()
{	
	LCD_ShowString(0,32,">", LBBLUE, LGRAYBLUE, 16, 0);
	LCD_ShowString(16,16,"[1]Weather", LBBLUE, LGRAYBLUE, 16, 0);
	LCD_ShowString(16,32,"[2]Music", LBBLUE, LGRAYBLUE, 16, 0);
	LCD_ShowString(16,48,"[3]Device Info", LBBLUE, LGRAYBLUE, 16, 0);
	LCD_ShowString(16,64,"<--", LBBLUE, LGRAYBLUE, 16, 0);																						
}

static void fun_c1()
{	
	LCD_ShowString(0,48,">", LBBLUE, LGRAYBLUE, 16, 0);
	LCD_ShowString(16,16,"[1]Weather", LBBLUE, LGRAYBLUE, 16, 0);
	LCD_ShowString(16,32,"[2]Music", LBBLUE, LGRAYBLUE, 16, 0);
	LCD_ShowString(16,48,"[3]Device Info", LBBLUE, LGRAYBLUE, 16, 0);
	LCD_ShowString(16,64,"<--", LBBLUE, LGRAYBLUE, 16, 0);																					
}

static void fun_d1()
{	
	LCD_ShowString(0,64,">", LBBLUE, LGRAYBLUE, 16, 0);
	LCD_ShowString(16,16,"[1]Weather", LBBLUE, LGRAYBLUE, 16, 0);
	LCD_ShowString(16,32,"[2]Music", LBBLUE, LGRAYBLUE, 16, 0);
	LCD_ShowString(16,48,"[3]Device Info", LBBLUE, LGRAYBLUE, 16, 0);
	LCD_ShowString(16,64,"<--", LBBLUE, LGRAYBLUE, 16, 0);																							
}

/*********第2层*****/
static void fun_a21()
{	
	LCD_ShowString(0,16,">", LBBLUE, LGRAYBLUE, 16, 0);
	LCD_ShowString(16,16,"* HangZhou", LBBLUE, LGRAYBLUE, 16, 0);
	LCD_ShowString(16,32,"* BeiJing", LBBLUE, LGRAYBLUE, 16, 0);
	LCD_ShowString(16,48,"* ShangHai", LBBLUE, LGRAYBLUE, 16, 0);
	LCD_ShowString(16,64,"<--", LBBLUE, LGRAYBLUE, 16, 0);																						
}



