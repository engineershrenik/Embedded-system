################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/smc_gen/r_ble_rx23w/src/app_lib/logger/r_ble_logger.c 

COMPILER_OBJS += \
src/smc_gen/r_ble_rx23w/src/app_lib/logger/r_ble_logger.obj 

# Each subdirectory must supply rules for building sources it contributes
src/smc_gen/r_ble_rx23w/src/app_lib/logger/%.obj: ../src/smc_gen/r_ble_rx23w/src/app_lib/logger/%.c 
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	@echo src\smc_gen\r_ble_rx23w\src\app_lib\logger\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_ble_rx23w\src\app_lib\logger\cSubCommand.tmp"
	ccrx -subcommand="src\smc_gen\r_ble_rx23w\src\app_lib\logger\cSubCommand.tmp" "$<"
	@echo 'Finished Building: $<'
	@echo.

