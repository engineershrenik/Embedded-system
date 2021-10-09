################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/smc_gen/r_ble_rx23w/src/app_lib/sec_data/r_ble_sec_data.c 

COMPILER_OBJS += \
src/smc_gen/r_ble_rx23w/src/app_lib/sec_data/r_ble_sec_data.obj 

# Each subdirectory must supply rules for building sources it contributes
src/smc_gen/r_ble_rx23w/src/app_lib/sec_data/%.obj: ../src/smc_gen/r_ble_rx23w/src/app_lib/sec_data/%.c 
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	@echo src\smc_gen\r_ble_rx23w\src\app_lib\sec_data\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_ble_rx23w\src\app_lib\sec_data\cSubCommand.tmp"
	ccrx -subcommand="src\smc_gen\r_ble_rx23w\src\app_lib\sec_data\cSubCommand.tmp" "$<"
	@echo 'Finished Building: $<'
	@echo.

