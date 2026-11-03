#include "app.h"

KEY_STATE Key_State;

__IO uint16_t result[1] = {0};
CCMRAM __IO float Vout = 0;  //输入电压


/********************************************************
函数名：  	bcfsm
日期：    	
功能：   	主循环状态机 	
输入参数：
返回值： 		
修改记录：
**********************************************************/
typedef enum
{
    Task_0_Initial_state, //初始状态
    Task_1_Get_HMI, 	  //检测串口屏协议
    Task_2_WIFI,      	  //检测WIFI
    Task_3_judgment,      //任务判断
    Task_4_Soft_start     //开始缓启动
} System_Task;

CCMRAM System_Task Current_State,Next_State;

CCMRAM void bcfsm(void)  //CCMRAM把函数放进CCRAM内存，加速执行速度
{
    Next_State=Current_State=Task_0_Initial_state;
    while(1)
    {
		// shellTask(&shell);

        Current_State=Next_State;
        switch(Current_State)
        {
        case Task_0_Initial_state:
        {
			beep_on(mode1);	//蜂鸣器提示
            Next_State=Task_1_Get_HMI;		 //下一状态：检测串口屏协议
        }
        break;
        case Task_1_Get_HMI ://检测串口屏协议
        {
			Protocol_parsing();	//解析串口屏协议
            Next_State=Task_2_WIFI;  //等待数据更新
        }
        break;
        case Task_2_WIFI://检测WIFI
        {
			if(wireless_send_flag == 1) 		//数据上报标志位
			{
				wireless_send_flag = 0;
				wireless_system_handler();		//执行无线模块相关事件
				wireless_onenet_data_handler();	//处理有关onenet的数据
				if((WirelessStatus.error_code & ERROR_MQTT_CONNECT) == 0)  wireless_publish_data(); 	//发布数据测试
			}
			if(wireless_get_receive_flag() == W_OK)		//无线模块接收到数据
			{
				wireless_receive_data_handler();		//接收数据处理函数
			}
			Next_State=Task_3_judgment;					//下一状态：任务判断
        }
        break;
        case Task_3_judgment : //任务判断
        {
			if(preheat_flag == 1)
			{
//				Preheat_Control();
			}
			else if(maketea_flag == 1)
			{
//				Maketea_Control();
			}
			else if(clean_flag == 1)
			{
//				Clean_Control();
			}
			else if(preheat_flag == 0 && maketea_flag == 0 && clean_flag == 0)
			{
				Next_State=Task_1_Get_HMI;
			}
        }
        break;
        case Task_4_Soft_start ://缓启动
        {
			
        }
        break;
        default:
            break;
        }
    }
}

// 定义任务类型枚举
typedef enum {
    ACTION_SERVO_INSTANT,    // 立即设置舵机角度
    ACTION_SERVO_SMOOTH,     // 缓动设置舵机角度
    ACTION_MOTOR_SPEED,      // 设置电机速度
    ACTION_STEPPER_ANGLE,    // 步进电机角度控制
    ACTION_WATER_PUMP,       // 新增水泵控制类型 
    ACTION_RESET             // 重置任务状态
} TaskType;

// 定义参数联合体
typedef union {
    struct {
        void* htim;
        uint32_t channel;
        float value;
        uint16_t duration;
    } servo;  // 舵机参数
    
    struct {
        STP_TYPEDEFT* motor;
        float degrees;
        uint16_t speed_rpm;  // 新增转速参数
    } stepper;  // 步进电机参数
    
    struct {
        uint8_t motor_id; // 电机编号1/2
        uint16_t speed;
    } motor;  // 普通电机参数

    struct { // 水泵参数
        uint8_t pump_id;  // 水泵编号1/2
        uint8_t duty;     // 占空比档位(0-5)
    } water;
} TaskParams;

// 优化后的任务结构体
typedef struct {
    uint32_t trigger_time;   // 触发时间（基于10ms单位）
    TaskType type;            // 任务类型
    TaskParams params;        // 参数联合体
} TeaTask;

/**
  * @brief  预热操作
  * @param  无
  * @retval 无
  */
