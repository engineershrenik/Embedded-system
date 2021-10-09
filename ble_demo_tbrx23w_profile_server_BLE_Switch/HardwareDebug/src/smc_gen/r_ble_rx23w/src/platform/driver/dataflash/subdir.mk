################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/smc_gen/r_ble_rx23w/src/platform/driver/dataflash/r_ble_dataflash.c 

COMPILER_OBJS += \
src/smc_gen/r_ble_rx23w/src/platform/driver/dataflash/r_ble_dataflash.obj 

# Each subdirectory must supply rules for building sources it contributes
src/smc_gen/r_ble_rx23w/src/platform/driver/dataflash/%.obj: ../src/smc_gen/r_ble_rx23w/src/platform/driver/dataflash/%.c 
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	@echo src\smc_gen\r_ble_rx23w\src\platform\driver\dataflash\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_ble_rx23w\src\platform\driver\dataflash\cSubCommand.tmp"
	ccrx -subcommand="src\smc_gen\r_ble_rx23w\src\platform\driver\dataflash\cSubCommand.tmp" "$<"
	@echo 'Finished Building: $<'
	@echo.

