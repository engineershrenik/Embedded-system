################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/smc_gen/r_ble_rx23w/src/app_lib/cmd/r_ble_cmd.c \
../src/smc_gen/r_ble_rx23w/src/app_lib/cmd/r_ble_cmd_abs.c \
../src/smc_gen/r_ble_rx23w/src/app_lib/cmd/r_ble_cmd_sys.c \
../src/smc_gen/r_ble_rx23w/src/app_lib/cmd/r_ble_cmd_vs.c 

COMPILER_OBJS += \
src/smc_gen/r_ble_rx23w/src/app_lib/cmd/r_ble_cmd.obj \
src/smc_gen/r_ble_rx23w/src/app_lib/cmd/r_ble_cmd_abs.obj \
src/smc_gen/r_ble_rx23w/src/app_lib/cmd/r_ble_cmd_sys.obj \
src/smc_gen/r_ble_rx23w/src/app_lib/cmd/r_ble_cmd_vs.obj 

# Each subdirectory must supply rules for building sources it contributes
src/smc_gen/r_ble_rx23w/src/app_lib/cmd/%.obj: ../src/smc_gen/r_ble_rx23w/src/app_lib/cmd/%.c 
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	@echo src\smc_gen\r_ble_rx23w\src\app_lib\cmd\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_ble_rx23w\src\app_lib\cmd\cSubCommand.tmp"
	ccrx -subcommand="src\smc_gen\r_ble_rx23w\src\app_lib\cmd\cSubCommand.tmp" "$<"
	@echo 'Finished Building: $<'
	@echo.

