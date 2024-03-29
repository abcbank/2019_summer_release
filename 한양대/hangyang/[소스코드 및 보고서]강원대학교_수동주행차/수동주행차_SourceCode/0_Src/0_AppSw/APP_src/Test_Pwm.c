/*
 * Test_Pwm.c
 *
 *  Created on: 2015. 3. 24.
 *      Author: kimwayne
 */

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/
#include <stdio.h>
#include "Test_Pwm.h"
#include "Test_Irq.h"

/******************************************************************************/
/*-----------------------------------Macros-----------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*--------------------------------Enumerations--------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*-----------------------------Data Structures--------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*------------------------------Global variables------------------------------*/
/******************************************************************************/

App_GtmTomPwmHl GtmTomPwmHl; /**< \brief Demo information */
App_GtmTomPwmHl GtmTomPwmHlDCmotor; /**< \brief Demo information */
App_GtmTomPwmHl GtmTomPwmservo;
App_GtmTomTimer GtmTomTimer; /**< \brief Demo information */
App_GtmTomTimer GtmTomMsTimer; /**< \brief Demo information */
App_GtmTomPwmHl GtmTomValve; /**< \brief Demo information */

uint16	TestDuty;
unsigned int	Gpt_TimerOverflow;
unsigned int	Gpt_MsTimerOverflow;
/******************************************************************************/
/*-------------------------Function Prototypes--------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*------------------------Private Variables/Constants-------------------------*/
/******************************************************************************/

/******************************************************************************/
/*-------------------------Function Implementations---------------------------*/
/******************************************************************************/



void Delay_us(uint32 DelayTime)
{

	Gpt_TimerOverflow = 0;
    IfxGtm_Tom_Timer_run(&GtmTomTimer.drivers.timerOneMs);

    while(Gpt_TimerOverflow < DelayTime){

    	__nop();

    }

    IfxGtm_Tom_Timer_stop(&GtmTomTimer.drivers.timerOneMs);

}


/** \name Interrupts for Timer
 * \{ */

IFX_INTERRUPT(Gpt_Notification_SystemTick_1us, 0, ISR_PRIORITY_TIMER_1us);
void Gpt_Notification_SystemTick_1us(void)
{
    IfxCpu_enableInterrupts();

    IfxGtm_Tom_Timer_acknowledgeTimerIrq(&GtmTomTimer.drivers.timerOneMs);
    Gpt_TimerOverflow++;
}

void Delay_ms(uint32 DelayTime)
{

	Gpt_MsTimerOverflow = 0;
    IfxGtm_Tom_Timer_run(&GtmTomMsTimer.drivers.timerOneMs);

    while(Gpt_MsTimerOverflow < (DelayTime*10)){
    	__nop();

    }

    IfxGtm_Tom_Timer_stop(&GtmTomMsTimer.drivers.timerOneMs);

}

/** \name Interrupts for Timer
 * \{ */

IFX_INTERRUPT(Gpt_Notification_SystemTick_1ms, 0, ISR_PRIORITY_TIMER_1ms);
void Gpt_Notification_SystemTick_1ms(void)
{
    IfxCpu_enableInterrupts();

    IfxGtm_Tom_Timer_acknowledgeTimerIrq(&GtmTomMsTimer.drivers.timerOneMs);
    Gpt_MsTimerOverflow++;

}

