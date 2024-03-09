#ifndef __MOTOR_H
#define __MOTOR_H
#define PWMA   TIM1->CCR4  //PA11
#define PWMB   TIM1->CCR1  //PA8
void set_pin(void);
void Set_Pwm(int moto1,int moto2);
int myabs(int a);
void Xianfu_Pwm(void);
void Turn_Off(float voltage);
extern int 	 Moto1,Moto2;
#endif
