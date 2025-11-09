#ifndef __APP_H__
#define __APP_H__

#include "main.h"

#include "commond.h"

typedef struct
{
    unsigned char Left;
    unsigned char Right;
    unsigned char Enter;
}KEY_STATE;
extern KEY_STATE Key_State;


void KeyEventCallBack(void);
void VolatgeEventCallBack(void);

#endif /* __APP_H__ */