void Pwm_MotorDutyAndDirectionControl(uint16 DutyCycle, uint8 Direction)
{
	/* set Inhibit pin high active */
	P02_OUT.B.P0 = 1;
	P00_OUT.B.P2 = 1;
	//P02_OUT.B.P2 = 1;
	//P33_OUT.B.P5 = 1;

	/* motor rev direction set up */
	switch(Direction)
	{
		case 0:          // CW
//			GTM_TOM0_CH9_SR0.B.SR0 = FREQ_20KHZ;
//			GTM_TOM0_CH9_SR1.B.SR1 = FREQ_20KHZ;
//			GTM_TOM0_CH10_SR0.B.SR0 = FREQ_20KHZ;
//			GTM_TOM0_CH10_SR1.B.SR1 =  FREQ_20KHZ-DutyCycle;
			Pwm_DutyUpdate(IfxGtm_TOM0_10_TOUT12_P00_3_OUT   ,DutyCycle);
			Pwm_DutyUpdate(IfxGtm_TOM0_9_TOUT1_P02_1_OUT  ,0);
			break;
		case 1:         // CCW
//			GTM_TOM0_CH9_SR0.B.SR0 = FREQ_20KHZ;
//			GTM_TOM0_CH9_SR1.B.SR1 = FREQ_20KHZ-DutyCycle;
//			GTM_TOM0_CH10_SR0.B.SR0 = FREQ_20KHZ;
//			GTM_TOM0_CH10_SR1.B.SR1 =  FREQ_20KHZ;
			Pwm_DutyUpdate(IfxGtm_TOM0_10_TOUT12_P00_3_OUT   ,0);
			Pwm_DutyUpdate(IfxGtm_TOM0_9_TOUT1_P02_1_OUT  ,DutyCycle);
			break;
		default:
			break;
	}

}

void Pwm_DutyUpdate(IfxGtm_Tom_ToutMap ChannelInfo, uint16 DutyCycle)
{
    IfxGtm_Tom_Timer *timer = &GtmTomPwmHlDCmotor.drivers.timer;
	uint16 CenterAlign, ComparePeriod, CompareDuty;
	Ifx_GTM_TOM_CH*   pTomCh;

	CenterAlign = DutyCycle;

	ComparePeriod = (FREQ_20KHZ+ CenterAlign)/2 ;
	CompareDuty   = (FREQ_20KHZ - CenterAlign)/2;

    /* Special handling due to GTM issue */
                      /* 100% duty cycle */
    if (CompareDuty == 0&& (CenterAlign != 4999))
    {
    	CompareDuty = 1;
    	ComparePeriod = ComparePeriod + 2;
    }

	IfxGtm_Tom_Timer_disableUpdate(timer);

	pTomCh = (Ifx_GTM_TOM_CH *)(0xF0108000+(0x800*(ChannelInfo.tom)) + 0x40*(ChannelInfo.channel));
	pTomCh->SR0.U = ComparePeriod;
	pTomCh->SR1.U = CompareDuty;

	IfxGtm_Tom_Timer_applyUpdate(timer);

} /* Pwm_MotorDrive */

void Pwm_ValveDutyUpdate(IfxGtm_Tom_ToutMap ChannelInfo,uint16 DutyCycle)
{
    IfxGtm_Tom_Timer *timer = &GtmTomValve.drivers.timer;
	Ifx_GTM_TOM_CH*   pTomCh;

	IfxGtm_Tom_Timer_disableUpdate(timer);

	pTomCh = (Ifx_GTM_TOM_CH *)(0xF0108000+(0x800*(ChannelInfo.tom)) + 0x40*(ChannelInfo.channel));
	pTomCh->SR0.U = FREQ_20KHZ;
	pTomCh->SR1.U = DutyCycle;

	IfxGtm_Tom_Timer_applyUpdate(timer);

} /* Pwm_MotorDrive */

