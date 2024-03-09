#include "control.h"	
#include "encoder.h"
#include "motor.h"
#include "stm32f1xx_hal.h"
#include "tim.h"
#define E_DIR -1
#define K_DIR -1



//#define SPEED_Y 40 //ǰ������趨�ٶ�
//#define SPEED_Z 100//��������趨�ٶ� 

float velocity_KP=K_DIR * 6;     // С���ٶȻ�PI����
float velocity_KI=K_DIR * 6;



//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
//{
//	if(htim->Instance == htim4.Instance)
//		{
//			Encoder_Right=E_DIR*Read_Encoder(2);                   
//			Encoder_Left=-E_DIR*Read_Encoder(3);
//			Kinematic_Analysis(Velocity,Turn);
//			Moto1=Incremental_PI_A(Encoder_Left,Target_A);                 //===�������ֵ������PWM
//			Moto2=Incremental_PI_B(Encoder_Right,Target_B);                 //===�������ֵ������PWM
				
//			Xianfu_Pwm();  																					 //===PWM�޷�
//			//Turn_Off(Voltage);																 //===���Ƕ��Լ���ѹ�Ƿ�����
//			Set_Pwm(1000,1000);                                    //===��ֵ��PWM�Ĵ���  
//	}
//}
/**************************************************************************
�������ܣ�PI������
��ڲ���������������ֵ��Ŀ���ٶ�
����  ֵ�����PWM
**************************************************************************/
int Incremental_PI_A (int Encoder,int Target)
{ 	
	 static int Bias,Pwm,Last_bias;
	 Bias=Encoder-Target;                //����ƫ��
	 Pwm+=velocity_KP*(Bias-Last_bias)+velocity_KI*Bias;   //����ʽPI������
	 Last_bias=Bias;	                   //������һ��ƫ�� 
	 return Pwm;                         //�������
}
int Incremental_PI_B (int Encoder,int Target)
{ 	
	 static int Bias,Pwm,Last_bias;
	 Bias=Encoder-Target;                //����ƫ��
	 Pwm+=velocity_KP*(Bias-Last_bias)+velocity_KI*Bias;   //����ʽPI������
	 Last_bias=Bias;	                   //������һ��ƫ�� 
	 return Pwm;                         //�������
}


/**************************************************************************
�������ܣ�С���˶���ѧģ��
��ڲ������ٶȺ�ת��
����  ֵ����
**************************************************************************/
void Kinematic_Analysis(int velocity,int turn)
{
		Target_A=velocity+turn; 
		Target_B=velocity-turn;      //���ֲ���
}

