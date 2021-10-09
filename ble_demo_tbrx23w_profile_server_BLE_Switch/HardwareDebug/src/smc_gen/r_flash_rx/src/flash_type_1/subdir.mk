################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/smc_gen/r_flash_rx/src/flash_type_1/r_codeflash.c \
../src/smc_gen/r_flash_rx/src/flash_type_1/r_codeflash_extra.c \
../src/smc_gen/r_flash_rx/src/flash_type_1/r_dataflash.c \
../src/smc_gen/r_flash_rx/src/flash_type_1/r_flash_type1.c \
../src/smc_gen/r_flash_rx/src/flash_type_1/r_flash_utils.c 

COMPILER_OBJS += \
src/smc_gen/r_flash_rx/src/flash_type_1/r_codeflash.obj \
src/smc_gen/r_flash_rx/src/flash_type_1/r_codeflash_extra.obj \
src/smc_gen/r_flash_rx/src/flash_type_1/r_dataflash.obj \
src/smc_gen/r_flash_rx/src/flash_type_1/r_flash_type1.obj \
src/smc_gen/r_flash_rx/src/flash_type_1/r_flash_utils.obj 

# Each subdirectory must supply rules for building sources it contributes
src/smc_gen/r_flash_rx/src/flash_type_1/%.obj: ../src/smc_gen/r_flash_rx/src/flash_type_1/%.c 
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	@echo src\smc_gen\r_flash_rx\src\flash_type_1\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_flash_rx\src\flash_type_1\cSubCommand.tmp"
	ccrx -subcommand="src\smc_gen\r_flash_rx\src\flash_type_1\cSubCommand.tmp" "$<"
	@echo 'Finished Building: $<'
	@echo.

