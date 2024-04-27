#ifndef  _pid_H
#define  _pid_H
#include "./SYSTEM/sys/sys.h"

typedef struct
{
	float Med_Angle;			//机械中值--能使得小车真正平衡住的角度。
	float Vertical_Kp;	  //直立环KP
	float Vertical_Kd;	  //直立环KD
	float Velocity_Kp;	  //速度环KP
	float Velocity_Ki;    //速度环KI
	float Turn_Kd;        //转向环KD
	float Turn_Kp;        //转向环KP
	int 	Vertical_out;   //直立环输出变量
	int 	Velocity_out;   //速度环输出变量
	int 	Turn_out;       //转向环输出变量
	float Target_Speed;	  //期望速度（俯仰）
	float Turn_Speed;		  //期望速度（偏航）	
}BlanceCar_PID;
/* function -------------------------------------------------------------------------------------------------------------*/
int Vertical(float Med,float Angle,float gyro_X);//函数声明
int Velocity(int Target,int encoder_left,int encoder_right);
int Turn(int gyro_Z,int RC); 

void PID_ParaInit(void);
void Get_Angle(uint8_t way);
void Oled_Proc(void);
void Key_Proc(void);

void PID_ParaInit(void);
void PID_control(void);

#endif

