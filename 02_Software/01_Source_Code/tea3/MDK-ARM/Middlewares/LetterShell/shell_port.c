#include "shell_port.h"
#include "main.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "usart.h"

Shell shell;
uint8_t shellByteBuff;
char shellBuffer[512] = { 0 };

/**
 * @brief 用户shell写
 * 
 * @param data 数据
 * @param len 数据长度
 * 
 * @return short 实际写入的数据长度
 */
short userShellWrite(char* data, unsigned short len)
{
    HAL_UART_Transmit(&huart1, (uint8_t *)data, len, 0x1FF);
	return len;
}

/**
 * @brief 用户shell读
 * 
 * @param data 数据
 * @param len 数据长度
 * 
 * @return short 实际读取到
 */
short userShellRead(char *data, unsigned short len)
{
    if(HAL_UART_Receive(&huart1, (uint8_t *)data, len, 0x1FF) != HAL_OK)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

void LetterShell_Init(void)
{
    shell.write = userShellWrite;
	shell.read = userShellRead;
    shellInit(&shell, shellBuffer, 512);
}


/////////////  Shell User  ///////////
SHELL_EXPORT_USER(SHELL_CMD_TYPE(SHELL_TYPE_USER) | SHELL_CMD_PERMISSION(1), Tourist, "", Tourist);
/////////////  Shell Func  ///////////
/**
***********************************************************************
* @brief:      
* @details:    测试Shell
***********************************************************************
**/
int func(int i, char ch, char *str)//命令
{
    printf("input int: %d, char: %c, string: %s\r\n", i, ch, str);
}
int testVar = 256;//变量

uint8_t stateReset(int argc, char* argv[])
{
    
    return 0;
}

//uint8_t flashLoaderMode(int argc, char* argv[])
//{

//    return 0;
//}

//uint8_t screen(int argc, char* argv[])
//{

//    return 0;
//}

//uint8_t set(int argc, char* argv[])
//{

//    return 0;
//}

//uint8_t get(int argc, char* argv[])
//{

//    return 0;
//}

////////////////////////////////   Test测试   //////////////////////////////
//权限+形式（函数/变量。。）+命令名称+函数名/变量名+描述
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC), func, func, this is a c like function);//命令测试
SHELL_EXPORT_VAR(SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_VAR_INT), testVar, &testVar, var for test);//变量测试

////////////////////////////////   软件复位   //////////////////////////////
//SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_MAIN), stateReset, stateReset, reset state machine.);

////////////////////////////////   Flash写入模式   //////////////////////////////
//SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_MAIN), flashLoaderMode, flashLoaderMode, load data into flash.);

////////////////////////////////   模式/参数调节   //////////////////////////////
//SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_MAIN),set,set
//    ,Set target parameters:\r\n
//    gp/i/d for gpsP/I/D\r\n
//    stt for AutoControl_StrightTurnThre\r\n
//    gpser for AutoControl_EqualRange\r\n
//    gpssi for GPS_SAMPLING_Interval\r\n
//    spd for car speed);

//SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_MAIN), screen, screen, Control screen
//                 :\r\n
//                     on to open\r\n
//                         off to close);

////////////////////////////////   获取当前参数   //////////////////////////////
//SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_MAIN),get,get
//    ,Get target parameters:\r\n
//    gps for gpsPID\r\n
//    spd for car speed\r\n
//    all for all para\r\n);
