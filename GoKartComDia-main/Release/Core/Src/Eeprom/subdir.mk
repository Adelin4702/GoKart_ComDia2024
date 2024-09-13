################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Eeprom/Eeprom.c 

OBJS += \
./Core/Src/Eeprom/Eeprom.o 

C_DEPS += \
./Core/Src/Eeprom/Eeprom.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Eeprom/%.o Core/Src/Eeprom/%.su Core/Src/Eeprom/%.cyclo: ../Core/Src/Eeprom/%.c Core/Src/Eeprom/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../USB_HOST/App -I../USB_HOST/Target -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Eeprom

clean-Core-2f-Src-2f-Eeprom:
	-$(RM) ./Core/Src/Eeprom/Eeprom.cyclo ./Core/Src/Eeprom/Eeprom.d ./Core/Src/Eeprom/Eeprom.o ./Core/Src/Eeprom/Eeprom.su

.PHONY: clean-Core-2f-Src-2f-Eeprom

