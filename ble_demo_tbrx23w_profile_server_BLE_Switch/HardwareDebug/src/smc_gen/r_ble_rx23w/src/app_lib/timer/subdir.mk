################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/smc_gen/r_ble_rx23w/src/app_lib/timer/r_ble_timer.c \
../src/smc_gen/r_ble_rx23w/src/app_lib/timer/r_ble_timer_rx23w.c 

COMPILER_OBJS += \
src/smc_gen/r_ble_rx23w/src/app_lib/timer/r_ble_timer.obj \
src/smc_gen/r_ble_rx23w/src/app_lib/timer/r_ble_timer_rx23w.obj 

# Each subdirectory must supply rules for building sources it contributes
src/smc_gen/r_ble_rx23w/src/app_lib/timer/%.obj: ../src/smc_gen/r_ble_rx23w/src/app_lib/timer/%.c 
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	@echo src\smc_gen\r_ble_rx23w\src\app_lib\timer\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_ble_rx23w\src\app_lib\timer\cSubCommand.tmp"
	ccrx -subcommand="src\smc_gen\r_ble_rx23w\src\app_lib\timer\cSubCommand.tmp" "$<"
	@echo 'Finished Building: $<'
	@echo.

