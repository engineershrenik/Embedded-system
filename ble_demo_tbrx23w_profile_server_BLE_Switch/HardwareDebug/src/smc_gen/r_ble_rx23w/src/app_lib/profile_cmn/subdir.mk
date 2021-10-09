################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/smc_gen/r_ble_rx23w/src/app_lib/profile_cmn/r_ble_serv_common.c \
../src/smc_gen/r_ble_rx23w/src/app_lib/profile_cmn/r_ble_servc_if.c \
../src/smc_gen/r_ble_rx23w/src/app_lib/profile_cmn/r_ble_servs_if.c 

COMPILER_OBJS += \
src/smc_gen/r_ble_rx23w/src/app_lib/profile_cmn/r_ble_serv_common.obj \
src/smc_gen/r_ble_rx23w/src/app_lib/profile_cmn/r_ble_servc_if.obj \
src/smc_gen/r_ble_rx23w/src/app_lib/profile_cmn/r_ble_servs_if.obj 

# Each subdirectory must supply rules for building sources it contributes
src/smc_gen/r_ble_rx23w/src/app_lib/profile_cmn/%.obj: ../src/smc_gen/r_ble_rx23w/src/app_lib/profile_cmn/%.c 
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	@echo src\smc_gen\r_ble_rx23w\src\app_lib\profile_cmn\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_ble_rx23w\src\app_lib\profile_cmn\cSubCommand.tmp"
	ccrx -subcommand="src\smc_gen\r_ble_rx23w\src\app_lib\profile_cmn\cSubCommand.tmp" "$<"
	@echo 'Finished Building: $<'
	@echo.

