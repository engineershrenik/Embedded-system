################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/smc_gen/r_bsp/mcu/all/dbsct.c \
../src/smc_gen/r_bsp/mcu/all/lowlvl.c \
../src/smc_gen/r_bsp/mcu/all/lowsrc.c \
../src/smc_gen/r_bsp/mcu/all/mcu_locks.c \
../src/smc_gen/r_bsp/mcu/all/r_bsp_common.c \
../src/smc_gen/r_bsp/mcu/all/r_bsp_cpu.c \
../src/smc_gen/r_bsp/mcu/all/r_bsp_interrupts.c \
../src/smc_gen/r_bsp/mcu/all/r_bsp_locking.c \
../src/smc_gen/r_bsp/mcu/all/r_bsp_mcu_startup.c \
../src/smc_gen/r_bsp/mcu/all/r_bsp_software_interrupt.c \
../src/smc_gen/r_bsp/mcu/all/r_rx_intrinsic_functions.c \
../src/smc_gen/r_bsp/mcu/all/resetprg.c \
../src/smc_gen/r_bsp/mcu/all/sbrk.c 

COMPILER_OBJS += \
src/smc_gen/r_bsp/mcu/all/dbsct.obj \
src/smc_gen/r_bsp/mcu/all/lowlvl.obj \
src/smc_gen/r_bsp/mcu/all/lowsrc.obj \
src/smc_gen/r_bsp/mcu/all/mcu_locks.obj \
src/smc_gen/r_bsp/mcu/all/r_bsp_common.obj \
src/smc_gen/r_bsp/mcu/all/r_bsp_cpu.obj \
src/smc_gen/r_bsp/mcu/all/r_bsp_interrupts.obj \
src/smc_gen/r_bsp/mcu/all/r_bsp_locking.obj \
src/smc_gen/r_bsp/mcu/all/r_bsp_mcu_startup.obj \
src/smc_gen/r_bsp/mcu/all/r_bsp_software_interrupt.obj \
src/smc_gen/r_bsp/mcu/all/r_rx_intrinsic_functions.obj \
src/smc_gen/r_bsp/mcu/all/resetprg.obj \
src/smc_gen/r_bsp/mcu/all/sbrk.obj 

# Each subdirectory must supply rules for building sources it contributes
src/smc_gen/r_bsp/mcu/all/%.obj: ../src/smc_gen/r_bsp/mcu/all/%.c 
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	@echo src\smc_gen\r_bsp\mcu\all\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_bsp\mcu\all\cSubCommand.tmp"
	ccrx -subcommand="src\smc_gen\r_bsp\mcu\all\cSubCommand.tmp" "$<"
	@echo 'Finished Building: $<'
	@echo.