void GtmTomPwmHl_initTimer_DCmotor(void)
{
    {   /* GTM TOM configuration */
        IfxGtm_Tom_Timer_Config timerConfig;
        IfxGtm_Tom_PwmHl_Config pwmHlConfig;

        IfxGtm_Tom_Timer_initConfig(&timerConfig, &MODULE_GTM);
        timerConfig.base.frequency                  = 20000;  //20Khz
//        timerConfig.base.isrPriority                = ISR_PRIORITY_TIMER;	//For Interrupt Enable
        timerConfig.base.isrPriority                = 0;
        timerConfig.base.isrProvider                = 0;
        timerConfig.base.minResolution              = (1.0 / timerConfig.base.frequency) / 1000;
        timerConfig.base.trigger.enabled            = FALSE;
        timerConfig.tom                             = IfxGtm_Tom_0;
        timerConfig.timerChannel                    = IfxGtm_Tom_Ch_0;
        timerConfig.clock                           = IfxGtm_Cmu_Clk_0;

        timerConfig.triggerOut                      = &IfxGtm_TOM0_0_TOUT18_P00_9_OUT;	//For Trigger Signal output port
        timerConfig.base.trigger.outputEnabled      = TRUE;
        timerConfig.base.trigger.enabled            = FALSE;	//For Trigger Signal Check via Oscilloscope
        timerConfig.base.trigger.triggerPoint       = 2500;
        timerConfig.base.trigger.risingEdgeAtPeriod = TRUE;

        IfxGtm_Tom_Timer_init(&GtmTomPwmHlDCmotor.drivers.timer, &timerConfig);


        IfxGtm_Tom_ToutMapP ccx[2]   = {&IfxGtm_TOM0_9_TOUT1_P02_1_OUT,
        								&IfxGtm_TOM0_10_TOUT12_P00_3_OUT
        								};

        IfxGtm_Tom_ToutMapP coutx[2] = {&IfxGtm_TOM0_11_TOUT3_P02_3_OUT,
        		                        &IfxGtm_TOM0_2_TOUT28_P33_6_OUT
        		                        };

        pwmHlConfig.timer                 = &GtmTomPwmHlDCmotor.drivers.timer;
        pwmHlConfig.tom                   = timerConfig.tom;
//      pwmHlConfig.base.deadtime         = 1e-8;
//      pwmHlConfig.base.minPulse         = 0;
        pwmHlConfig.base.channelCount     = 2;
        pwmHlConfig.base.emergencyEnabled = FALSE;
        pwmHlConfig.base.outputMode       = IfxPort_OutputMode_pushPull;
        pwmHlConfig.base.outputDriver     = IfxPort_PadDriver_cmosAutomotiveSpeed1;
        pwmHlConfig.base.ccxActiveState   = Ifx_ActiveState_high;
        pwmHlConfig.base.coutxActiveState = Ifx_ActiveState_low;
        pwmHlConfig.ccx                   = ccx;
        pwmHlConfig.coutx                 = coutx;

        IfxGtm_Tom_PwmHl_init(&GtmTomPwmHlDCmotor.drivers.pwm, &pwmHlConfig);

        GTM_TOM0_TGC0_OUTEN_CTRL.U = 0x0000AAAA;
        GTM_TOM0_TGC0_OUTEN_STAT.U = 0x0000AAAA;
        GTM_TOM0_TGC0_ENDIS_CTRL.U = 0x0000AAAA;
        GTM_TOM0_TGC0_ENDIS_STAT.U = 0x0000AAAA;

        GTM_TOM0_TGC1_OUTEN_STAT.U = 0x0000AAAA;
        GTM_TOM0_TGC1_OUTEN_CTRL.U = 0x0000AAAA;
        GTM_TOM0_TGC1_ENDIS_CTRL.U = 0x0000AAAA;
        GTM_TOM0_TGC1_ENDIS_STAT.U = 0x0000AAAA;

        GTM_TOM0_TGC0_GLB_CTRL.U = 0xAAAA0000;
        GTM_TOM0_TGC1_GLB_CTRL.U = 0xAAAA0000;

     //   IfxGtm_Tom_Timer_run(&GtmTomPwmHlDCmotor.drivers.timer);

    }
}

