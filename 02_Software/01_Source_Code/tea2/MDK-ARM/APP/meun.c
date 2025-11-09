#include "meun.h"
#include "pic.h"

unsigned char meun_num;
MEUN_TABLE table[5] = {
    //首页
    {0, 0, 1, (*my_testA0)},

    //第一层
    {1, 2, 0, (*my_testB1)},
    {2, 3, 0, (*my_testB2)},
    {3, 4, 0, (*my_testB3)},
    {4, 1, 0, (*my_testB4)},   
	
	//第二层
};
void (*current_operation_index)();

void Meun_Init(void) 
{
    LCD_Init();
    LCD_Fill(0, 0, lcddev.width, lcddev.height, WHITE);
	meun_num = 1;
}

static int task_now = 0;  
static unsigned char last_meun = 0;

static unsigned char func_index = 0;
static unsigned char last_index = 4;
void LCD_PLAY(void) 
{
    if(Key_State.Right == 1)
    {
        func_index = table[func_index].down;
        Key_State.Right = 0;
    }
    if(Key_State.Left == 1)
    {
		LCD_Clear(WHITE);
        func_index = table[func_index].enter;
        Key_State.Left = 0;
    }
    if(func_index != last_index)
    {
        current_operation_index = table[func_index].current_opereation;
        (*current_operation_index)();
        last_index = func_index;
    }
}

void LCD_TASK_SETNOW(int task_num) 
{
     task_now = task_num;  
}
