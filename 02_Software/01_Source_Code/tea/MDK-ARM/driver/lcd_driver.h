#ifndef __LCD_DRIVER_H
#define __LCD_DRIVER_H		

#include "main.h"

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t

// 在指定位置绘制一个点
// 参数: x, y - 点的坐标；color - 点的颜色
void GUI_DrawPoint(u16 x, u16 y, u16 color);

// 用指定颜色填充一个矩形区域
// 参数: sx, sy - 矩形左上角坐标；ex, ey - 矩形右下角坐标；color - 填充颜色
void LCD_Fill(u16 sx, u16 sy, u16 ex, u16 ey, u16 color);

// 绘制一条直线
// 参数: x1, y1 - 起点坐标；x2, y2 - 终点坐标
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);

// 绘制一个矩形
// 参数: x1, y1 - 矩形左上角坐标；x2, y2 - 矩形右下角坐标
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);

// 绘制一个圆
// 参数: x0, y0 - 圆心坐标；fc - 圆的颜色；r - 圆的半径
void Draw_Circle(u16 x0, u16 y0, u16 fc, u8 r);

// 绘制一个三角形
// 参数: x0, y0; x1, y1; x2, y2 - 三角形的三个顶点坐标
void Draw_Triangel(u16 x0, u16 y0, u16 x1, u16 y1, u16 x2, u16 y2);

// 填充一个三角形
// 参数: x0, y0; x1, y1; x2, y2 - 三角形的三个顶点坐标
void Fill_Triangel(u16 x0, u16 y0, u16 x1, u16 y1, u16 x2, u16 y2);

// 显示一个字符
// 参数: x, y - 字符显示位置；fc - 字符颜色；bc - 背景颜色；num - 显示的字符；
//       size - 字符大小；mode - 模式(0:非叠加, 1:叠加)
void LCD_ShowChar(u16 x, u16 y, u16 fc, u16 bc, u8 num, u8 size, u8 mode);

// 显示一个数字
// 参数: x, y - 数字显示位置；num - 要显示的数字；len - 数字位数；size - 字体大小
void LCD_ShowNum(u16 x, u16 y, u32 num, u8 len, u8 size);

// 显示两位数字
// 参数: x, y - 数字显示位置；num - 要显示的两位数字；len - 位数；size - 字体大小；mode - 模式
void LCD_Show2Num(u16 x, u16 y, u16 num, u8 len, u8 size, u8 mode);

// 显示一个字符串
// 参数: x, y - 字符串显示位置；size - 字体大小；p - 字符串指针；mode - 模式
void LCD_ShowString(u16 x, u16 y, u8 size, u8 *p, u8 mode);

// 显示16号字体的文本
// 参数: x, y - 文本显示位置；fc - 字体颜色；bc - 背景颜色；s - 文本字符串；mode - 模式
void GUI_DrawFont16(u16 x, u16 y, u16 fc, u16 bc, u8 *s, u8 mode);

// 显示24号字体的文本
void GUI_DrawFont24(u16 x, u16 y, u16 fc, u16 bc, u8 *s, u8 mode);

// 显示32号字体的文本
void GUI_DrawFont32(u16 x, u16 y, u16 fc, u16 bc, u8 *s, u8 mode);

// 显示字符串
// 参数: x, y - 字符串显示位置；fc - 字体颜色；bc - 背景颜色；str - 字符串；
//       size - 字体大小；mode - 模式
void Show_Str(u16 x, u16 y, u16 fc, u16 bc, u8 *str, u8 size, u8 mode);

// 显示16位色图片
// 参数: x, y - 图片显示起点坐标；p - 图片数据指针
void Gui_Drawbmp16(u16 x, u16 y, const unsigned char *p);
void Gui_Drawbmp16_Flexible(u16 x, u16 y, const unsigned char *p, u16 width, u16 height);

// 绘制一个圆(支持填充)
// 参数: xc, yc - 圆心坐标；c - 圆的颜色；r - 半径；fill - 是否填充(1:填充, 0:不填充)
void gui_circle(int xc, int yc, u16 c, int r, int fill);

// 居中显示字符串
// 参数: x, y - 中心位置；fc - 字体颜色；bc - 背景颜色；str - 字符串；
//       size - 字体大小；mode - 模式
void Gui_StrCenter(u16 x, u16 y, u16 fc, u16 bc, u8 *str, u8 size, u8 mode);

// 填充矩形区域
// 参数: x1, y1 - 矩形左上角坐标；x2, y2 - 矩形右下角坐标
void LCD_DrawFillRectangle(u16 x1, u16 y1, u16 x2, u16 y2);



/* 测试代码 */
void DrawTestPage(u8 *str);
void Test_Color(void);
void Test_FillRec(void);
void Test_Circle(void);
void Test_Triangle(void);
void English_Font_test(void);
void Chinese_Font_test(void);
void Pic_test(void);
void Load_Drow_Dialog(void);
void Touch_Test(void);
void lcd_main_test(void);
void Rotate_Test(void);
/* 时间记录 */
void test_time(void);

/*********************** 界面显示代码 ********************************/
void my_testA0(void);
void my_testB1(void);
void my_testB2(void);
void my_testB3(void);
void my_testB4(void);


#endif	/* __LCD_DRIVER_H */





