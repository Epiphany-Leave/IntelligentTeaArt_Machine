#include "file.h"
#include "string.h"

// 滑动窗口结构体
typedef struct {
    float history[FILTER_WINDOW_SIZE]; // 历史数据窗口
    uint8_t index;                    // 当前写入位置
    float sum;                        // 窗口数据总和
} SlidingWindow;

SlidingWindow adc_window[AXIS_NUMBER]; // 每个通道独立窗口

// 初始化滑动窗口
void init_sliding_window(void) 
{
    for(int ch=0; ch<AXIS_NUMBER; ch++)
	{
        memset(adc_window[ch].history, 0, sizeof(adc_window[ch].history));
        adc_window[ch].index = 0;
        adc_window[ch].sum = 0;
    }
}

// 滑动均值滤波计算
uint16_t sliding_filter(int ch, uint16_t new_value) 
{
    SlidingWindow* win = &adc_window[ch];
    
    // 减去即将被替换的旧值
    win->sum -= win->history[win->index];
    
    // 存入新值并更新总和
    win->history[win->index] = new_value;
    win->sum += new_value;
    
    // 更新索引（环形缓冲区）
    win->index = (win->index + 1) % FILTER_WINDOW_SIZE;
    
    return win->sum / FILTER_WINDOW_SIZE;
}

