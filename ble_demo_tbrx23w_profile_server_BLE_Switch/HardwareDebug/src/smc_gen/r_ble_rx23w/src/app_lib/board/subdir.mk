################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/smc_gen/r_ble_rx23w/src/app_lib/board/r_ble_board.c 

COMPILER_OBJS += \
src/smc_gen/r_ble_rx23w/src/app_lib/board/r_ble_board.obj 

# Each subdirectory must supply rules for building sources it contributes
src/smc_gen/r_ble_rx23w/src/app_lib/board/%.obj: ../src/smc_gen/r_ble_rx23w/src/app_lib/board/%.c 
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	@echo src\smc_gen\r_ble_rx23w\src\app_lib\board\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_ble_rx23w\src\app_lib\board\cSubCommand.tmp"
	ccrx -subcommand="src\smc_gen\r_ble_rx23w\src\app_lib\board\cSubCommand.tmp" "$<"
	@echo 'Finished Building: $<'
	@echo.

