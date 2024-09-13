################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/OS/OS.c 

OBJS += \
./Core/Src/OS/OS.o 

C_DEPS += \
./Core/Src/OS/OS.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/OS/%.o Core/Src/OS/%.su Core/Src/OS/%.cyclo: ../Core/Src/OS/%.c Core/Src/OS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../USB_HOST/App -I../USB_HOST/Target -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-OS

clean-Core-2f-Src-2f-OS:
	-$(RM) ./Core/Src/OS/OS.cyclo ./Core/Src/OS/OS.d ./Core/Src/OS/OS.o ./Core/Src/OS/OS.su

.PHONY: clean-Core-2f-Src-2f-OS

