/**
 * \file Cpu0_Main.c
 * \brief Main function definition for Cpu core 0 .
 *
 * \copyright Copyright (c) 2012 Infineon Technologies AG. All rights reserved.
 *
 *
 *
 *                                 IMPORTANT NOTICE
 *
 *
 * Infineon Technologies AG (Infineon) is supplying this file for use
 * exclusively with Infineon's microcontroller products. This file can be freely
 * distributed within development tools that are supporting such microcontroller
 * products.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 */

#include "Tricore/Cpu/Std/Ifx_Types.h"
#include "Tricore/Cpu/Std/IfxCpu_Intrinsics.h"
#include "Tricore/Scu/Std/IfxScuWdt.h"
#include <Stm/Std/IfxStm.h>
#include <Port/Std/IfxPort.h>
#include "Test_Irq.h"
#include "Test_ModuleInit.h"
#include "Test_Pwm.h"
#include "Test_Adc.h"
#include "Test_Encoder.h"


// normally shorter signal is left longer signal is right
// maybe reverse
/****private constants definitions****/
#define CW				0
#define CCW				1
#define SI_0	P22_OUT.B.P0
#define CL_0	P22_OUT.B.P1
#define SI_1	P22_OUT.B.P2
#define CL_1	P22_OUT.B.P3
#define TRESHOLD	4000
#define CAMMISSION	900
#define OBSSTOP		450
#define HILLLIMMIT	1900
#define READY		2000
#define OBSAVOID	65

/****extern variables/function****/
extern void PID(uint16 encodercheck, double goal);
extern uint16 dc_duty;

/****function definitions****/
void schoolzone();
void speedzone();
void direction1();
void direction2();
void Sensor_Part();
void Mission_Part();
void getCamera();
void medianFilter();
void gaussian();
void joke();
void Delay(int time);

/****sensor variables****/
volatile uint16 distance=0;
volatile uint16 hill=0;
uint16 dismid=0;
uint16 hillmid=0;
uint16 dist[5]={0, };
uint16 hist[5]={0, };
uint8 distcnt=0;
uint16 infrared[2]={0, };
uint8 TWO=0;

/****zone and drive variables****/
uint8 dash=0;
uint8 dashline=0;
uint8 zone=0;
uint8 zoneflag=0;
uint16 zonecnt=0;
uint16 before=0;
uint8 state=0;
uint8 obsstate=0;
uint16 servo=610;//L 732 M 610 R 488
uint8 obscnt=0;

/****camera variables****/
float CamS_L[98]={0, };
float CamS_R[98]={0, };
uint16 Cam_L[98]={0, };
uint16 Cam_R[98]={0, };
uint16 Median_L[98]={0, };
uint16 Median_R[98]={0, };
sint32 Gaussian_L[98]={0, };
sint32 Gaussian_R[98]={0, };
sint32 max_L=0;
sint32 max_R=0;
uint8 pixel_L=0;
uint8 pixel_R=0;
uint16 camaver=0;
uint16 Smax_L=0;
uint16 Smax_R=0;
uint16 Smin_L=4095;
uint16 Smin_R=4095;
uint32 camsum=0;

void core0_main (void)
{

	__enable ();
	/*
	 * !!WATCHDOG0 AND SAFETY WATCHDOG ARE DISABLED HERE!!
	 * Enable the watchdog in the demo if it is required and also service the watchdog periodically
	 * */

	IfxScuWdt_disableCpuWatchdog (IfxScuWdt_getCpuWatchdogPassword ());
	IfxScuWdt_disableSafetyWatchdog (IfxScuWdt_getSafetyWatchdogPassword ());
	Test_ModuleInit();
	Delay_ms(READY);

	while (1) {
		/*Camera_Part*/
		P13_OUT.B.P0 = !P13_OUT.B.P0;
		joke();
		Delay_ms(8);
		getCamera();
		medianFilter();
		gaussian();

		/*Sensor_Part*/
		Sensor_Part();

		/*Judgement_Part*/
		Mission_Part();

		/*drive_Part*/
		switch(zone) {
		case 0 :
			direction1();
			speedzone();
			Pwm_servo(servo);
			break;
		case 1 :
			direction2();
			schoolzone();
			Pwm_servo(servo);
			break;
		default :
			break;
		}
	}
}


