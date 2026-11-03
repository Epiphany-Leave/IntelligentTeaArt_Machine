#ifndef _BEEP_H__
#define _BEEP_H__

#include "main.h"

enum beep_mode
{
    silent=0,
    mode1=1,
    mode2,
    mode3
};

typedef struct
{
    enum beep_mode mode;
    uint8_t num;
    uint8_t time;
    
}beep_struct;

extern uint8_t beep_volume;
extern beep_struct beep;

void beep_SetFreq(uint16_t freq);
void beep_off(void);
void beep_on(enum beep_mode mode);  //可选 mode1/mode2/mode3
void beep_run(void);                //把这个函数扔到50毫秒的延时函数里面，就可以响
#endif 
