################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../0_Src/0_AppSw/APP_src/Test_Adc.c \
../0_Src/0_AppSw/APP_src/Test_Dio.c \
../0_Src/0_AppSw/APP_src/Test_Encoder.c \
../0_Src/0_AppSw/APP_src/Test_ModuleInit.c \
../0_Src/0_AppSw/APP_src/Test_Pwm.c 

OBJS += \
./0_Src/0_AppSw/APP_src/Test_Adc.o \
./0_Src/0_AppSw/APP_src/Test_Dio.o \
./0_Src/0_AppSw/APP_src/Test_Encoder.o \
./0_Src/0_AppSw/APP_src/Test_ModuleInit.o \
./0_Src/0_AppSw/APP_src/Test_Pwm.o 

C_DEPS += \
./0_Src/0_AppSw/APP_src/Test_Adc.d \
./0_Src/0_AppSw/APP_src/Test_Dio.d \
./0_Src/0_AppSw/APP_src/Test_Encoder.d \
./0_Src/0_AppSw/APP_src/Test_ModuleInit.d \
./0_Src/0_AppSw/APP_src/Test_Pwm.d 


# Each subdirectory must supply rules for building sources it contributes
0_Src/0_AppSw/APP_src/%.o: ../0_Src/0_AppSw/APP_src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TriCore C Compiler'
	"$(TRICORE_TOOLS)/bin/tricore-gcc" -c -IC:/Users/kimwayne/HanyangUniv_Project/TC237L_DemoPack_HanyangUniv/h -I"C:\Users\Administrator\Desktop\7.11최종(UART_X)\TC237L_DemoPack_HanyangUniv_N\0_Src\4_McHal\Tricore\Multican" -I"C:\Users\Administrator\Desktop\7.11최종(UART_X)\TC237L_DemoPack_HanyangUniv_N\0_Src\4_McHal\Tricore\Multican\Can" -I"C:\Users\Administrator\Desktop\7.11최종(UART_X)\TC237L_DemoPack_HanyangUniv_N\0_Src\4_McHal\Tricore\Multican\Std" -I"C:\Users\Administrator\Desktop\7.11최종(UART_X)\TC237L_DemoPack_HanyangUniv_N\0_Src\4_McHal\Tricore\_Impl" -I"C:\Users\Administrator\Desktop\7.11최종(UART_X)\TC237L_DemoPack_HanyangUniv_N\0_Src\4_McHal\Tricore\_Lib\DataHandling" -I"C:\Users\Administrator\Desktop\7.11최종(UART_X)\TC237L_DemoPack_HanyangUniv_N\0_Src\4_McHal\Tricore\_Lib\InternalMux" -I"C:\Users\Administrator\Desktop\7.11최종(UART_X)\TC237L_DemoPack_HanyangUniv_N\0_Src\4_McHal\Tricore\_PinMap" -I"C:\Users\Administrator\Desktop\7.11최종(UART_X)\TC237L_DemoPack_HanyangUniv_N\0_Src\4_McHal\Tricore\Asclin\Asc" -I"C:\Users\Administrator\Desktop\7.11최종(UART_X)\TC237L_DemoPack_HanyangUniv_N\0_Src\4_McHal\Tricore\Asclin\Lin" -I"C:\Users\Administrator\Desktop\7.11최종(UART_X)\TC237L_DemoPack_HanyangUniv_N\0_Src\4_McHal\Tricore\Asclin\Spi" -I"C:\Users\Administrator\Desktop\7.11최종(UART_X)\TC237L_DemoPack_HanyangUniv_N\0_Src\4_McHal\Tricore\Asclin\Std" -I"C:\Users\Administrator\Desktop\7.11최종(UART_X)\TC237L_DemoPack_HanyangUniv_N\0_Src\4_McHal\Tricore\Cpu\CStart" -I"C:\Users\Administrator\Desktop\7.11최종(UART_X)\TC237L_DemoPack_HanyangUniv_N\0_Src\4_McHal\Tricore\Cpu\Irq" -I"C:\Users\Administrator\Desktop\7.11최종(UART_X)\TC237L_DemoPack_HanyangUniv_N\0_Src\4_McHal\Tricore\Cpu\Std" -I"C:\Users\Administrator\Desktop\7.11최종(UART_X)\TC237L_DemoPack_HanyangUniv_N\0_Src\4_McHal\Tricore\Cpu\Trap" -I"C:\Users\Administrator\Desktop\7.11최종(UART_X)\TC237L_DemoPack_HanyangUniv_N\0_Src\4_McHal\Tricore\Dma\Dma" -I"C:\Users\Administrator\Desktop\7.11최종(UART_X)\TC237L_DemoPack_HanyangUniv_N\0_Src\4_McHal\Tricore\Dma\Std" -I"C:\Users\Administrator\Desktop\7.11최종(UART_X)\TC237L_DemoPack_HanyangUniv_N\0_Src\4_McHal\Tricore\Gtm\Std" -I"C:\Users\Administrator\Desktop\7.11최종(UART_X)\TC237L_DemoPack_HanyangUniv_N\0_Src\4_McHal\Tricore\Gtm\Tom" -I"C:\Users\Administrator\Desktop\7.11최종(UART_X)\TC237L_DemoPack_HanyangUniv_N\0_Src\4_McHal\Tricore\Gtm\Trig" -I"C:\Users\Administrator\Desktop\7.11최종(UART_X)\TC237L_DemoPack_HanyangUniv_N\0_Src\4_McHal\Tricore\Port\Io" -I"C:\Users\Administrator\Desktop\7.11최종(UART_X)\TC237L_DemoPack_HanyangUniv_N\0_Src\4_McHal\Tricore\Port\Std" -I"C:\Users\Administrator\Desktop\7.11최종(UART_X)\TC237L_DemoPack_HanyangUniv_N\0_Src\4_McHal\Tricore\Scu\Std" -I"C:\Users\Administrator\Desktop\7.11최종(UART_X)\TC237L_DemoPack_HanyangUniv_N\0_Src\4_McHal\Tricore\Src\Std" -I"C:\Users\Administrator\Desktop\7.11최종(UART_X)\TC237L_DemoPack_HanyangUniv_N\0_Src\4_McHal\Tricore\Stm\Std" -I"C:\Users\Administrator\Desktop\7.11최종(UART_X)\TC237L_DemoPack_HanyangUniv_N\0_Src\4_McHal\Tricore\Vadc\Adc" -I"C:\Users\Administrator\Desktop\7.11최종(UART_X)\TC237L_DemoPack_HanyangUniv_N\0_Src\4_McHal\Tricore\Vadc\Std" -I"C:\Users\Administrator\Desktop\7.11최종(UART_X)\TC237L_DemoPack_HanyangUniv_N\0_Src\4_McHal\Tricore" -I"C:\Users\Administrator\Desktop\7.11최종(UART_X)\TC237L_DemoPack_HanyangUniv_N\0_Src\4_McHal\Tricore\_Reg" -I"C:\Users\Administrator\Desktop\7.11최종(UART_X)\TC237L_DemoPack_HanyangUniv_N\0_Src\1_SrvSw\Config\Common" -I"C:\Users\Administrator\Desktop\7.11최종(UART_X)\TC237L_DemoPack_HanyangUniv_N\0_Src\1_SrvSw" -I"C:\Users\Administrator\Desktop\7.11최종(UART_X)\TC237L_DemoPack_HanyangUniv_N\0_Src\4_McHal" -I"C:\Users\Administrator\Desktop\7.11최종(UART_X)\TC237L_DemoPack_HanyangUniv_N\0_Src\1_SrvSw\Tricore\Compilers" -I"C:\Users\Administrator\Desktop\7.11최종(UART_X)\TC237L_DemoPack_HanyangUniv_N\0_Src\0_AppSw\APP_inc" -I"C:\Users\Administrator\Desktop\7.11최종(UART_X)\TC237L_DemoPack_HanyangUniv_N\0_Src\1_SrvSw\_Utilities" -I"C:\Users\Administrator\Desktop\7.11최종(UART_X)\TC237L_DemoPack_HanyangUniv_N\0_Src\1_SrvSw\Config" -I"C:\Users\Administrator\Desktop\7.11최종(UART_X)\TC237L_DemoPack_HanyangUniv_N\0_Src\1_SrvSw\If" -I"C:\Users\Administrator\Desktop\7.11최종(UART_X)\TC237L_DemoPack_HanyangUniv_N\0_Src\1_SrvSw\StdIf" -I"C:\Users\Administrator\Desktop\7.11최종(UART_X)\TC237L_DemoPack_HanyangUniv_N\0_Src\1_SrvSw\SysSe" -I"C:\Users\Administrator\Desktop\7.11최종(UART_X)\TC237L_DemoPack_HanyangUniv_N\0_Src\1_SrvSw\Tricore" -I"C:\Users\Administrator\Desktop\7.11최종(UART_X)\TC237L_DemoPack_HanyangUniv_N\0_Src\4_McHal\Tricore" -fno-common -O2 -fgcse-after-reload -ffast-math -funswitch-loops -fpredictive-commoning -ftree-vectorize -fipa-cp-clone -fpeel-loops -fmove-loop-invariants -frename-registers -fira-algorithm=priority -g3 -W -Wall -Wextra -Wdiv-by-zero -Warray-bounds -Wcast-align -Wignored-qualifiers -Wformat -Wformat-security -DAPPKIT_TC237TFT -fshort-double -mcpu=tc23xx -mversion-info -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