// 任务表初始化
const TeaTask preheat_process[] = {
    // 触发时间 | 任务类型          | 参数配置
    
    // ... 其他任务项
    {2500, ACTION_RESET,          {0}} //复位   
};
void Preheat_Control(void)
{
    static uint8_t last_executed = 0;
    
    for (uint8_t i = last_executed; i < sizeof(preheat_process)/sizeof(TeaTask); i++) {
        if (preheat_time < preheat_process[i].trigger_time) break;
        
        switch (preheat_process[i].type) {
            case ACTION_SERVO_INSTANT:
                Servo_SetInstantAngle(
                    preheat_process[i].params.servo.htim,
                    preheat_process[i].params.servo.channel,
                    preheat_process[i].params.servo.value
                );
                break;
                
            case ACTION_SERVO_SMOOTH:
                Servo_StartSmoothMove(
                    preheat_process[i].params.servo.htim,
                    preheat_process[i].params.servo.channel,
                    preheat_process[i].params.servo.value,
                    preheat_process[i].params.servo.duration
                );
                break;
                
            case ACTION_MOTOR_SPEED:
                Motor_Control(preheat_process[i].params.motor.motor_id, preheat_process[i].params.motor.speed);
                break;

            case ACTION_STEPPER_ANGLE: {
                // 设置步进电机角度和转速
                STP_TYPEDEFT* motor = preheat_process[i].params.stepper.motor;
                float degrees = preheat_process[i].params.stepper.degrees;
                uint16_t rpm = preheat_process[i].params.stepper.speed_rpm;
                
                // 设置转速（需在StepperMotor_SetAngle前调用）
                StepperMotor_SetSpeed(motor, rpm);
                StepperMotor_SetAngle(motor, degrees);
                break;
            }

            case ACTION_WATER_PUMP:
                WaterPump_Control(preheat_process[i].params.water.pump_id, preheat_process[i].params.water.duty);
                break;
                
            case ACTION_RESET:
                preheat_flag = 0;
                preheat_time = 0;
                last_executed = 0;
                return;
                
            default:
                break;
        }
        last_executed = i + 1;
    }	
}

/**
  * @brief  煮茶操作
  * @param  无
  * @retval 无
  */