void Pwm_servo(uint16 DutyCycle)
{

	Pwm_DutyUpdate_Servo(IfxGtm_TOM0_7_TOUT32_P33_10_OUT   ,DutyCycle);
}
void Pwm_DutyUpdate_Servo(IfxGtm_Tom_ToutMap ChannelInfo, uint16 DutyCycle)
{
    IfxGtm_Tom_Timer *timer = &GtmTomPwmservo.drivers.timer;
	uint32 ComparePeriod, CompareDuty;
	Ifx_GTM_TOM_CH*   pTomCh;

	ComparePeriod = 5859 ; //20ms
	CompareDuty   = DutyCycle;

	IfxGtm_Tom_Timer_disableUpdate(timer);

	pTomCh = (Ifx_GTM_TOM_CH *)(0xF0108000+(0x800*(ChannelInfo.tom)) + 0x40*(ChannelInfo.channel));
	pTomCh->SR0.U = ComparePeriod;
	pTomCh->SR1.U = CompareDuty;

	IfxGtm_Tom_Timer_applyUpdate(timer);

}
void Gtm_servo_init(void)
{
    {   /* GTM TOM configuration */
        IfxGtm_Tom_Timer_Config servoConfig;
        IfxGtm_Tom_PwmHl_Config pwmSTConfig;

        IfxGtm_Tom_Timer_initConfig(&servoConfig, &MODULE_GTM);
        servoConfig.base.frequency       = 20000;
        servoConfig.base.isrPriority     = 0;
        servoConfig.base.isrProvider     = 0;
        servoConfig.base.minResolution   = (1.0 / servoConfig.base.frequency) / 1000;
        servoConfig.base.trigger.enabled = FALSE;

        servoConfig.tom                  = IfxGtm_Tom_0;
        servoConfig.timerChannel         = IfxGtm_Tom_Ch_3;
        servoConfig.clock                = IfxGtm_Cmu_Fxclk_2;

        servoConfig.triggerOut                      = &IfxGtm_TOM0_3_TOUT21_P00_12_OUT;
        servoConfig.base.trigger.outputEnabled      = TRUE;
        servoConfig.base.trigger.enabled            = FALSE;	//For Trigger Signal Check via Oscilloscope
        servoConfig.base.trigger.triggerPoint       = 2500;
        servoConfig.base.trigger.risingEdgeAtPeriod = TRUE;

        IfxGtm_Tom_Timer_init(&GtmTomPwmservo.drivers.timer, &servoConfig);

         IfxGtm_Tom_ToutMapP ccx[2]   = {&IfxGtm_TOM0_7_TOUT32_P33_10_OUT,
         								&IfxGtm_TOM0_6_TOUT29_P33_7_OUT,
         								};

         IfxGtm_Tom_ToutMapP coutx[2] = {&IfxGtm_TOM0_11_TOUT3_P02_3_OUT,
         		                        &IfxGtm_TOM0_2_TOUT33_P33_11_OUT,
         		                        };

         pwmSTConfig.timer                 = &GtmTomPwmservo.drivers.timer;
         pwmSTConfig.tom                   = servoConfig.tom;
 //      pwmHlConfig.base.deadtime         = 1e-8;
 //      pwmHlConfig.base.minPulse         = 0;
         pwmSTConfig.base.channelCount     = 2;
         pwmSTConfig.base.emergencyEnabled = FALSE;
         pwmSTConfig.base.outputMode       = IfxPort_OutputMode_pushPull;
         pwmSTConfig.base.outputDriver     = IfxPort_PadDriver_cmosAutomotiveSpeed1;
         pwmSTConfig.base.ccxActiveState   = Ifx_ActiveState_low;
         pwmSTConfig.base.coutxActiveState = Ifx_ActiveState_high;
         pwmSTConfig.ccx                   = ccx;
         pwmSTConfig.coutx                 = coutx;

         IfxGtm_Tom_PwmHl_init(&GtmTomPwmservo.drivers.pwm, &pwmSTConfig);
         GTM_TOM0_CH7_CTRL.B.RST_CCU0=0;

    }
}
void GtmTomTimer_initTimer(void)
{
    {   /* GTM TOM configuration */
        IfxGtm_Tom_Timer_Config timerConfig;
        IfxGtm_Tom_Timer_initConfig(&timerConfig, &MODULE_GTM);
        timerConfig.base.frequency       = 100000;
        timerConfig.base.isrPriority     = ISR_PRIORITY_TIMER_1us;
        timerConfig.base.isrProvider     = 0;
        timerConfig.base.minResolution   = (1.0 / timerConfig.base.frequency) / 1000;
        timerConfig.base.trigger.enabled = FALSE;

        //IfxGtm_TOM1_0_TOUT32_P33_10_OUT
        timerConfig.tom                  = IfxGtm_Tom_1;
        timerConfig.timerChannel         = IfxGtm_Tom_Ch_0;
        timerConfig.clock                = IfxGtm_Cmu_Fxclk_0;

        IfxGtm_Tom_Timer_init(&GtmTomTimer.drivers.timerOneMs, &timerConfig);
        GTM_TOM1_CH0_SR0.B.SR0 = 	100; //1500;			// 1500 -> 1.5ms
        IfxGtm_Tom_Timer_run(&GtmTomTimer.drivers.timerOneMs);

    }
}

