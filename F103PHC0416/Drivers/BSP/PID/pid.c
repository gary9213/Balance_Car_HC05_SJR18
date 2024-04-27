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
 函数功能:PID参数初始化
 函数说明:无
------------------------------------------*/
void PID_ParaInit(void)
{
    PID.Med_Angle=1.3;//机械中值--能使得小车真正平衡住的角度。

    
    
    PID.Vertical_Kp=-230;//直立环KP
    PID.Vertical_Kd=-2.6;//直立环KD

    PID.Velocity_Kp=0.16;//速度环KP
    PID.Velocity_Ki=0.0008; //速度环KI

    PID.Turn_Kp=40;    //转向环KP
    PID.Turn_Kd=0.2;   //转向环KP

    PID.Vertical_out=0;//直立环输出变量
    PID.Velocity_out=0; //速度环输出变量
    PID.Turn_out=0;

    PID.Turn_out=0;       //转向环输出变量
    PID.Target_Speed=0;	  //期望速度（俯仰）
    PID.Turn_Speed=0;		  //期望速度（偏航）
    


}





void PID_control(void)
{
    if((Fore==0)&&(Back==0))PID.Target_Speed=0;//未接受到前进后退指令-->速度清零，稳在原地
    if(Fore==1)PID.Target_Speed=-25;// 前进1标志位拉高-->需要前进
    if(Back==1)PID.Target_Speed=25;//
    PID.Target_Speed=PID.Target_Speed>SPEED_X?SPEED_X:(PID.Target_Speed<-SPEED_X?(-SPEED_X):PID.Target_Speed);//限幅

    /*左右*/
    if((Left==0)&&(Right==0))PID.Turn_Speed=0;
    if(Left==1)PID.Turn_Speed-=50;	//左转
    if(Right==1)PID.Turn_Speed+=50;	//右转
    PID.Turn_Speed=PID.Turn_Speed>SPEED_Z?SPEED_Z:(PID.Turn_Speed<-SPEED_Z?(-SPEED_Z):PID.Turn_Speed);//限幅( (20*100) * 100   )

    /*转向约束*/
    if((Left==0)&&(Right==0))PID.Turn_Kd=-0.7;//若无左右转向指令，则开启转向约束
    else if((Left==1)||(Right==1))PID.Turn_Kd=0;//若左右转向指令接收到，则去掉转向约束

    //1.采集编码器数据&MPU6050角度信息。
    Read_RightSpeed(&RightSpeed);//电机是相对安装，刚好相差180度，为了编码器输出极性一致，就需要对其中一个取反。
    Read_LeftSpeed(&LeftSpeed);

    //2.将数据压入闭环控制中，计算出控制输出量。
    PID.Velocity_out=Velocity(PID.Target_Speed,LeftSpeed,RightSpeed);//速度环
    PID.Vertical_out=Vertical( PID.Velocity_out-PID.Med_Angle,rol,gyr_x);  //直立环


    PID.Turn_out=Turn(gyr_z,PID.Turn_Speed);																//转向环

    PWM_out=PID.Vertical_out;//最终输出
    //3.把控制输出量加载到电机上，完成最终的的控制。
    MOTO1=PWM_out-PID.Turn_out;//左电机
    MOTO2=PWM_out+PID.Turn_out;//右电机
    Limit(&MOTO1,&MOTO2);	 //PWM限幅			
    Load(MOTO1,MOTO2);		 //加载到电机上。

}

/*------------------------------------------
 函数功能:直立环PD控制器
 函数说明:
	->入口参数：期望角度、真实角度、真实角速度
	->出口参数：直立环输出
------------------------------------------*/
int Vertical(float Angle,float Med,float gyro_Y)
{
	int PWM_out;
	
	PWM_out=PID.Vertical_Kp*(Med-Angle)+PID.Vertical_Kd*(0-gyro_Y);//【1】
	return PWM_out;
}
/*------------------------------------------
 函数功能:速度环PI控制器
 函数说明:
	->入口参数：期望速度度、左编码器数值、右编码器数值
	->出口参数：速度环输出
------------------------------------------*/

int Velocity(int Target,int encoder_left,int encoder_right)
{
	static int PWM_out,Encoder_Err,Encoder_S,EnC_Err_Lowout,EnC_Err_Lowout_last;//【2】
	float a=0.7;//【3】
	
	//1.计算速度偏差
	Encoder_Err= (encoder_left+encoder_right)-Target;//舍去误差encoder_right-0;//
	//2.对速度偏差进行低通滤波
	//low_out=(1-a)*Ek+a*low_out_last;
	EnC_Err_Lowout=(1-a)*Encoder_Err+a*EnC_Err_Lowout_last;//使得波形更加平滑，滤除高频干扰，防止速度突变。
	EnC_Err_Lowout_last=EnC_Err_Lowout;//防止速度过大的影响直立环的正常工作。
	//3.对速度偏差积分，积分出位移
	Encoder_S+=EnC_Err_Lowout;//【4】
	//4.积分限幅
	Encoder_S=Encoder_S>10000?10000:(Encoder_S<(-10000)?(-10000):Encoder_S);
//	if((Angle_Balance>80)||(Angle_Balance<-80)||Voltage<1130||BalanceState==0)//小车已经倾倒或者电压过低或者未使能，消除积分
//	{
//		Encoder_S=0;//加载到电机上。
//	}
	//5.速度环控制输出计算
	PWM_out=PID.Velocity_Kp*EnC_Err_Lowout+PID.Velocity_Ki*Encoder_S;//【5】
	return PWM_out;
}

//if((Fore==0)&&(Back==0))Target_Speed=0;//未接受到前进后退指令-->速度清零，稳在原地
//			if(Fore==1)Target_Speed=-25;// 前进1标志位拉高-->需要前进
//			if(Back==1)Target_Speed=25;//

/*********************
转向环：系数*Z轴角速度+系数*遥控数据
*********************/
int Turn(int gyro_Z,int RC)
{
	int PWM_out;
	//这不是一个严格的PD控制器，Kd针对的是转向的约束，但Kp针对的是遥控的转向。
	PWM_out=PID.Turn_Kd*gyro_Z + PID.Turn_Kp*RC;
	return PWM_out;
}