// 任务表初始化
const TeaTask tea_process[] = {
    // 触发时间 | 任务类型          | 参数配置
    //添茶
    {10,  ACTION_SERVO_SMOOTH,  .params.servo = {&htim2, TIM_CHANNEL_4, HOLDER_4_P, 100}}, //舵机4
    {200,  ACTION_SERVO_SMOOTH,  .params.servo = {&htim2, TIM_CHANNEL_1, HOLDER_1_T, 500}}, //舵机3
    {500,  ACTION_MOTOR_SPEED,   .params.motor = {Motor_1, 200}}, //电机1开
    {800,  ACTION_MOTOR_SPEED,   .params.motor = {Motor_1, 0}}, //电机1关
    //添水
    {850,  ACTION_SERVO_SMOOTH, .params.servo = {&htim2, TIM_CHANNEL_1, HOLDER_1_W, 1000}}, //舵机1
    {1150, ACTION_STEPPER_ANGLE, .params.stepper = {&g_stepper2, 720.0f, 10000}}, //步进电机2
    {1200, ACTION_WATER_PUMP,    .params.water = {PUMP_2, 2}}, //水泵2
    // {1500, ACTION_STEPPER_ANGLE, .params.stepper = {&g_stepper2, 720.0f, 10000}}, //步进电机2
    {1600, ACTION_STEPPER_ANGLE, .params.stepper = {&g_stepper2, 0.0f, 10000}}, //步进电机2
    {2050, ACTION_WATER_PUMP,    .params.water = {PUMP_2, 0}}, //水泵2
    {2100, ACTION_SERVO_SMOOTH, .params.servo = {&htim2, TIM_CHANNEL_1, HOLDER_1_M, 500}}, //舵机1
    {2300, ACTION_SERVO_SMOOTH, .params.servo = {&htim2, TIM_CHANNEL_3, HOLDER_3_D, 100}}, //舵机3
    //摇壶
    {2420, ACTION_SERVO_INSTANT, .params.servo = {&htim2, TIM_CHANNEL_2, SHAKER_1_D, 0}}, //舵机2
    {2430, ACTION_SERVO_INSTANT, .params.servo = {&htim2, TIM_CHANNEL_2, SHAKER_1_U, 0}},
    {2440, ACTION_SERVO_INSTANT, .params.servo = {&htim2, TIM_CHANNEL_2, SHAKER_1_D, 0}},
    {2450, ACTION_SERVO_INSTANT, .params.servo = {&htim2, TIM_CHANNEL_2, SHAKER_1_U, 0}},
    {2460, ACTION_SERVO_INSTANT, .params.servo = {&htim2, TIM_CHANNEL_2, SHAKER_1_D, 0}},
    {2470, ACTION_SERVO_INSTANT, .params.servo = {&htim2, TIM_CHANNEL_2, SHAKER_1_U, 0}},
    //沏茶
    {2500, ACTION_SERVO_SMOOTH, .params.servo = {&htim2, TIM_CHANNEL_2, HOLDER_2_D, 100}}, //舵机2
    {2510, ACTION_STEPPER_ANGLE, .params.stepper = {&g_stepper1, 360.0f, 10000}}, //步进电机1
    {2910, ACTION_STEPPER_ANGLE, .params.stepper = {&g_stepper1, 0.0f, 10000}}, //步进电机1
    {3300, ACTION_SERVO_SMOOTH, .params.servo = {&htim2, TIM_CHANNEL_2, HOLDER_2_U, 100}}, //舵机2
    {3400, ACTION_SERVO_SMOOTH, .params.servo = {&htim2, TIM_CHANNEL_3, HOLDER_3_U, 100}}, //舵机3
    // ... 其他任务项
    {3420, ACTION_RESET,          {0}} //复位
};
void Maketea_Control(void) 
{
    static uint8_t last_executed = 0;
    
    for (uint8_t i = last_executed; i < sizeof(tea_process)/sizeof(TeaTask); i++) {
        if (maketea_time < tea_process[i].trigger_time) break;
        
        switch (tea_process[i].type) {
            case ACTION_SERVO_INSTANT:
                Servo_SetInstantAngle(
                    tea_process[i].params.servo.htim,
                    tea_process[i].params.servo.channel,
                    tea_process[i].params.servo.value
                );
                break;
                
            case ACTION_SERVO_SMOOTH:
                Servo_StartSmoothMove(
                    tea_process[i].params.servo.htim,
                    tea_process[i].params.servo.channel,
                    tea_process[i].params.servo.value,
                    tea_process[i].params.servo.duration
                );
                break;
                
            case ACTION_MOTOR_SPEED:
                Motor_Control(tea_process[i].params.motor.motor_id, tea_process[i].params.motor.speed);
                break;

            case ACTION_STEPPER_ANGLE: {
                // 设置步进电机角度和转速
                STP_TYPEDEFT* motor = tea_process[i].params.stepper.motor;
                float degrees = tea_process[i].params.stepper.degrees;
                uint16_t rpm = tea_process[i].params.stepper.speed_rpm;
                
                // 设置转速（需在StepperMotor_SetAngle前调用）
                StepperMotor_SetSpeed(motor, rpm);
                StepperMotor_SetAngle(motor, degrees);
                break;
            }

            case ACTION_WATER_PUMP:
                WaterPump_Control(tea_process[i].params.water.pump_id, tea_process[i].params.water.duty);
                break;
                
            case ACTION_RESET:
                maketea_flag = 0;
                maketea_time = 0;
                last_executed = 0;
                return;
                
            default:
                break;
        }
        last_executed = i + 1;
    }
}

/**
  * @brief  清洗操作
  * @param  无
  * @retval 无
  */