void SecondTimer_Initialization(void)
{
	volatile float       stm_freq;
	Ifx_STM             *stm = &MODULE_STM0;
	IfxStm_CompareConfig stmCompareConfig;

	/* suspend by debugger enabled */
	IfxStm_enableOcdsSuspend(stm);
	/* get current STM frequency : debug purpose only*/
	stm_freq = IfxScuCcu_getStmFrequency();
	/* constructor of configuration */
	IfxStm_initCompareConfig(&stmCompareConfig);
	stmCompareConfig.triggerPriority = ISR_PRIORITY_STM;
	stmCompareConfig.ticks = 100000000;
	stmCompareConfig.typeOfService = IfxSrc_Tos_cpu0;
	/* Now Compare functionality is initialized */
	IfxStm_initCompare(stm, &stmCompareConfig);

} // End of TaskScheduler_Initialization()

//*********************************************************************************************
// @Function	 	void UsrIsr_Stm_0(void)
// @Description   	STM0 Interrupt for system tick generation
// @Returnvalue		None
// @Parameters    	None
//*********************************************************************************************

IFX_INTERRUPT (SecondTimer_Isr, 0, ISR_PRIORITY_STM);
void SecondTimer_Isr(void)
{
	Ifx_STM *stm = &MODULE_STM0;

	// Set next 1ms scheduler tick alarm
	IfxStm_updateCompare(stm, IfxStm_Comparator_0, IfxStm_getLower(stm) + 100000000);
	__enable();
}


void direction1() {
	//Center L Pixel 21 	R Pixel 77
	//Servo  L 724 <-114-> M 610 <-114-> R 496
	/*
	 * 1-> L pixel O, R pixel O straight
	 * 2-> L pixel O, R pixel X right
	 * 3-> L pixel X, R pixel O left
	 * 4-> L pixel X, R pixel X before or straight
	 */

	if(pixel_L != 0 && pixel_R != 0) state=1;
	else if(pixel_L != 0 && pixel_R == 0) state=2;
	else if(pixel_L == 0 && pixel_R != 0) state=3;
	else if (pixel_L == 0 && pixel_R == 0) state=5;

	switch(state) {
	case 1 :
		servo = 610+2*(101-(pixel_L+pixel_R));
		break;
	case 2 :	// 우회전
		servo = 610-3.5*(pixel_L-20);
		break;
	case 3 :	// 좌회전
		servo = 610-3.5*(pixel_R-81);
		break;
	case 5 :
		servo = before;
		break;
	default :
		break;
	}

	if(servo<488)		servo=488;
	else if(servo>732)	servo=732;
	before = servo;
}
void direction2() {
	//Center L Pixel 21 	R Pixel 77
	//Servo  L 724 <-114-> M 610 <-114-> R 496
	/*
	 * 1-> L pixel O, R pixel O straight
	 * 2-> L pixel O, R pixel X right
	 * 3-> L pixel X, R pixel O left
	 * 4-> L pixel X, R pixel X before or straight
	 */

	if(pixel_L != 0 && pixel_R != 0) state=1;
	else if(pixel_L != 0 && pixel_R == 0) state=2;
	else if(pixel_L == 0 && pixel_R != 0) state=3;
	else if (pixel_L == 0 && pixel_R == 0) state=5;

	switch(state) {
	case 1 :
		servo = 610+2*(101-(pixel_L+pixel_R));
		break;
	case 2 :	// 우회전
		servo = 610-7*(pixel_L-20);
		break;
	case 3 :	// 좌회전
		servo = 610-7*(pixel_R-81);
		break;
	case 5 :
		servo = before;
		break;
	default :
		break;
	}

	if(servo<488)		servo=488;
	else if(servo>732)	servo=732;
	before = servo;
}
void speedzone() { 		// 완성
	dash=0;
	dashline=0;

	if(dismid>OBSSTOP) {
		PID(get_encoder(), 0);
		Pwm_MotorDutyAndDirectionControl(0,0);
	}
	else if(dismid<OBSSTOP){
		if(state==1)	PID(get_encoder(),1.6);
		else			PID(get_encoder(),1.3);
	}
	zonecnt++;
}

