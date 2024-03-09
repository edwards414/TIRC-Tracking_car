#include "motor.h"
#include "gpio.h"
uint8_t BIN1 ,BIN2,AIN1,AIN2;		
/**************************************************************************
函数功能：赋值给PWM寄存器
入口参数：左轮PWM、右轮PWM
返回  值：无
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
函数功能：绝对值函数
入口参数：int
返回  值：unsigned int
目    的：经过直立环和速度环以及转向环计算出来的PWM有可能为负值
					而只能赋给定时器PWM寄存器只能是正值。故需要对PWM进行绝对值处理
**************************************************************************/
int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}
/**************************************************************************
函数功能：限制PWM赋值 
入口参数：无
返回  值：无
**************************************************************************/
void Xianfu_Pwm(void)
{
	 //===PWM满幅是7200 限制在7000
    if(Moto1<-6900 ) Moto1=-7000 ;
		if(Moto1>6900 )  Moto1=7000 ;
	  if(Moto2<-6900 ) Moto2=-7000 ;
		if(Moto2>6900 )  Moto2=7000 ;
}
/**************************************************************************
函数功能：异常关闭电机
入口参数：倾角和电压
返回  值：无
**************************************************************************/
void Turn_Off( float voltage)
{
		if(voltage<6.4)	 //电池电压低于11.1V关闭电机
		{	                                   //===倾角大于40度关闭电机																			 
				Moto1=0;
				Moto2=0;
		}
}
	
