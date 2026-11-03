#ifndef __MEUN_H__
#define __MEUN_H__

#include "commond.h"
    
typedef struct
{
    unsigned char current;
    unsigned char down;
    unsigned char enter;
    void (*current_opereation)();
}MEUN_TABLE;

extern unsigned char meun_num;

/*记得将SPI的DMA优先级拉高，要不然会卡死*/

/*lcd初始化函数*/
void Meun_Init(void);


/*放在主循环中，自行修改*/
void LCD_PLAY(void);

/*调用此函数，修改LCD闪烁任务1-6，输入0停止闪烁*/
void LCD_TASK_SETNOW(int task_num );


#endif /* __MEUN_H__ */

