#ifndef __CONTROL_H
#define __CONTROL_H

#define PI 3.14159265
void Kinematic_Analysis(int velocity,int turn);
int Incremental_PI_A (int Encoder,int Target);
int Incremental_PI_B (int Encoder,int Target);
extern int Encoder_Left,Encoder_Right; //編碼器
extern int 	 Moto1,Moto2,Target_A,Target_B;	//馬達目前 目標
extern int Velocity,Turn; //速度 轉向
#endif