void GtmTomTimer_initMsTimer(void)
{
    {   /* GTM TOM configuration */
        IfxGtm_Tom_Timer_Config MstimerConfig;
        IfxGtm_Tom_Timer_initConfig(&MstimerConfig, &MODULE_GTM);
        MstimerConfig.base.frequency       = 100000;
        MstimerConfig.base.isrPriority     = ISR_PRIORITY_TIMER_1ms;
        MstimerConfig.base.isrProvider     = 0;
        MstimerConfig.base.minResolution   = (1.0 / MstimerConfig.base.frequency) / 1000;
        MstimerConfig.base.trigger.enabled = FALSE;

        MstimerConfig.tom                  = IfxGtm_Tom_0;
        MstimerConfig.timerChannel         = IfxGtm_Tom_Ch_14;
        MstimerConfig.clock                = IfxGtm_Cmu_Fxclk_0;

        IfxGtm_Tom_Timer_init(&GtmTomMsTimer.drivers.timerOneMs, &MstimerConfig);
        GTM_TOM0_CH14_SR0.B.SR0 = 	10000; //1500;			// 1500 -> 1.5ms
        IfxGtm_Tom_Timer_run(&GtmTomMsTimer.drivers.timerOneMs);

    }

}

uint32 Gpt_GetTimeElapsed(void)
{

return	GTM_TOM1_CH0_CN0.B.CN0;

}