const TeaTask clean_process[] = {
    // 触发时间 | 任务类型          | 参数配置
    {10, ACTION_STEPPER_ANGLE, .params.stepper = {&g_stepper1, 360.0f, 10000}}, //步进电机1
    {20, ACTION_SERVO_SMOOTH, .params.servo = {&htim2, TIM_CHANNEL_3, HOLDER_3_U, 100}}, //舵机3
    {30, ACTION_WATER_PUMP,    .params.water = {PUMP_1, 2}}, //水泵1
    {100, ACTION_SERVO_SMOOTH, .params.servo = {&htim2, TIM_CHANNEL_1, HOLDER_1_W, 1000}}, //舵机1
    {400, ACTION_STEPPER_ANGLE, .params.stepper = {&g_stepper1, 0.0f, 10000}}, //步进电机1
    {405, ACTION_WATER_PUMP,    .params.water = {PUMP_1, 0}}, //水泵1
    {400, ACTION_WATER_PUMP,    .params.water = {PUMP_2, 2}}, //水泵2
    {720, ACTION_WATER_PUMP,    .params.water = {PUMP_2, 0}}, //水泵2
    {730, ACTION_SERVO_SMOOTH, .params.servo = {&htim2, TIM_CHANNEL_4, HOLDER_4_N, 100}}, //舵机4
    {790, ACTION_SERVO_INSTANT, .params.servo = {&htim3, TIM_CHANNEL_1, HOLDER_5_N, 0}}, //舵机5
    {800, ACTION_SERVO_SMOOTH, .params.servo = {&htim2, TIM_CHANNEL_4, HOLDER_4_P, 100}}, //舵机4
    {840, ACTION_SERVO_INSTANT, .params.servo = {&htim3, TIM_CHANNEL_1, HOLDER_5_P, 0}}, //舵机5
    {850, ACTION_SERVO_SMOOTH, .params.servo = {&htim2, TIM_CHANNEL_1, HOLDER_1_M, 1000}}, //舵机1
    // ... 其他任务项
    {1100, ACTION_RESET,          {0}} //复位    
};

void Clean_Control(void)
{
    static uint8_t last_executed = 0;
    
    for (uint8_t i = last_executed; i < sizeof(clean_process)/sizeof(TeaTask); i++) {
        if (clean_time < clean_process[i].trigger_time) break;
        
        switch (clean_process[i].type) {
            case ACTION_SERVO_INSTANT:
                Servo_SetInstantAngle(
                    clean_process[i].params.servo.htim,
                    clean_process[i].params.servo.channel,
                    clean_process[i].params.servo.value
                );
                break;
                
            case ACTION_SERVO_SMOOTH:
                Servo_StartSmoothMove(
                    clean_process[i].params.servo.htim,
                    clean_process[i].params.servo.channel,
                    clean_process[i].params.servo.value,
                    clean_process[i].params.servo.duration
                );
                break;
                
            case ACTION_MOTOR_SPEED:
                Motor_Control(clean_process[i].params.motor.motor_id, clean_process[i].params.motor.speed);
                break;

            case ACTION_STEPPER_ANGLE: {
                // 设置步进电机角度和转速
                STP_TYPEDEFT* motor = clean_process[i].params.stepper.motor;
                float degrees = clean_process[i].params.stepper.degrees;
                uint16_t rpm = clean_process[i].params.stepper.speed_rpm;
                
                // 设置转速（需在StepperMotor_SetAngle前调用）
                StepperMotor_SetSpeed(motor, rpm);
                StepperMotor_SetAngle(motor, degrees);
                break;
            }

            case ACTION_WATER_PUMP:
                WaterPump_Control(clean_process[i].params.water.pump_id, clean_process[i].params.water.duty);
                break;
                
            case ACTION_RESET:
                clean_flag = 0;
                clean_time = 0;
                last_executed = 0;
                return;
                
            default:
                break;
        }
        last_executed = i + 1;
    }	
}

/**
  * @brief  添茶操作
  * @param  无
  * @retval 无
  */
