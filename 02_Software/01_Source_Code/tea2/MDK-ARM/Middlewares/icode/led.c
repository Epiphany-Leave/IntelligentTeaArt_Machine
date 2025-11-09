#include "led.h"

/* 命令回调函数 */
typedef void (*cmd_cb)(char*);

/* 命令结构体 */
typedef struct
{
	char* cmd;	// 接收到的命令
	cmd_cb cb;	// 对应命令的回调函数
}ST_CMD;

// 先把下面的函数先声明下
void help_proc(char* str);
void led_proc(char* str);

/* 命令列表 */
ST_CMD cmd_list[] = 
{
	{"?",	help_proc},
	{"led",	led_proc},
};


/* ===================================================== */
// 描述："?"命令的回调函数，打印所有的命令。
// 参数：
// 返回值：
/* ===================================================== */
void help_proc(char* str)
{
	int i, size = sizeof(cmd_list)/sizeof(ST_CMD);
	
	printf("this is helper~\r\n");
	for(i = 0; i < size; i++)
	{
		printf("%s \r\n", cmd_list[i].cmd);
	}
}

/* ===================================================== */
// 描述："led"命令的回调函数，打印所有的命令。
// 参数：
// 返回值：
/* ===================================================== */
void led_proc(char* str)
{
	if(strstr(str, "-h"))
	{
		printf("you can use [on/off] ctrl led \r\n");
		return;
	}
	if(strstr(str, "on"))
	{
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
		return;
	}
	if(strstr(str, "off"))
	{
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
		return;
	}
	if(strstr(str, "blink"))
	{
		int count, ret;
		ret = sscanf(str, "blink %d", &count);
		if(ret == 1)
		{
			printf("led begin blink %d time \r\n", count);
			for(int i = 0; i < count*2; i++)
			{
				HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
				HAL_Delay(100);
			}
		}
	}
}

/* 接收数据的二级缓冲 */
uint8_t debug_rev_buf[64];	// 存放数据
uint8_t rev_cnt = 0;		// 数据计数

/* ===================================================== */
// 描述：寻找字符串中非空格数据的位置
// 参数：
// 返回值：
/* ===================================================== */
char *skip(char *buf)
{
	while(*buf == ' ')
	{
		buf++;
	}
	return buf;
}

/* ===================================================== */
// 描述：处理函数，对比接收到的命令是否在命令列表中，并执行。
// 参数：接收到的命令
// 返回值：
/* ===================================================== */
void debug_cmd_proc(char* buf)
{
	int i, size = sizeof(cmd_list)/sizeof(ST_CMD);
	
	for(i = 0; i < size; i++)
	{
		// cmd列表中命令的长度
		int len = strlen(cmd_list[i].cmd);
		
		if(strncmp(buf, cmd_list[i].cmd, len) == 0)
		{
			char *s = skip(buf + len);
			// 传入的参数是：接收到的命令去掉了前面的cmd命令后
			// 第一个不是空格的字符开始，一直到结束
			cmd_list[i].cb(s);
		}
	}
}

/* ===================================================== */
// 描述：把接收到的字符放入二级缓存，如果接收到换行就执行处理函数;
// 参数：ch：接收到的字符
// 返回值：
/* ===================================================== */
void at_proc(uint8_t ch)
{
	if(ch > 0x7e)	// 可显示字符的范围是: 0x20 < ch < 0x7e
	{
		return;
	}
	if(ch < 0x20)	// 换行是 0d 0a，这里认为小于0x20的都是回车换行
	{
		if(rev_cnt)
		{
			// 对比命令并执行
			debug_cmd_proc((char*)debug_rev_buf);
			// 重置二级缓存
			rev_cnt = 0;
			memset(debug_rev_buf, 0, 64);
		}
	}
	else
	{
		// 存入二级缓存
		debug_rev_buf[rev_cnt] = ch;
		rev_cnt++;
	}
	if(rev_cnt >= 64)	// 溢出、清空数据
	{
		rev_cnt = 0;
		memset(debug_rev_buf, 0, 64);
	}
}


