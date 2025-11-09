#ifndef __FILE_H_
#define __FILE_H_

#include "main.h"

#define FILTER_WINDOW_SIZE 8  // 滑动窗口大小（建议5-10）

void init_sliding_window(void);
uint16_t sliding_filter(int ch, uint16_t new_value);

#endif /* __FILE_H_ */
