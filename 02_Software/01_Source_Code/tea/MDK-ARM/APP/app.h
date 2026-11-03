#ifndef __APP_H__
#define __APP_H__

#include "main.h"

#include "commond.h"

void bcfsm(void);


void Preheat_Control(void);
void Maketea_Control(void) ;
void Clean_Control(void);
void Addtea_Control(void);

typedef struct
{
    unsigned char Left;
    unsigned char Right;
    unsigned char Enter;
}KEY_STATE;
extern KEY_STATE Key_State;

void Protocol_parsing(void);
void KeyEventCallBack(void);
void VolatgeEventCallBack(void);

#endif /* __APP_H__ */

