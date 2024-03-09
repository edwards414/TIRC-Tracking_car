#ifndef __PID_H
#define __PID_H
#include <stdint.h>
void PID_control(void);
int QTR8_read (void);
void forward_brake(int pos_right, int pos_left) ;
void sharp_turn (void);
void motor_control (double pos_right, double pos_left) ;

extern uint8_t BIN1 ,BIN2,AIN1,AIN2;
#endif