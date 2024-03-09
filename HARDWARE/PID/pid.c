#include "pid.h"
#include <stdint.h>
#include "gpio.h"
#include "motor.h"
#include "tim.h"
#include "stm32f1xx_hal.h"
int sensor_read = 0x00000000;
int position;

float Kp = 0.002; //set up the constants value
float Ki = 0.001;
float Kd = 15;
float Kr = 0;
int P, I, D, R;
int lastError = 0;
int errors[10] = {0,0,0,0,0,0,0,0,0,0};
int error_sum = 0;
int last_end = 0;	// 0 -> Left, 1 -> Right 
int last_idle = 0;

const uint8_t maxspeedr = 100;
const uint8_t maxspeedl = 100;
const uint8_t basespeedr = 15;
const uint8_t basespeedl = 15;
const int ARR = 10;
int actives = 0;


//*************
//¹¦ÄÜ×xÈ¡
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim){
	if(htim == &htim4){
		PID_control();
	}
}
	
int QTR8_read () 
{
	sensor_read = 0x00000000;
	int pos = 0;
  int active = 0;
	
	if (HAL_GPIO_ReadPin(SENSOR1_GPIO_Port, SENSOR1_Pin)) {
		sensor_read |= 0x00000001;
		pos += 3000;
    active++;
		last_end = 1;
	}
	if (HAL_GPIO_ReadPin(SENSOR2_GPIO_Port, SENSOR2_Pin)) {
		sensor_read |= 0x00000010;
		pos += 2500;
    active++;
  }
	if (HAL_GPIO_ReadPin(SENSOR3_GPIO_Port, SENSOR3_Pin)) {
		sensor_read |= 0x00000100;
		pos += 3000;
    active++;
  }
	if (HAL_GPIO_ReadPin(SENSOR4_GPIO_Port, SENSOR4_Pin)) {
		sensor_read |= 0x00001000;
		pos += 4000;
    active++;
  }
	if (HAL_GPIO_ReadPin(SENSOR5_GPIO_Port, SENSOR5_Pin)) {
		sensor_read |= 0x00010000;
		pos += 5000;
    active++;
  }
	if (HAL_GPIO_ReadPin(SENSOR6_GPIO_Port, SENSOR6_Pin)) {
		sensor_read |= 0x00100000;
		pos += 6000;
    active++;
  }
	if (HAL_GPIO_ReadPin(SENSOR7_GPIO_Port, SENSOR7_Pin)) {
		sensor_read |= 0x01000000;
		pos += 6500;
    active++;
  }
	if (HAL_GPIO_ReadPin(SENSOR8_GPIO_Port, SENSOR8_Pin)) {
		sensor_read |= 0x10000000;
		pos += 5500;
    active++;
		last_end = 0;
  }
	actives = active;
	position = pos/active;
	if (actives == 0)
		last_idle++;
	else
		last_idle = 0;

	return pos/active;
}
	
	
	
	
void forward_brake(int pos_right, int pos_left) 
{
	if (actives == 0)
		sharp_turn();
	else
		motor_control(pos_right, pos_left);
}
void past_errors (int error) 
{
  for (int i = 9; i > 0; i--) 
      errors[i] = errors[i-1];
  errors[0] = error;
}
int errors_sum (int index, int abs) 
{
  int sum = 0;
  for (int i = 0; i < index; i++) 
  {
    if (abs == 1 & errors[i] < 0) 
      sum += -errors[i]; 
    else
      sum += errors[i];
  }
  return sum;
}
	

void sharp_turn () {
	
	if (last_idle < 25)
	{
		if (last_end == 1)
			motor_control(-10, 10);
		else
			motor_control(10, -10);
	}
	else 
	{
		if (last_end == 1)
			motor_control(-15, 15);
		else
			motor_control(15, -15);
	}
}
void motor_control (double pos_right, double pos_left) 
{
	if( pos_right<0)	BIN1=1,	BIN2=0;
		else if(pos_right>0)	BIN1=0,	BIN2=1;
		else BIN2=1,	BIN1=1;
	if(pos_left<0)	AIN1=1,	AIN2=0;
		else if(pos_left>0)	AIN1=0,	AIN2=1;
		else AIN1=1,	AIN2=1;
		set_pin();
		__HAL_TIM_SET_COMPARE (&htim1, TIM_CHANNEL_1, ARR * pos_right);
		__HAL_TIM_SET_COMPARE (&htim1, TIM_CHANNEL_4, ARR * pos_left);
}


void PID_control() {
	uint16_t position = QTR8_read();	
  int error = 4500 - position;
	past_errors(error);

  P = error;
  I = errors_sum(5, 0);
  D = error - lastError;
  R = errors_sum(5, 1);
  lastError = error;
	
  int motorspeed = P*Kp + I*Ki + D*Kd;
  
  int motorspeedl = basespeedl + motorspeed - R*Kr;
  int motorspeedr = basespeedr - motorspeed - R*Kr;
  
  if (motorspeedl > maxspeedl)
    motorspeedl = maxspeedl;
  if (motorspeedr > maxspeedr)
    motorspeedr = maxspeedr;
	
	forward_brake(motorspeedr, motorspeedl);
}