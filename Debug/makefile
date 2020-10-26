################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Middlewares/FreeRTOS/subdir.mk
-include Drivers/STM32F4xx_HAL_Driver/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
6_stm32f4_FREERTOS_uart_led_message_queue.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
6_stm32f4_FREERTOS_uart_led_message_queue.list \

OBJCOPY_BIN += \
6_stm32f4_FREERTOS_uart_led_message_queue.bin \


# All Target
all: 6_stm32f4_FREERTOS_uart_led_message_queue.elf secondary-outputs

# Tool invocations
6_stm32f4_FREERTOS_uart_led_message_queue.elf: $(OBJS) $(USER_OBJS) C:\Users\Aishwarya\Desktop\stm\6_stm32f4_FREERTOS_uart_led_message_queue\STM32F407VGTX_FLASH.ld
	arm-none-eabi-gcc -o "6_stm32f4_FREERTOS_uart_led_message_queue.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\Aishwarya\Desktop\stm\6_stm32f4_FREERTOS_uart_led_message_queue\STM32F407VGTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="6_stm32f4_FREERTOS_uart_led_message_queue.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

6_stm32f4_FREERTOS_uart_led_message_queue.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "6_stm32f4_FREERTOS_uart_led_message_queue.list"
	@echo 'Finished building: $@'
	@echo ' '

6_stm32f4_FREERTOS_uart_led_message_queue.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "6_stm32f4_FREERTOS_uart_led_message_queue.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
