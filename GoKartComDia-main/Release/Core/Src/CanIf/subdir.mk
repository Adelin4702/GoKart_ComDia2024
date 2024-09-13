################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/CanIf/CanIf.c 

OBJS += \
./Core/Src/CanIf/CanIf.o 

C_DEPS += \
./Core/Src/CanIf/CanIf.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/CanIf/%.o Core/Src/CanIf/%.su Core/Src/CanIf/%.cyclo: ../Core/Src/CanIf/%.c Core/Src/CanIf/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../USB_HOST/App -I../USB_HOST/Target -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-CanIf

clean-Core-2f-Src-2f-CanIf:
	-$(RM) ./Core/Src/CanIf/CanIf.cyclo ./Core/Src/CanIf/CanIf.d ./Core/Src/CanIf/CanIf.o ./Core/Src/CanIf/CanIf.su

.PHONY: clean-Core-2f-Src-2f-CanIf

