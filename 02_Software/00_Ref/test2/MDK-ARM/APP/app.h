#include "servo.h"
#include "water.h"
#include "lcd.h"
#include "main.h"
#include "motor.h"
#include "stepper_motor.h"

#include "interrupt.h"

#define MENU_TITLE_MAX_SIZE 30
#define MENU_LABEL_MAX_SIZE	10
#define MENU_LEVEL_NUM 10

typedef struct
{
	unsigned char current;
	unsigned char up;//向上翻索引号
	unsigned char down;//向下翻索引号
	unsigned char enter;//确认索引号
	void (*current_operation)();
} LCD_TABLE;


