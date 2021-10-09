################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/smc_gen/r_bsp/mcu/rx23w/mcu_clocks.c \
../src/smc_gen/r_bsp/mcu/rx23w/mcu_init.c \
../src/smc_gen/r_bsp/mcu/rx23w/mcu_interrupts.c \
../src/smc_gen/r_bsp/mcu/rx23w/r_bsp_clock.c \
../src/smc_gen/r_bsp/mcu/rx23w/r_bsp_vbatt.c \
../src/smc_gen/r_bsp/mcu/rx23w/vecttbl.c 

COMPILER_OBJS += \
src/smc_gen/r_bsp/mcu/rx23w/mcu_clocks.obj \
src/smc_gen/r_bsp/mcu/rx23w/mcu_init.obj \
src/smc_gen/r_bsp/mcu/rx23w/mcu_interrupts.obj \
src/smc_gen/r_bsp/mcu/rx23w/r_bsp_clock.obj \
src/smc_gen/r_bsp/mcu/rx23w/r_bsp_vbatt.obj \
src/smc_gen/r_bsp/mcu/rx23w/vecttbl.obj 

# Each subdirectory must supply rules for building sources it contributes
src/smc_gen/r_bsp/mcu/rx23w/%.obj: ../src/smc_gen/r_bsp/mcu/rx23w/%.c 
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	@echo src\smc_gen\r_bsp\mcu\rx23w\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_bsp\mcu\rx23w\cSubCommand.tmp"
	ccrx -subcommand="src\smc_gen\r_bsp\mcu\rx23w\cSubCommand.tmp" "$<"
	@echo 'Finished Building: $<'
	@echo.

