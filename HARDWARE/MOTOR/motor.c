#include "motor.h"
#include "gpio.h"
uint8_t BIN1 ,BIN2,AIN1,AIN2;		
/**************************************************************************
�������ܣ���ֵ��PWM�Ĵ���
��ڲ���������PWM������PWM
����  ֵ����
**************************************************************************/
void set_pin()
{
	if (AIN2 == 0)HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
	else HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
	
	if (AIN1 == 0)HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_RESET);
	else HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_SET);
	
	if (BIN1 == 0)HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);
	else HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_SET);
	
	if (BIN2 == 0)HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,GPIO_PIN_RESET);
	else HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,GPIO_PIN_SET);
	
	


}
void Set_Pwm(int moto1,int moto2)
{	
	if(moto1<0)	BIN1=1,	BIN2=0;
		else if(moto1>0)	BIN1=0,	BIN2=1;
		else BIN2=1,	BIN1=1;
	if(moto2<0)	AIN1=1,	AIN2=0;
		else if(moto2>0)	AIN1=0,	AIN2=1;
		else AIN1=1,	AIN2=1;
		set_pin();
		PWMB=myabs(moto1);	
		PWMA=myabs(moto2);

}



/**************************************************************************
�������ܣ�����ֵ����
��ڲ�����int
����  ֵ��unsigned int
Ŀ    �ģ�����ֱ�������ٶȻ��Լ�ת�򻷼��������PWM�п���Ϊ��ֵ
					��ֻ�ܸ�����ʱ��PWM�Ĵ���ֻ������ֵ������Ҫ��PWM���о���ֵ����
**************************************************************************/
int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}
/**************************************************************************
�������ܣ�����PWM��ֵ 
��ڲ�������
����  ֵ����
**************************************************************************/
void Xianfu_Pwm(void)
{
	 //===PWM������7200 ������7000
    if(Moto1<-6900 ) Moto1=-7000 ;
		if(Moto1>6900 )  Moto1=7000 ;
	  if(Moto2<-6900 ) Moto2=-7000 ;
		if(Moto2>6900 )  Moto2=7000 ;
}
/**************************************************************************
�������ܣ��쳣�رյ��
��ڲ�������Ǻ͵�ѹ
����  ֵ����
**************************************************************************/
void Turn_Off( float voltage)
{
		if(voltage<6.4)	 //��ص�ѹ����11.1V�رյ��
		{	                                   //===��Ǵ���40�ȹرյ��																			 
				Moto1=0;
				Moto2=0;
		}
}
	