void schoolzone() {
	PID(get_encoder(),0.8);

	if(dash==0) {
		if(pixel_L==0 && pixel_R!=0) {
			dashline=1;
			dash=1;
		}
		if(pixel_R==0 && pixel_L!=0){
			dashline=2;
			dash=1;
		}
	}

	if(dismid > 400) {
		P13_OUT.B.P1 = 0;
		obsstate=1;
	}

	if(obsstate==1)	{
		if(dashline==1) {
			servo=732;
			obscnt++;
			if(obscnt==OBSAVOID)
			{
				obscnt=0;
				obsstate=0;
				dashline=2;
				P13_OUT.B.P1 = 1;
			}
		}
		else if(dashline==2) {
			servo=488;
			obscnt++;
			if(obscnt==OBSAVOID)
			{
				obscnt=0;
				obsstate=0;
				dashline=1;
				P13_OUT.B.P1 = 1;
			}
		}
	}
	zonecnt++;

}

void Sensor_Part() {
	uint8 di=0;
	uint8 di1=0;
	uint16 distemp=0;
	uint16 hilltemp=0;

	Test_VadcAutoScan(IfxVadc_GroupId_0);
	Test_VadcAutoScan(IfxVadc_GroupId_1);
	distance=Adc_Result_Scan[0][9];//AN9 102 pin6 => A/D2 3
	hill=Adc_Result_Scan[1][4];//AN16
	infrared[0]=Adc_Result_Scan[0][10]/1000;//AN10
	infrared[1]=Adc_Result_Scan[0][11]/1000;//AN11

	dist[distcnt]=distance;
	hist[distcnt]=hill;
	if(distcnt==2) {
		for(di=0; di<4; di++) {
			for(di1=1; di1<5; di1++) {
				if(dist[di] > dist[di1]){
					distemp = dist[di];
					dist[di] = dist[di1];
					dist[di1] = distemp;
				}
				if(hist[di] > hist[di1]){
					hilltemp = hist[di];
					hist[di] = hist[di1];
					hist[di1] = hilltemp;
				}
			}
		}
		dismid=dist[2];
		hillmid=hist[2];
	}
	distcnt++;
	if(distcnt>4) distcnt=0;
}

void Mission_Part() {	// 100바퀴 확인 요망
	if(camaver<CAMMISSION)	TWO = 1;
	if(hillmid<HILLLIMMIT) 	dismid=0;
	if((infrared[0]==0 && infrared[1]==0) && TWO == 1 && zonecnt > 30){
		P13_OUT.B.P3 = !P13_OUT.B.P3;
		TWO = 0;
		zonecnt=0;
		if(zoneflag==0) {								// 이론적으로 문제가 없음
			zone=1;
			zoneflag=1;
		}
		else if(zoneflag==1){
			zone=0;
			zoneflag=0;
		}
	}

}

void joke() {
	uint8 index = 0;
	uint8 camsize = 127;
	SI_0 = 1;
	SI_1 = 1;
	Delay(3);
	CL_0 = 1;
	CL_1 = 1;
	Delay(3);
	SI_0 = 0;
	SI_1 = 0;
	Delay(3);
	CL_0 = 0;
	CL_1 = 0;
	Delay(6);
	for(index=0; index<camsize; index++) {
		CL_0 = 1;
		CL_1 = 1;
		Delay(6);
		CL_0 = 0;
		CL_1 = 0;
		Delay(6);
	}
}

