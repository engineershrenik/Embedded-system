################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/smc_gen/r_ble_rx23w/src/platform/r_ble_pf_configs.c \
../src/smc_gen/r_ble_rx23w/src/platform/r_ble_pf_functions.c \
../src/smc_gen/r_ble_rx23w/src/platform/r_ble_pf_lowpower.c 

COMPILER_OBJS += \
src/smc_gen/r_ble_rx23w/src/platform/r_ble_pf_configs.obj \
src/smc_gen/r_ble_rx23w/src/platform/r_ble_pf_functions.obj \
src/smc_gen/r_ble_rx23w/src/platform/r_ble_pf_lowpower.obj 

# Each subdirectory must supply rules for building sources it contributes
src/smc_gen/r_ble_rx23w/src/platform/%.obj: ../src/smc_gen/r_ble_rx23w/src/platform/%.c 
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	@echo src\smc_gen\r_ble_rx23w\src\platform\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_ble_rx23w\src\platform\cSubCommand.tmp"
	ccrx -subcommand="src\smc_gen\r_ble_rx23w\src\platform\cSubCommand.tmp" "$<"
	@echo 'Finished Building: $<'
	@echo.

