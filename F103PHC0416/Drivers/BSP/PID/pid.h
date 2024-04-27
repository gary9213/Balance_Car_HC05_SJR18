#ifndef  _pid_H
#define  _pid_H
#include "./SYSTEM/sys/sys.h"

typedef struct
{
	float Med_Angle;			//��е��ֵ--��ʹ��С������ƽ��ס�ĽǶȡ�
	float Vertical_Kp;	  //ֱ����KP
	float Vertical_Kd;	  //ֱ����KD
	float Velocity_Kp;	  //�ٶȻ�KP
	float Velocity_Ki;    //�ٶȻ�KI
	float Turn_Kd;        //ת��KD
	float Turn_Kp;        //ת��KP
	int 	Vertical_out;   //ֱ�����������
	int 	Velocity_out;   //�ٶȻ��������
	int 	Turn_out;       //ת���������
	float Target_Speed;	  //�����ٶȣ�������
	float Turn_Speed;		  //�����ٶȣ�ƫ����	
}BlanceCar_PID;
/* function -------------------------------------------------------------------------------------------------------------*/
int Vertical(float Med,float Angle,float gyro_X);//��������
int Velocity(int Target,int encoder_left,int encoder_right);
int Turn(int gyro_Z,int RC); 

void PID_ParaInit(void);
void Get_Angle(uint8_t way);
void Oled_Proc(void);
void Key_Proc(void);

void PID_ParaInit(void);
void PID_control(void);

#endif

