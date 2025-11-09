#ifndef __BEEP_BSP_H__
#define __BEEP_BSP_H__

#include "main.h"

typedef enum
{
    silent=0,
    mode1=1,
    mode2,
    mode3
}beep_mode;

typedef struct
{
    uint16_t freq; // 音符频率（Hz）
    uint16_t duration; // 持续时间（单位：50ms）
} beep_note;

typedef struct
{
	beep_mode mode;
	uint16_t num;
    uint16_t length;          // 音符序列长度
    uint16_t index;           // 当前音符索引
    uint16_t time;            // 当前音符的计时
} beep_struct;

extern uint8_t beep_volume;
extern beep_struct beep;

void beep_SetFreq(uint16_t freq);
void beep_off(void);
void beep_on(beep_mode mode);  //可选 mode1/mode2/mode3
void beep_run(void);                //把这个函数扔到50毫秒的延时函数里面，就可以响

#endif /* __BEEP_BSP_H_ */ 
