################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/smc_gen/Config_BLE_PROFILE/app_main.c \
../src/smc_gen/Config_BLE_PROFILE/gatt_db.c \
../src/smc_gen/Config_BLE_PROFILE/r_ble_gapc.c \
../src/smc_gen/Config_BLE_PROFILE/r_ble_gaps.c \
../src/smc_gen/Config_BLE_PROFILE/r_ble_gats.c \
../src/smc_gen/Config_BLE_PROFILE/r_ble_lss.c 

COMPILER_OBJS += \
src/smc_gen/Config_BLE_PROFILE/app_main.obj \
src/smc_gen/Config_BLE_PROFILE/gatt_db.obj \
src/smc_gen/Config_BLE_PROFILE/r_ble_gapc.obj \
src/smc_gen/Config_BLE_PROFILE/r_ble_gaps.obj \
src/smc_gen/Config_BLE_PROFILE/r_ble_gats.obj \
src/smc_gen/Config_BLE_PROFILE/r_ble_lss.obj 

# Each subdirectory must supply rules for building sources it contributes
src/smc_gen/Config_BLE_PROFILE/%.obj: ../src/smc_gen/Config_BLE_PROFILE/%.c 
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	@echo src\smc_gen\Config_BLE_PROFILE\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\Config_BLE_PROFILE\cSubCommand.tmp"
	ccrx -subcommand="src\smc_gen\Config_BLE_PROFILE\cSubCommand.tmp" "$<"
	@echo 'Finished Building: $<'
	@echo.

