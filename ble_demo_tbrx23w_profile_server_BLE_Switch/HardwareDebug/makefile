################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include makefile.init

RM := rm -rf *.sni *.dbg *.lst *.lis *.lpp *.map *.x *.lbp *.bls *.libelf *.rel *.lbk *.abs *.mi *.jmp *.fsy *.ud *.udm 1st/*.abs 1st/*.jmp 1st/*.fsy

# All of the sources participating in the build are defined here
-include sources.mk
-include src/smc_gen/r_ble_rx23w/src/app_lib/board/subdir.mk
-include src/smc_gen/r_flash_rx/src/flash_type_4/subdir.mk
-include src/smc_gen/r_ble_rx23w/src/app_lib/timer/subdir.mk
-include src/smc_gen/r_flash_rx/src/subdir.mk
-include src/smc_gen/r_gpio_rx/src/subdir.mk
-include src/smc_gen/r_ble_rx23w/src/app_lib/abs/subdir.mk
-include src/smc_gen/r_ble_rx23w/src/app_lib/cmd/subdir.mk
-include src/smc_gen/r_bsp/board/generic_rx23w/subdir.mk
-include src/smc_gen/Config_BLE_PROFILE/subdir.mk
-include src/smc_gen/r_ble_rx23w/src/platform/subdir.mk
-include src/smc_gen/r_cmt_rx/src/subdir.mk
-include src/smc_gen/r_ble_rx23w/src/app_lib/rtos/subdir.mk
-include src/smc_gen/r_lpc_rx/src/targets/rx23w/subdir.mk
-include src/smc_gen/r_flash_rx/src/flash_type_3/subdir.mk
-include src/smc_gen/r_ble_rx23w/src/app_lib/sec_data/subdir.mk
-include src/smc_gen/r_irq_rx/src/subdir.mk
-include src/smc_gen/r_ble_rx23w/src/app_lib/profile_cmn/subdir.mk
-include src/smc_gen/r_ble_rx23w/src/app_lib/discovery/subdir.mk
-include src/smc_gen/r_sci_rx/src/subdir.mk
-include src/smc_gen/general/subdir.mk
-include src/smc_gen/r_lpc_rx/src/subdir.mk
-include src/smc_gen/r_bsp/mcu/all/subdir.mk
-include src/subdir.mk
-include src/smc_gen/r_sci_rx/src/targets/rx23w/subdir.mk
-include src/smc_gen/r_ble_rx23w/src/app_lib/cli/subdir.mk
-include src/smc_gen/r_pincfg/subdir.mk
-include src/smc_gen/r_ble_rx23w/src/app_lib/cli/console/rx_family/subdir.mk
-include src/smc_gen/r_byteq/src/subdir.mk
-include src/smc_gen/r_flash_rx/src/flash_type_1/subdir.mk
-include src/smc_gen/r_gpio_rx/src/targets/rx23w/subdir.mk
-include src/smc_gen/r_ble_rx23w/src/app_lib/logger/subdir.mk
-include src/smc_gen/r_ble_rx23w/src/platform/driver/dataflash/subdir.mk
-include src/smc_gen/r_bsp/mcu/rx23w/subdir.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif 
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif 
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif 
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif 
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif 
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif 
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif 
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif 
ifneq ($(strip $(SX_DEPS)),)
-include $(SX_DEPS)
endif 
ifneq ($(strip $(JMP_DEPS)),)
-include $(JMP_DEPS)
endif 
ifneq ($(strip $(SRC_DEPS)),)
-include $(SRC_DEPS)
endif 
ifneq ($(strip $(PP_DEPS)),)
-include $(PP_DEPS)
endif 
ifneq ($(strip $(P_DEPS)),)
-include $(P_DEPS)
endif 
ifneq ($(strip $(FSY_DEPS)),)
-include $(FSY_DEPS)
endif 
endif

ifneq ($(strip $(SRC_UPPER_SRCS)),)
ALL_ASMS += $(SRC_UPPER_SRCS) 
endif
ifneq ($(strip $(SRC_SRCS)),)
ALL_ASMS += $(SRC_SRCS) 
endif
ifneq ($(strip $(S_UPPER_SRCS)),)
ALL_ASMS += $(S_UPPER_SRCS) 
endif
ifneq ($(strip $(S_SRCS)),)
ALL_ASMS += $(S_SRCS) 
endif


-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables
LINKER_OUTPUT_OUTPUTS += \
ble_demo_tbrx23w_profile_server.mot

LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS += \
ble_demo_tbrx23w_profile_server.lib

CONVERTOR_OUTPUT_OUTPUTS += \
ble_demo_tbrx23w_profile_server.mot

OBJS := \
$(COMPILER_OBJS) \
$(INDIVIDUAL_COMPILER_OBJS) \
$(ASSEMBLER_OBJS) \
$(CUSTOM_OBJS)

# All Target
all:
	$(MAKE) --no-print-directory pre-build
	$(MAKE) --no-print-directory main-build


# Main-build Target
main-build: $(CONVERTOR_OUTPUT_OUTPUTS) ble_demo_tbrx23w_profile_server.x
	@echo 'Build complete.'

%.mot: $(LINKER_OUTPUT_OUTPUTS) Converter.sub
	@echo 'Invoking: Converter'
	@echo 'Building target:'
	@echo Converterble_demo_tbrx23w_profile_server.tmp=
	@sed -e "s/^/    /" "Converterble_demo_tbrx23w_profile_server.tmp"
	rlink -subcommand="Converterble_demo_tbrx23w_profile_server.tmp"
	@echo 'Finished building target:'
	@echo.


ble_demo_tbrx23w_profile_server.mot: $(OBJS)  $(ALL_ASMS) $(LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS)   \
C:\Users\Shrenik\e2_studio\workspace\ble_demo_tbrx23w_profile_server\src\smc_gen\r_ble_rx23w\lib\lib_ble_ps_ccrx.lib
	@echo 'Invoking: Linker'
	@echo Linkerble_demo_tbrx23w_profile_server.tmp=
	@sed -e "s/^/    /" "Linkerble_demo_tbrx23w_profile_server.tmp"
	rlink -subcommand="Linkerble_demo_tbrx23w_profile_server.tmp"
	@echo 'Finished building:'
	@echo.


ble_demo_tbrx23w_profile_server.lib: 
	@echo 'Invoking: Library Generator'
	@echo LibraryGeneratorble_demo_tbrx23w_profile_server.tmp=
	@sed -e "s/^/    /" "LibraryGeneratorble_demo_tbrx23w_profile_server.tmp"
	lbgrx -subcommand="LibraryGeneratorble_demo_tbrx23w_profile_server.tmp"
	@echo 'Finished building:'
	@echo.

ble_demo_tbrx23w_profile_server.x: ble_demo_tbrx23w_profile_server.mot
		-C:\Users\Shrenik\.eclipse\com.renesas.platform_1435879475\Utilities\\ccrx\renesas_cc_converter.exe ble_demo_tbrx23w_profile_server.mot ble_demo_tbrx23w_profile_server.x

# Other Targets
clean:
	-$(RM) $(LINKER_OUTPUT_OUTPUTS) $(LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS) $(CONVERTOR_OUTPUT_OUTPUTS)
	-rm -rf $(OBJS) $(C_DEPS) $(ASM_DEPS) $(DSP_DEPS) 
	-rm -rf src/smc_gen/r_ble_rx23w/src/app_lib/board/*.asm src/smc_gen/r_ble_rx23w/src/app_lib/board/*.p src/smc_gen/r_ble_rx23w/src/app_lib/board/*.pp src/smc_gen/r_ble_rx23w/src/app_lib/board/*.src src/smc_gen/r_ble_rx23w/src/app_lib/board/*.jmp src/smc_gen/r_ble_rx23w/src/app_lib/board/*.lst src/smc_gen/r_ble_rx23w/src/app_lib/board/*.prn src/smc_gen/r_ble_rx23w/src/app_lib/board/*.i src/smc_gen/r_ble_rx23w/src/app_lib/board/*.ud 
	-rm -rf src/smc_gen/r_flash_rx/src/flash_type_4/*.asm src/smc_gen/r_flash_rx/src/flash_type_4/*.p src/smc_gen/r_flash_rx/src/flash_type_4/*.pp src/smc_gen/r_flash_rx/src/flash_type_4/*.src src/smc_gen/r_flash_rx/src/flash_type_4/*.jmp src/smc_gen/r_flash_rx/src/flash_type_4/*.lst src/smc_gen/r_flash_rx/src/flash_type_4/*.prn src/smc_gen/r_flash_rx/src/flash_type_4/*.i src/smc_gen/r_flash_rx/src/flash_type_4/*.ud 
	-rm -rf src/smc_gen/r_ble_rx23w/src/app_lib/timer/*.asm src/smc_gen/r_ble_rx23w/src/app_lib/timer/*.p src/smc_gen/r_ble_rx23w/src/app_lib/timer/*.pp src/smc_gen/r_ble_rx23w/src/app_lib/timer/*.src src/smc_gen/r_ble_rx23w/src/app_lib/timer/*.jmp src/smc_gen/r_ble_rx23w/src/app_lib/timer/*.lst src/smc_gen/r_ble_rx23w/src/app_lib/timer/*.prn src/smc_gen/r_ble_rx23w/src/app_lib/timer/*.i src/smc_gen/r_ble_rx23w/src/app_lib/timer/*.ud 
	-rm -rf src/smc_gen/r_flash_rx/src/*.asm src/smc_gen/r_flash_rx/src/*.p src/smc_gen/r_flash_rx/src/*.pp src/smc_gen/r_flash_rx/src/*.src src/smc_gen/r_flash_rx/src/*.jmp src/smc_gen/r_flash_rx/src/*.lst src/smc_gen/r_flash_rx/src/*.prn src/smc_gen/r_flash_rx/src/*.i src/smc_gen/r_flash_rx/src/*.ud 
	-rm -rf src/smc_gen/r_gpio_rx/src/*.asm src/smc_gen/r_gpio_rx/src/*.p src/smc_gen/r_gpio_rx/src/*.pp src/smc_gen/r_gpio_rx/src/*.src src/smc_gen/r_gpio_rx/src/*.jmp src/smc_gen/r_gpio_rx/src/*.lst src/smc_gen/r_gpio_rx/src/*.prn src/smc_gen/r_gpio_rx/src/*.i src/smc_gen/r_gpio_rx/src/*.ud 
	-rm -rf src/smc_gen/r_ble_rx23w/src/app_lib/abs/*.asm src/smc_gen/r_ble_rx23w/src/app_lib/abs/*.p src/smc_gen/r_ble_rx23w/src/app_lib/abs/*.pp src/smc_gen/r_ble_rx23w/src/app_lib/abs/*.src src/smc_gen/r_ble_rx23w/src/app_lib/abs/*.jmp src/smc_gen/r_ble_rx23w/src/app_lib/abs/*.lst src/smc_gen/r_ble_rx23w/src/app_lib/abs/*.prn src/smc_gen/r_ble_rx23w/src/app_lib/abs/*.i src/smc_gen/r_ble_rx23w/src/app_lib/abs/*.ud 
	-rm -rf src/smc_gen/r_ble_rx23w/src/app_lib/cmd/*.asm src/smc_gen/r_ble_rx23w/src/app_lib/cmd/*.p src/smc_gen/r_ble_rx23w/src/app_lib/cmd/*.pp src/smc_gen/r_ble_rx23w/src/app_lib/cmd/*.src src/smc_gen/r_ble_rx23w/src/app_lib/cmd/*.jmp src/smc_gen/r_ble_rx23w/src/app_lib/cmd/*.lst src/smc_gen/r_ble_rx23w/src/app_lib/cmd/*.prn src/smc_gen/r_ble_rx23w/src/app_lib/cmd/*.i src/smc_gen/r_ble_rx23w/src/app_lib/cmd/*.ud 
	-rm -rf src/smc_gen/r_bsp/board/generic_rx23w/*.asm src/smc_gen/r_bsp/board/generic_rx23w/*.p src/smc_gen/r_bsp/board/generic_rx23w/*.pp src/smc_gen/r_bsp/board/generic_rx23w/*.src src/smc_gen/r_bsp/board/generic_rx23w/*.jmp src/smc_gen/r_bsp/board/generic_rx23w/*.lst src/smc_gen/r_bsp/board/generic_rx23w/*.prn src/smc_gen/r_bsp/board/generic_rx23w/*.i src/smc_gen/r_bsp/board/generic_rx23w/*.ud 
	-rm -rf src/smc_gen/Config_BLE_PROFILE/*.asm src/smc_gen/Config_BLE_PROFILE/*.p src/smc_gen/Config_BLE_PROFILE/*.pp src/smc_gen/Config_BLE_PROFILE/*.src src/smc_gen/Config_BLE_PROFILE/*.jmp src/smc_gen/Config_BLE_PROFILE/*.lst src/smc_gen/Config_BLE_PROFILE/*.prn src/smc_gen/Config_BLE_PROFILE/*.i src/smc_gen/Config_BLE_PROFILE/*.ud 
	-rm -rf src/smc_gen/r_ble_rx23w/src/platform/*.asm src/smc_gen/r_ble_rx23w/src/platform/*.p src/smc_gen/r_ble_rx23w/src/platform/*.pp src/smc_gen/r_ble_rx23w/src/platform/*.src src/smc_gen/r_ble_rx23w/src/platform/*.jmp src/smc_gen/r_ble_rx23w/src/platform/*.lst src/smc_gen/r_ble_rx23w/src/platform/*.prn src/smc_gen/r_ble_rx23w/src/platform/*.i src/smc_gen/r_ble_rx23w/src/platform/*.ud 
	-rm -rf src/smc_gen/r_cmt_rx/src/*.asm src/smc_gen/r_cmt_rx/src/*.p src/smc_gen/r_cmt_rx/src/*.pp src/smc_gen/r_cmt_rx/src/*.src src/smc_gen/r_cmt_rx/src/*.jmp src/smc_gen/r_cmt_rx/src/*.lst src/smc_gen/r_cmt_rx/src/*.prn src/smc_gen/r_cmt_rx/src/*.i src/smc_gen/r_cmt_rx/src/*.ud 
	-rm -rf src/smc_gen/r_ble_rx23w/src/app_lib/rtos/*.asm src/smc_gen/r_ble_rx23w/src/app_lib/rtos/*.p src/smc_gen/r_ble_rx23w/src/app_lib/rtos/*.pp src/smc_gen/r_ble_rx23w/src/app_lib/rtos/*.src src/smc_gen/r_ble_rx23w/src/app_lib/rtos/*.jmp src/smc_gen/r_ble_rx23w/src/app_lib/rtos/*.lst src/smc_gen/r_ble_rx23w/src/app_lib/rtos/*.prn src/smc_gen/r_ble_rx23w/src/app_lib/rtos/*.i src/smc_gen/r_ble_rx23w/src/app_lib/rtos/*.ud 
	-rm -rf src/smc_gen/r_lpc_rx/src/targets/rx23w/*.asm src/smc_gen/r_lpc_rx/src/targets/rx23w/*.p src/smc_gen/r_lpc_rx/src/targets/rx23w/*.pp src/smc_gen/r_lpc_rx/src/targets/rx23w/*.src src/smc_gen/r_lpc_rx/src/targets/rx23w/*.jmp src/smc_gen/r_lpc_rx/src/targets/rx23w/*.lst src/smc_gen/r_lpc_rx/src/targets/rx23w/*.prn src/smc_gen/r_lpc_rx/src/targets/rx23w/*.i src/smc_gen/r_lpc_rx/src/targets/rx23w/*.ud 
	-rm -rf src/smc_gen/r_flash_rx/src/flash_type_3/*.asm src/smc_gen/r_flash_rx/src/flash_type_3/*.p src/smc_gen/r_flash_rx/src/flash_type_3/*.pp src/smc_gen/r_flash_rx/src/flash_type_3/*.src src/smc_gen/r_flash_rx/src/flash_type_3/*.jmp src/smc_gen/r_flash_rx/src/flash_type_3/*.lst src/smc_gen/r_flash_rx/src/flash_type_3/*.prn src/smc_gen/r_flash_rx/src/flash_type_3/*.i src/smc_gen/r_flash_rx/src/flash_type_3/*.ud 
	-rm -rf src/smc_gen/r_ble_rx23w/src/app_lib/sec_data/*.asm src/smc_gen/r_ble_rx23w/src/app_lib/sec_data/*.p src/smc_gen/r_ble_rx23w/src/app_lib/sec_data/*.pp src/smc_gen/r_ble_rx23w/src/app_lib/sec_data/*.src src/smc_gen/r_ble_rx23w/src/app_lib/sec_data/*.jmp src/smc_gen/r_ble_rx23w/src/app_lib/sec_data/*.lst src/smc_gen/r_ble_rx23w/src/app_lib/sec_data/*.prn src/smc_gen/r_ble_rx23w/src/app_lib/sec_data/*.i src/smc_gen/r_ble_rx23w/src/app_lib/sec_data/*.ud 
	-rm -rf src/smc_gen/r_irq_rx/src/*.asm src/smc_gen/r_irq_rx/src/*.p src/smc_gen/r_irq_rx/src/*.pp src/smc_gen/r_irq_rx/src/*.src src/smc_gen/r_irq_rx/src/*.jmp src/smc_gen/r_irq_rx/src/*.lst src/smc_gen/r_irq_rx/src/*.prn src/smc_gen/r_irq_rx/src/*.i src/smc_gen/r_irq_rx/src/*.ud 
	-rm -rf src/smc_gen/r_ble_rx23w/src/app_lib/profile_cmn/*.asm src/smc_gen/r_ble_rx23w/src/app_lib/profile_cmn/*.p src/smc_gen/r_ble_rx23w/src/app_lib/profile_cmn/*.pp src/smc_gen/r_ble_rx23w/src/app_lib/profile_cmn/*.src src/smc_gen/r_ble_rx23w/src/app_lib/profile_cmn/*.jmp src/smc_gen/r_ble_rx23w/src/app_lib/profile_cmn/*.lst src/smc_gen/r_ble_rx23w/src/app_lib/profile_cmn/*.prn src/smc_gen/r_ble_rx23w/src/app_lib/profile_cmn/*.i src/smc_gen/r_ble_rx23w/src/app_lib/profile_cmn/*.ud 
	-rm -rf src/smc_gen/r_ble_rx23w/src/app_lib/discovery/*.asm src/smc_gen/r_ble_rx23w/src/app_lib/discovery/*.p src/smc_gen/r_ble_rx23w/src/app_lib/discovery/*.pp src/smc_gen/r_ble_rx23w/src/app_lib/discovery/*.src src/smc_gen/r_ble_rx23w/src/app_lib/discovery/*.jmp src/smc_gen/r_ble_rx23w/src/app_lib/discovery/*.lst src/smc_gen/r_ble_rx23w/src/app_lib/discovery/*.prn src/smc_gen/r_ble_rx23w/src/app_lib/discovery/*.i src/smc_gen/r_ble_rx23w/src/app_lib/discovery/*.ud 
	-rm -rf src/smc_gen/r_sci_rx/src/*.asm src/smc_gen/r_sci_rx/src/*.p src/smc_gen/r_sci_rx/src/*.pp src/smc_gen/r_sci_rx/src/*.src src/smc_gen/r_sci_rx/src/*.jmp src/smc_gen/r_sci_rx/src/*.lst src/smc_gen/r_sci_rx/src/*.prn src/smc_gen/r_sci_rx/src/*.i src/smc_gen/r_sci_rx/src/*.ud 
	-rm -rf src/smc_gen/general/*.asm src/smc_gen/general/*.p src/smc_gen/general/*.pp src/smc_gen/general/*.src src/smc_gen/general/*.jmp src/smc_gen/general/*.lst src/smc_gen/general/*.prn src/smc_gen/general/*.i src/smc_gen/general/*.ud 
	-rm -rf src/smc_gen/r_lpc_rx/src/*.asm src/smc_gen/r_lpc_rx/src/*.p src/smc_gen/r_lpc_rx/src/*.pp src/smc_gen/r_lpc_rx/src/*.src src/smc_gen/r_lpc_rx/src/*.jmp src/smc_gen/r_lpc_rx/src/*.lst src/smc_gen/r_lpc_rx/src/*.prn src/smc_gen/r_lpc_rx/src/*.i src/smc_gen/r_lpc_rx/src/*.ud 
	-rm -rf src/smc_gen/r_bsp/mcu/all/*.asm src/smc_gen/r_bsp/mcu/all/*.p src/smc_gen/r_bsp/mcu/all/*.pp src/smc_gen/r_bsp/mcu/all/*.src src/smc_gen/r_bsp/mcu/all/*.jmp src/smc_gen/r_bsp/mcu/all/*.lst src/smc_gen/r_bsp/mcu/all/*.prn src/smc_gen/r_bsp/mcu/all/*.i src/smc_gen/r_bsp/mcu/all/*.ud 
	-rm -rf src/*.asm src/*.p src/*.pp src/*.src src/*.jmp src/*.lst src/*.prn src/*.i src/*.ud 
	-rm -rf src/smc_gen/r_sci_rx/src/targets/rx23w/*.asm src/smc_gen/r_sci_rx/src/targets/rx23w/*.p src/smc_gen/r_sci_rx/src/targets/rx23w/*.pp src/smc_gen/r_sci_rx/src/targets/rx23w/*.src src/smc_gen/r_sci_rx/src/targets/rx23w/*.jmp src/smc_gen/r_sci_rx/src/targets/rx23w/*.lst src/smc_gen/r_sci_rx/src/targets/rx23w/*.prn src/smc_gen/r_sci_rx/src/targets/rx23w/*.i src/smc_gen/r_sci_rx/src/targets/rx23w/*.ud 
	-rm -rf src/smc_gen/r_ble_rx23w/src/app_lib/cli/*.asm src/smc_gen/r_ble_rx23w/src/app_lib/cli/*.p src/smc_gen/r_ble_rx23w/src/app_lib/cli/*.pp src/smc_gen/r_ble_rx23w/src/app_lib/cli/*.src src/smc_gen/r_ble_rx23w/src/app_lib/cli/*.jmp src/smc_gen/r_ble_rx23w/src/app_lib/cli/*.lst src/smc_gen/r_ble_rx23w/src/app_lib/cli/*.prn src/smc_gen/r_ble_rx23w/src/app_lib/cli/*.i src/smc_gen/r_ble_rx23w/src/app_lib/cli/*.ud 
	-rm -rf src/smc_gen/r_pincfg/*.asm src/smc_gen/r_pincfg/*.p src/smc_gen/r_pincfg/*.pp src/smc_gen/r_pincfg/*.src src/smc_gen/r_pincfg/*.jmp src/smc_gen/r_pincfg/*.lst src/smc_gen/r_pincfg/*.prn src/smc_gen/r_pincfg/*.i src/smc_gen/r_pincfg/*.ud 
	-rm -rf src/smc_gen/r_ble_rx23w/src/app_lib/cli/console/rx_family/*.asm src/smc_gen/r_ble_rx23w/src/app_lib/cli/console/rx_family/*.p src/smc_gen/r_ble_rx23w/src/app_lib/cli/console/rx_family/*.pp src/smc_gen/r_ble_rx23w/src/app_lib/cli/console/rx_family/*.src src/smc_gen/r_ble_rx23w/src/app_lib/cli/console/rx_family/*.jmp src/smc_gen/r_ble_rx23w/src/app_lib/cli/console/rx_family/*.lst src/smc_gen/r_ble_rx23w/src/app_lib/cli/console/rx_family/*.prn src/smc_gen/r_ble_rx23w/src/app_lib/cli/console/rx_family/*.i src/smc_gen/r_ble_rx23w/src/app_lib/cli/console/rx_family/*.ud 
	-rm -rf src/smc_gen/r_byteq/src/*.asm src/smc_gen/r_byteq/src/*.p src/smc_gen/r_byteq/src/*.pp src/smc_gen/r_byteq/src/*.src src/smc_gen/r_byteq/src/*.jmp src/smc_gen/r_byteq/src/*.lst src/smc_gen/r_byteq/src/*.prn src/smc_gen/r_byteq/src/*.i src/smc_gen/r_byteq/src/*.ud 
	-rm -rf src/smc_gen/r_flash_rx/src/flash_type_1/*.asm src/smc_gen/r_flash_rx/src/flash_type_1/*.p src/smc_gen/r_flash_rx/src/flash_type_1/*.pp src/smc_gen/r_flash_rx/src/flash_type_1/*.src src/smc_gen/r_flash_rx/src/flash_type_1/*.jmp src/smc_gen/r_flash_rx/src/flash_type_1/*.lst src/smc_gen/r_flash_rx/src/flash_type_1/*.prn src/smc_gen/r_flash_rx/src/flash_type_1/*.i src/smc_gen/r_flash_rx/src/flash_type_1/*.ud 
	-rm -rf src/smc_gen/r_gpio_rx/src/targets/rx23w/*.asm src/smc_gen/r_gpio_rx/src/targets/rx23w/*.p src/smc_gen/r_gpio_rx/src/targets/rx23w/*.pp src/smc_gen/r_gpio_rx/src/targets/rx23w/*.src src/smc_gen/r_gpio_rx/src/targets/rx23w/*.jmp src/smc_gen/r_gpio_rx/src/targets/rx23w/*.lst src/smc_gen/r_gpio_rx/src/targets/rx23w/*.prn src/smc_gen/r_gpio_rx/src/targets/rx23w/*.i src/smc_gen/r_gpio_rx/src/targets/rx23w/*.ud 
	-rm -rf src/smc_gen/r_ble_rx23w/src/app_lib/logger/*.asm src/smc_gen/r_ble_rx23w/src/app_lib/logger/*.p src/smc_gen/r_ble_rx23w/src/app_lib/logger/*.pp src/smc_gen/r_ble_rx23w/src/app_lib/logger/*.src src/smc_gen/r_ble_rx23w/src/app_lib/logger/*.jmp src/smc_gen/r_ble_rx23w/src/app_lib/logger/*.lst src/smc_gen/r_ble_rx23w/src/app_lib/logger/*.prn src/smc_gen/r_ble_rx23w/src/app_lib/logger/*.i src/smc_gen/r_ble_rx23w/src/app_lib/logger/*.ud 
	-rm -rf src/smc_gen/r_ble_rx23w/src/platform/driver/dataflash/*.asm src/smc_gen/r_ble_rx23w/src/platform/driver/dataflash/*.p src/smc_gen/r_ble_rx23w/src/platform/driver/dataflash/*.pp src/smc_gen/r_ble_rx23w/src/platform/driver/dataflash/*.src src/smc_gen/r_ble_rx23w/src/platform/driver/dataflash/*.jmp src/smc_gen/r_ble_rx23w/src/platform/driver/dataflash/*.lst src/smc_gen/r_ble_rx23w/src/platform/driver/dataflash/*.prn src/smc_gen/r_ble_rx23w/src/platform/driver/dataflash/*.i src/smc_gen/r_ble_rx23w/src/platform/driver/dataflash/*.ud 
	-rm -rf src/smc_gen/r_bsp/mcu/rx23w/*.asm src/smc_gen/r_bsp/mcu/rx23w/*.p src/smc_gen/r_bsp/mcu/rx23w/*.pp src/smc_gen/r_bsp/mcu/rx23w/*.src src/smc_gen/r_bsp/mcu/rx23w/*.jmp src/smc_gen/r_bsp/mcu/rx23w/*.lst src/smc_gen/r_bsp/mcu/rx23w/*.prn src/smc_gen/r_bsp/mcu/rx23w/*.i src/smc_gen/r_bsp/mcu/rx23w/*.ud 
	@echo
	@echo 'Clean complete.'

pre-build:
	@echo.
	-..\src\smc_gen\r_ble_rx23w\lib\ble_fit_lib_selector.bat
	@echo.

.PHONY: all clean  
-include ../makefile.targets