const TeaTask add_process[] = {
    // 触发时间 | 任务类型          | 参数配置
    //添水
    {20,  ACTION_SERVO_SMOOTH, .params.servo = {&htim2, TIM_CHANNEL_1, HOLDER_1_W, 1000}}, //舵机1
    {400, ACTION_STEPPER_ANGLE, .params.stepper = {&g_stepper2, 720.0f, 10000}}, //步进电机1
    {410, ACTION_WATER_PUMP,    .params.water = {PUMP_2, 2}}, //水泵2
    {1000, ACTION_STEPPER_ANGLE, .params.stepper = {&g_stepper2,0.0f, 10000}}, //步进电机1
    // {500, ACTION_STEPPER_ANGLE, .params.stepper = {&g_stepper1, 0.0f, 10000}}, //步进电机1
    {1600, ACTION_WATER_PUMP,    .params.water = {PUMP_2, 0}}, //水泵2
    {1650, ACTION_SERVO_SMOOTH, .params.servo = {&htim2, TIM_CHANNEL_1, HOLDER_1_M, 1000}}, //舵机1
    {1950, ACTION_SERVO_SMOOTH, .params.servo = {&htim2, TIM_CHANNEL_3, HOLDER_3_D, 100}}, //舵机3
    //摇壶
    {2050, ACTION_SERVO_INSTANT, .params.servo = {&htim2, TIM_CHANNEL_2, SHAKER_1_D, 0}}, //舵机2
    {2060, ACTION_SERVO_INSTANT, .params.servo = {&htim2, TIM_CHANNEL_2, SHAKER_1_U, 0}},
    {2070, ACTION_SERVO_INSTANT, .params.servo = {&htim2, TIM_CHANNEL_2, SHAKER_1_D, 0}},
    {2080, ACTION_SERVO_INSTANT, .params.servo = {&htim2, TIM_CHANNEL_2, SHAKER_1_U, 0}},
    {2090, ACTION_SERVO_INSTANT, .params.servo = {&htim2, TIM_CHANNEL_2, SHAKER_1_D, 0}},
    {2100, ACTION_SERVO_INSTANT, .params.servo = {&htim2, TIM_CHANNEL_2, SHAKER_1_U, 0}},
    //沏茶
    {2110, ACTION_SERVO_SMOOTH, .params.servo = {&htim2, TIM_CHANNEL_2, HOLDER_2_D, 100}}, //舵机2
    {2160, ACTION_STEPPER_ANGLE, .params.stepper = {&g_stepper1, 360.0f, 10000}}, //步进电机2
    {2760, ACTION_STEPPER_ANGLE, .params.stepper = {&g_stepper1, 0.0f, 10000}}, //步进电机2
    {3350, ACTION_SERVO_SMOOTH, .params.servo = {&htim2, TIM_CHANNEL_2, HOLDER_2_U, 100}}, //舵机2
    {3400, ACTION_SERVO_SMOOTH, .params.servo = {&htim2, TIM_CHANNEL_3, HOLDER_3_U, 100}}, //舵机3
    // ... 其他任务项
    {3410, ACTION_RESET,          {0}} //复位    
};

void Addtea_Control(void)
{
    static uint8_t last_executed = 0;
    
    for (uint8_t i = last_executed; i < sizeof(add_process)/sizeof(TeaTask); i++) {
        if (addtea_time < add_process[i].trigger_time) break;
        
        switch (add_process[i].type) {
            case ACTION_SERVO_INSTANT:
                Servo_SetInstantAngle(
                    add_process[i].params.servo.htim,
                    add_process[i].params.servo.channel,
                    add_process[i].params.servo.value
                );
                break;
                
            case ACTION_SERVO_SMOOTH:
                Servo_StartSmoothMove(
                    add_process[i].params.servo.htim,
                    add_process[i].params.servo.channel,
                    add_process[i].params.servo.value,
                    add_process[i].params.servo.duration
                );
                break;
                
            case ACTION_MOTOR_SPEED:
                Motor_Control(add_process[i].params.motor.motor_id, add_process[i].params.motor.speed);
                break;

            case ACTION_STEPPER_ANGLE: {
                // 设置步进电机角度和转速
                STP_TYPEDEFT* motor = add_process[i].params.stepper.motor;
                float degrees = add_process[i].params.stepper.degrees;
                uint16_t rpm = add_process[i].params.stepper.speed_rpm;
                
                // 设置转速（需在StepperMotor_SetAngle前调用）
                StepperMotor_SetSpeed(motor, rpm);
                StepperMotor_SetAngle(motor, degrees);
                break;
            }

            case ACTION_WATER_PUMP:
                WaterPump_Control(add_process[i].params.water.pump_id, add_process[i].params.water.duty);
                break;
                
            case ACTION_RESET:
                addtea_flag = 0;
                addtea_time = 0;
                last_executed = 0;
                return;
                
            default:
                break;
        }
        last_executed = i + 1;
    }
}

