################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/smc_gen/r_gpio_rx/src/targets/rx23w/r_gpio_rx23w.c 

COMPILER_OBJS += \
src/smc_gen/r_gpio_rx/src/targets/rx23w/r_gpio_rx23w.obj 

# Each subdirectory must supply rules for building sources it contributes
src/smc_gen/r_gpio_rx/src/targets/rx23w/%.obj: ../src/smc_gen/r_gpio_rx/src/targets/rx23w/%.c 
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	@echo src\smc_gen\r_gpio_rx\src\targets\rx23w\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_gpio_rx\src\targets\rx23w\cSubCommand.tmp"
	ccrx -subcommand="src\smc_gen\r_gpio_rx\src\targets\rx23w\cSubCommand.tmp" "$<"
	@echo 'Finished Building: $<'
	@echo.