void getCamera() {
	uint8 index = 0;
	uint8 i=0;
	uint8 i2=0;
	uint8 camsize = 127;

	camsum=0;

	SI_0 = 1;
	SI_1 = 1;
	Delay(3);
	CL_0 = 1;
	CL_1 = 1;
	Delay(3);
	SI_0 = 0;
	SI_1 = 0;
	Delay(3);
	CL_0 = 0;
	CL_1 = 0;
	Delay(6);
	for(index=0; index<camsize; index++) {
		CL_0 = 1;
		CL_1 = 1;
		Delay(6);
		CL_0 = 0;
		CL_1 = 0;
		if(index>13 && index<112) {
			Test_VadcAutoScan(IfxVadc_GroupId_1);
			CamS_L[index-14] = Adc_Result_Scan[1][8];  //AN20 103 pin36 => A/D1 3
			CamS_R[index-14] = Adc_Result_Scan[1][9]; //AN21 103 pin39 => A/D1 2
		}
		Delay(6);
		if(CamS_L[index-14]<Smin_L) Smin_L=CamS_L[index-14];
		if(CamS_L[index-14]>Smax_L) Smax_L=CamS_L[index-14];
		if(CamS_R[index-14]<Smin_R) Smin_R=CamS_R[index-14];
		if(CamS_R[index-14]>Smax_R) Smax_R=CamS_R[index-14];
	}

	for(i=0; i<98; i++){
		Cam_L[i]=2000*((CamS_L[i]-Smin_L)/(Smax_L-Smin_L));
		Cam_R[i]=2000*((CamS_R[i]-Smin_R)/(Smax_R-Smin_R));
	}

	for(i2=10; i2<88; i2++){
		if(68<i2 && i2<88)	camsum += Cam_L[i2];
		if(10<i2 && i2<30)	camsum += Cam_R[i2];
	}

	camaver = camsum/38;
	Smax_L=0;
	Smax_R=0;
	Smin_L=4095;
	Smin_R=4095;
	return;
}
void medianFilter() {
	uint16 camsize=98;
	uint8 box=0;
	uint16 box1=0;
	uint8 i=0;
	uint8 i1=0;
	uint8 i2=0;
	uint8 i3=1;
	sint16 box_L[5]={0};
	sint16 box_R[5]={0};

	Median_L[0] = Cam_L[0];
	Median_L[1] = Cam_L[1];
	Median_R[0] = Cam_R[0];
	Median_R[1] = Cam_R[1];

	Median_L[96] = Cam_L[96];
	Median_L[97] = Cam_L[97];
	Median_R[96] = Cam_R[96];
	Median_R[97] = Cam_R[97];

	for(i=2; i<camsize-2; i++) {
		box=i-2;
		for(i1=0; i1<5; i1++) {
			box_L[i1] = Cam_L[box];
			box_R[i1] = Cam_R[box];
			box++;
		}

		for(i2=0; i2<4; i2++) {
			for(i3=1; i3<5; i3++) {
				if(box_L[i2] > box_L[i3]){
					box1 = box_L[i2];
					box_L[i2] = box_L[i3];
					box_L[i3] = box1;
				}
				if(box_R[i2] > box_R[i3]){
					box1 = box_R[i2];
					box_R[i2] = box_R[i3];
					box_R[i3] = box1;
				}
			}
		}
		Median_L[i] = box_L[2];
		Median_R[i] = box_R[2];
	}
	return;
}

void gaussian() {
	uint8 a=0;
	uint8 index=0;
	uint8 camsize=98;

	for(a=0; a<7; a++){
		Gaussian_L[a]= Median_L[a];
		Gaussian_L[a+91]= Median_L[a+91];
		Gaussian_R[a]=Median_R[a];
		Gaussian_R[a+91]= Median_R[a+91];
	}
	max_L=0;
	max_R=0;
	pixel_L=0;
	pixel_R=0;

	for(index=7; index<camsize-7; index++) {
		Gaussian_L[index] = Median_L[index-7]*(10)+Median_L[index-6]*(5)+Median_L[index-5]*(5)+Median_L[index-4]*(5)+Median_L[index-3]*(5)+
				Median_L[index-2]*(-5)+Median_L[index-1]*(-15)+Median_L[index]*(-20)+Median_L[index+1]*(-15)+Median_L[index+2]*(-5)+
				Median_L[index+3]*(5)+Median_L[index+4]*(5)+Median_L[index+5]*(5)+Median_L[index+6]*(5)+Median_L[index+7]*(10);

		Gaussian_R[index] = Median_R[index-7]*(10)+Median_R[index-6]*(5)+Median_R[index-5]*(5)+Median_R[index-4]*(5)+Median_R[index-3]*(5)+
				Median_R[index-2]*(-5)+Median_R[index-1]*(-15)+Median_R[index]*(-20)+Median_R[index+1]*(-15)+Median_R[index+2]*(-5)+
				Median_R[index+3]*(5)+Median_R[index+4]*(5)+Median_R[index+5]*(5)+Median_R[index+6]*(5)+Median_R[index+7]*(10);

		if((max_L <= Gaussian_L[index]) && Gaussian_L[index]>TRESHOLD) {
			max_L = Gaussian_L[index];
			pixel_L = index;
		}
		if((max_R <= Gaussian_R[index]) && Gaussian_R[index]>TRESHOLD) {
			max_R = Gaussian_R[index];
			pixel_R = index;
		}
	}
	return;
}



void Delay(int time) {
	int i=0;
	int ii=0;
	for(i=0; i<time; i++) {
		for(ii=0; ii<0xFFFF; ii++);
	}
}
