#include "control.h"	
#include "encoder.h"
#include "motor.h"
#include "stm32f1xx_hal.h"
#include "tim.h"
#define E_DIR -1
#define K_DIR -1



//#define SPEED_Y 40 //前后最大设定速度
//#define SPEED_Z 100//左右最大设定速度 

float velocity_KP=K_DIR * 6;     // 小车速度环PI参数
float velocity_KI=K_DIR * 6;



//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
//{
//	if(htim->Instance == htim4.Instance)
//		{
//			Encoder_Right=E_DIR*Read_Encoder(2);                   
//			Encoder_Left=-E_DIR*Read_Encoder(3);
//			Kinematic_Analysis(Velocity,Turn);
//			Moto1=Incremental_PI_A(Encoder_Left,Target_A);                 //===计算左轮电机最终PWM
//			Moto2=Incremental_PI_B(Encoder_Right,Target_B);                 //===计算右轮电机最终PWM
				
//			Xianfu_Pwm();  																					 //===PWM限幅
//			//Turn_Off(Voltage);																 //===检查角度以及电压是否正常
//			Set_Pwm(1000,1000);                                    //===赋值给PWM寄存器  
//	}
//}
/**************************************************************************
函数功能：PI控制器
入口参数：编码器测量值，目标速度
返回  值：电机PWM
**************************************************************************/
int Incremental_PI_A (int Encoder,int Target)
{ 	
	 static int Bias,Pwm,Last_bias;
	 Bias=Encoder-Target;                //计算偏差
	 Pwm+=velocity_KP*(Bias-Last_bias)+velocity_KI*Bias;   //增量式PI控制器
	 Last_bias=Bias;	                   //保存上一次偏差 
	 return Pwm;                         //增量输出
}
int Incremental_PI_B (int Encoder,int Target)
{ 	
	 static int Bias,Pwm,Last_bias;
	 Bias=Encoder-Target;                //计算偏差
	 Pwm+=velocity_KP*(Bias-Last_bias)+velocity_KI*Bias;   //增量式PI控制器
	 Last_bias=Bias;	                   //保存上一次偏差 
	 return Pwm;                         //增量输出
}


/**************************************************************************
函数功能：小车运动数学模型
入口参数：速度和转角
返回  值：无
**************************************************************************/
void Kinematic_Analysis(int velocity,int turn)
{
		Target_A=velocity+turn; 
		Target_B=velocity-turn;      //两轮差速
}

