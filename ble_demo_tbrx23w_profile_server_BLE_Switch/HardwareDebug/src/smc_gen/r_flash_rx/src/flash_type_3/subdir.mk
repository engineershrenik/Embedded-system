################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/smc_gen/r_flash_rx/src/flash_type_3/r_flash_type3.c 

COMPILER_OBJS += \
src/smc_gen/r_flash_rx/src/flash_type_3/r_flash_type3.obj 

# Each subdirectory must supply rules for building sources it contributes
src/smc_gen/r_flash_rx/src/flash_type_3/%.obj: ../src/smc_gen/r_flash_rx/src/flash_type_3/%.c 
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	@echo src\smc_gen\r_flash_rx\src\flash_type_3\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_flash_rx\src\flash_type_3\cSubCommand.tmp"
	ccrx -subcommand="src\smc_gen\r_flash_rx\src\flash_type_3\cSubCommand.tmp" "$<"
	@echo 'Finished Building: $<'
	@echo.

