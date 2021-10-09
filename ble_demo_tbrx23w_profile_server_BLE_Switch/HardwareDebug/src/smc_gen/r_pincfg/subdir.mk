################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/smc_gen/r_pincfg/Pin.c \
../src/smc_gen/r_pincfg/r_irq_rx_pinset.c \
../src/smc_gen/r_pincfg/r_sci_rx_pinset.c 

COMPILER_OBJS += \
src/smc_gen/r_pincfg/Pin.obj \
src/smc_gen/r_pincfg/r_irq_rx_pinset.obj \
src/smc_gen/r_pincfg/r_sci_rx_pinset.obj 

# Each subdirectory must supply rules for building sources it contributes
src/smc_gen/r_pincfg/%.obj: ../src/smc_gen/r_pincfg/%.c 
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	@echo src\smc_gen\r_pincfg\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_pincfg\cSubCommand.tmp"
	ccrx -subcommand="src\smc_gen\r_pincfg\cSubCommand.tmp" "$<"
	@echo 'Finished Building: $<'
	@echo.

