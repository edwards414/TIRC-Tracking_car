#ifndef __CONTROL_H
#define __CONTROL_H

#define PI 3.14159265
void Kinematic_Analysis(int velocity,int turn);
int Incremental_PI_A (int Encoder,int Target);
int Incremental_PI_B (int Encoder,int Target);
extern int Encoder_Left,Encoder_Right; //���a��
extern int 	 Moto1,Moto2,Target_A,Target_B;	//�R�_Ŀǰ Ŀ��
extern int Velocity,Turn; //�ٶ� �D��
#endif
