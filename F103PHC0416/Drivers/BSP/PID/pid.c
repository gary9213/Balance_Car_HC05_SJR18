#include "./BSP/PID/pid.h"
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/ENCODER/encoder.h"
#include "./BSP/MOTOR/motor.h"
#include "./BSP/HC05/hc05.h"
extern short  LeftSpeed;
extern short RightSpeed;
extern float pit, rol, yaw;
extern int16_t acc_x, acc_y, acc_z;
extern int16_t gyr_x, gyr_y, gyr_z;
extern int16_t temp;
uint8_t SPEED_X,SPEED_Z;
int Vertical(float Med,float Angle,float gyro_X);
int PWM_out;
int MOTO1,MOTO2;
BlanceCar_PID PID;

extern uint8_t Fore,Back,Left,Right;
/*------------------------------------------
 ��������:PID������ʼ��
 ����˵��:��
------------------------------------------*/
void PID_ParaInit(void)
{
    PID.Med_Angle=1.3;//��е��ֵ--��ʹ��С������ƽ��ס�ĽǶȡ�

    
    
    PID.Vertical_Kp=-230;//ֱ����KP
    PID.Vertical_Kd=-2.6;//ֱ����KD

    PID.Velocity_Kp=0.16;//�ٶȻ�KP
    PID.Velocity_Ki=0.0008; //�ٶȻ�KI

    PID.Turn_Kp=40;    //ת��KP
    PID.Turn_Kd=0.2;   //ת��KP

    PID.Vertical_out=0;//ֱ�����������
    PID.Velocity_out=0; //�ٶȻ��������
    PID.Turn_out=0;

    PID.Turn_out=0;       //ת���������
    PID.Target_Speed=0;	  //�����ٶȣ�������
    PID.Turn_Speed=0;		  //�����ٶȣ�ƫ����
    


}





void PID_control(void)
{
    if((Fore==0)&&(Back==0))PID.Target_Speed=0;//δ���ܵ�ǰ������ָ��-->�ٶ����㣬����ԭ��
    if(Fore==1)PID.Target_Speed=-25;// ǰ��1��־λ����-->��Ҫǰ��
    if(Back==1)PID.Target_Speed=25;//
    PID.Target_Speed=PID.Target_Speed>SPEED_X?SPEED_X:(PID.Target_Speed<-SPEED_X?(-SPEED_X):PID.Target_Speed);//�޷�

    /*����*/
    if((Left==0)&&(Right==0))PID.Turn_Speed=0;
    if(Left==1)PID.Turn_Speed-=50;	//��ת
    if(Right==1)PID.Turn_Speed+=50;	//��ת
    PID.Turn_Speed=PID.Turn_Speed>SPEED_Z?SPEED_Z:(PID.Turn_Speed<-SPEED_Z?(-SPEED_Z):PID.Turn_Speed);//�޷�( (20*100) * 100   )

    /*ת��Լ��*/
    if((Left==0)&&(Right==0))PID.Turn_Kd=-0.7;//��������ת��ָ�����ת��Լ��
    else if((Left==1)||(Right==1))PID.Turn_Kd=0;//������ת��ָ����յ�����ȥ��ת��Լ��

    //1.�ɼ�����������&MPU6050�Ƕ���Ϣ��
    Read_RightSpeed(&RightSpeed);//�������԰�װ���պ����180�ȣ�Ϊ�˱������������һ�£�����Ҫ������һ��ȡ����
    Read_LeftSpeed(&LeftSpeed);

    //2.������ѹ��ջ������У�����������������
    PID.Velocity_out=Velocity(PID.Target_Speed,LeftSpeed,RightSpeed);//�ٶȻ�
    PID.Vertical_out=Vertical( PID.Velocity_out-PID.Med_Angle,rol,gyr_x);  //ֱ����


    PID.Turn_out=Turn(gyr_z,PID.Turn_Speed);																//ת��

    PWM_out=PID.Vertical_out;//�������
    //3.�ѿ�����������ص�����ϣ�������յĵĿ��ơ�
    MOTO1=PWM_out-PID.Turn_out;//����
    MOTO2=PWM_out+PID.Turn_out;//�ҵ��
    Limit(&MOTO1,&MOTO2);	 //PWM�޷�			
    Load(MOTO1,MOTO2);		 //���ص�����ϡ�

}

/*------------------------------------------
 ��������:ֱ����PD������
 ����˵��:
	->��ڲ����������Ƕȡ���ʵ�Ƕȡ���ʵ���ٶ�
	->���ڲ�����ֱ�������
------------------------------------------*/
int Vertical(float Angle,float Med,float gyro_Y)
{
	int PWM_out;
	
	PWM_out=PID.Vertical_Kp*(Med-Angle)+PID.Vertical_Kd*(0-gyro_Y);//��1��
	return PWM_out;
}
/*------------------------------------------
 ��������:�ٶȻ�PI������
 ����˵��:
	->��ڲ����������ٶȶȡ����������ֵ���ұ�������ֵ
	->���ڲ������ٶȻ����
------------------------------------------*/

int Velocity(int Target,int encoder_left,int encoder_right)
{
	static int PWM_out,Encoder_Err,Encoder_S,EnC_Err_Lowout,EnC_Err_Lowout_last;//��2��
	float a=0.7;//��3��
	
	//1.�����ٶ�ƫ��
	Encoder_Err= (encoder_left+encoder_right)-Target;//��ȥ���encoder_right-0;//
	//2.���ٶ�ƫ����е�ͨ�˲�
	//low_out=(1-a)*Ek+a*low_out_last;
	EnC_Err_Lowout=(1-a)*Encoder_Err+a*EnC_Err_Lowout_last;//ʹ�ò��θ���ƽ�����˳���Ƶ���ţ���ֹ�ٶ�ͻ�䡣
	EnC_Err_Lowout_last=EnC_Err_Lowout;//��ֹ�ٶȹ����Ӱ��ֱ����������������
	//3.���ٶ�ƫ����֣����ֳ�λ��
	Encoder_S+=EnC_Err_Lowout;//��4��
	//4.�����޷�
	Encoder_S=Encoder_S>10000?10000:(Encoder_S<(-10000)?(-10000):Encoder_S);
//	if((Angle_Balance>80)||(Angle_Balance<-80)||Voltage<1130||BalanceState==0)//С���Ѿ��㵹���ߵ�ѹ���ͻ���δʹ�ܣ���������
//	{
//		Encoder_S=0;//���ص�����ϡ�
//	}
	//5.�ٶȻ������������
	PWM_out=PID.Velocity_Kp*EnC_Err_Lowout+PID.Velocity_Ki*Encoder_S;//��5��
	return PWM_out;
}

//if((Fore==0)&&(Back==0))Target_Speed=0;//δ���ܵ�ǰ������ָ��-->�ٶ����㣬����ԭ��
//			if(Fore==1)Target_Speed=-25;// ǰ��1��־λ����-->��Ҫǰ��
//			if(Back==1)Target_Speed=25;//

/*********************
ת�򻷣�ϵ��*Z����ٶ�+ϵ��*ң������
*********************/
int Turn(int gyro_Z,int RC)
{
	int PWM_out;
	//�ⲻ��һ���ϸ��PD��������Kd��Ե���ת���Լ������Kp��Ե���ң�ص�ת��
	PWM_out=PID.Turn_Kd*gyro_Z + PID.Turn_Kp*RC;
	return PWM_out;
}