/********************************************************
函数名：  	Protocol_parsing
日期：    	
功能：   	解析串口屏协议 	
输入参数：
返回值： 		
修改记录：
**********************************************************/
void Protocol_parsing(void)
{
	//串口数据格式：
	//串口数据帧长度：6字节
	//帧头      编号  	 状态    	帧尾
	//0x55      1字节    1字节     0xffffff
	//例子1：上位机代码  printh 55 01 00 ff ff ff  含义：1号led关闭
	//例子2：上位机代码  printh 55 04 01 ff ff ff  含义：4号led打开

	  while(usize >= FRAMELENGTH)
	  {
		  //校验帧头帧尾是否匹配
		  if(u(0) != 0x55 || u(3) != 0xff || u(4) != 0xff || u(5) != 0xff)
		  {
			  //不匹配删除1字节
			  udelete(1);
		  }
		  else
		  {
			  //匹配，跳出循环
			  break;
		  }
 
	  }
 
	  //进行解析
	  if(usize >= FRAMELENGTH && u(0) == 0x55 && u(3) == 0xff && u(4) == 0xff && u(5) == 0xff)
	  {
//		  TJCPrintf("msg.txt=\"led %d is %s\"", u(1), u(2) ? "on" : "off");
		  printf("任务编号:%d，任务状态:%d\r\n", u(1), u(2));
		  if(u(1) == 0x00 && u(2) == 0x01)
		  {
			  maketea_flag = 1;
			  printf("煮茶\r\n");
		  }
		  else if(u(1) == 0x01 && u(2) == 0x01)
		  {
			  clean_flag = 1;
			  printf("清洗\r\n");
		  }
		  else if(u(1) == 0x02 && u(2) == 0x01)
		  {
			  preheat_flag = 1;
			  printf("预热\r\n");
		  }
          else if(u(1) == 0x03 && u(2) == 0x01)
          {
              addtea_flag = 1;
              printf("添茶\r\n");
          }
		  udelete(FRAMELENGTH);
	  }
}


void KeyEventCallBack(void)
{
    for (uint8_t i = 0; i < key_num; i++)
    {
        if (key_array[i].key_value != key_none)
        {
            if(key_array[0].key_value == key_click_one)
            {
                Key_State.Left = 1;
            }
            if(key_array[1].key_value == key_click_one)
            {
                Key_State.Enter = 1;
            }
            if(key_array[2].key_value == key_click_one)
            {
                Key_State.Right = 1;
            }

            switch (key_array[i].key_value)
            {
            case key_click_one:
                printf("Key %d single click detected!\n", i);
                break;
            case key_click_double:
                printf("Key %d double click detected!\n", i);
                break;
            case key_long_press:
                printf("Key %d long press detected!\n", i);
                break;
            default:
                break;
            }

            // 清除按键值，防止重复处理
            key_array[i].key_value = key_none;
        }
    }
}

void VolatgeEventCallBack(void)
{
	static uint16_t Vn=0x00,Vn_1=0x00,Vn_2=0x00,Vn_3;
	
	// 查询ADC状态
	uint32_t state = HAL_ADC_GetState(&hadc2);
	if (( state & HAL_ADC_STATE_REG_EOC) == HAL_ADC_STATE_REG_EOC)
	{
		//滑动滤波
		result[0] = HAL_ADC_GetValue(&hadc2)/4096.0*3.3*11.0;
		Vn=(Vn_1+Vn_2+Vn_3+result[0])>>2;
        Vn_1=Vn_2;
        Vn_2=Vn_3;
        Vn_3=result[0];
		
		// 获取ADC转换结果
		Vout = (float)(Vn/4096.0*3.3*11);
//		printf("voltage: %.2f \r\n", Vout);
	}
	else
	{
//		printf("adc state %d \r\n",state);
	}
}
