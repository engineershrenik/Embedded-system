################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/ble_demo_tbrx23w_profile_server.c 

COMPILER_OBJS += \
src/ble_demo_tbrx23w_profile_server.obj 

# Each subdirectory must supply rules for building sources it contributes
src/%.obj: ../src/%.c 
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	@echo src\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\cSubCommand.tmp"
	ccrx -subcommand="src\cSubCommand.tmp" "$<"
	@echo 'Finished Building: $<'
	@echo.