void GtmTomValve_init(void){


    IfxGtm_Tom_Timer_Config timerConfig;
   // IfxGtm_Tom_PwmHl_Config pwmHlConfig;

    IfxGtm_Tom_Timer_initConfig(&timerConfig, &MODULE_GTM);
    timerConfig.base.frequency                  = 20000;  //20Khz
   // timerConfig.base.isrPriority                = ISR_PRIORITY_TIMER;	//For Interrupt Enable
    timerConfig.base.isrPriority                = 0;
    timerConfig.base.isrProvider                = 0;
    timerConfig.base.minResolution              = (1.0 / timerConfig.base.frequency) / 1000;
    timerConfig.tom                             = IfxGtm_Tom_0;
    timerConfig.timerChannel                    = IfxGtm_Tom_Ch_0;
    timerConfig.clock                           = IfxGtm_Cmu_Clk_0;
    timerConfig.triggerOut                      = &IfxGtm_TOM0_0_TOUT18_P00_9_OUT;
    timerConfig.base.trigger.outputEnabled      = TRUE;
    timerConfig.base.trigger.enabled            = FALSE;
    timerConfig.base.trigger.triggerPoint       = 2500;
    timerConfig.base.trigger.risingEdgeAtPeriod = TRUE;

    IfxGtm_Tom_Timer_init(&GtmTomValve.drivers.timer, &timerConfig);
    timerConfig.base.trigger.triggerPoint       = 0;

    timerConfig.base.trigger.enabled            = TRUE;	//For Trigger Signal Check via Oscilloscope

//    timerConfig.tom                             = IfxGtm_Tom_2;
//    timerConfig.timerChannel                    = IfxGtm_Tom_Ch_1;
//    timerConfig.triggerOut                      = &IfxGtm_TOM2_1_TOUT54_P21_3_OUT;                                 //&IfxGtm_TOM0_9_TOUT11_P00_2_OUT,
//    IfxGtm_Tom_Timer_init(&GtmTomValve.drivers.timer, &timerConfig);                                               //&IfxGtm_TOM0_10_TOUT12_P00_3_OUT,
                                                                                                                     //&IfxGtm_TOM1_8_TOUT0_P02_0_OUT,
    timerConfig.tom                             = IfxGtm_Tom_0;                                                      //&IfxGtm_TOM1_10_TOUT2_P02_2_OUT
    timerConfig.timerChannel                    = IfxGtm_Tom_Ch_9;                                                   //};
    timerConfig.triggerOut                      = &IfxGtm_TOM0_9_TOUT1_P02_1_OUT;                                   //
    IfxGtm_Tom_Timer_init(&GtmTomValve.drivers.timer, &timerConfig);                                                 //&IfxGtm_TOM0_1_TOUT27_P33_5_OUT,
                                                                                                                     //&IfxGtm_TOM0_2_TOUT28_P33_6_OUT,
                                                                                                                     //&IfxGtm_TOM1_9_TOUT1_P02_1_OUT,
    timerConfig.tom                             = IfxGtm_Tom_0;                                                      //&IfxGtm_TOM1_11_TOUT3_P02_3_OUT
    timerConfig.timerChannel                    = IfxGtm_Tom_Ch_10;
    timerConfig.triggerOut                      = &IfxGtm_TOM0_10_TOUT12_P00_3_OUT;
    IfxGtm_Tom_Timer_init(&GtmTomValve.drivers.timer, &timerConfig);


    IfxGtm_Tom_Timer_run(&GtmTomValve.drivers.timer);

}

/** \brief Demo init API
 *
 * This function is called from main during initialization phase
 */

void Pwm_Initialization(void)
{
    /* disable interrupts */
    boolean  interruptState = IfxCpu_disableInterrupts();

    /** - GTM clocks */
    Ifx_GTM *gtm = &MODULE_GTM;
    GtmTomPwmHl.info.gtmFreq = IfxGtm_Cmu_getModuleFrequency(gtm);
    IfxGtm_enable(gtm);

    /* Set the global clock frequencies */
    IfxGtm_Cmu_setGclkFrequency(gtm, GtmTomPwmHl.info.gtmFreq);
    GtmTomPwmHl.info.gtmGclkFreq = IfxGtm_Cmu_getGclkFrequency(gtm);

    //GTM_CMU_CLK_2_CTRL.B.CLK_CNT = 0x100;
   IfxGtm_Cmu_setClkFrequency(gtm, IfxGtm_Cmu_Clk_0,1000000);

    GtmTomPwmHl.info.gtmCmuClk0Freq = IfxGtm_Cmu_getClkFrequency(gtm, IfxGtm_Cmu_Clk_0, TRUE);
    GtmTomPwmHl.info.stateDeadline  = now();

    /** - Initialise the DC_MOTOR part */
    GtmTomPwmHl_initTimer_DCmotor();

    /** - Initialise the DC_MOTOR part */
    Gtm_servo_init();


    /** - Initialise the GTM part */
    GtmTomTimer_initTimer();
    /** - Initialise the GTM part */
    GtmTomTimer_initMsTimer();

    /* enable interrupts again */
    IfxCpu_restoreInterrupts(interruptState);

    IfxGtm_Cmu_enableClocks(gtm, IFXGTM_CMU_CLKEN_FXCLK |IFXGTM_CMU_CLKEN_CLK0);

}
