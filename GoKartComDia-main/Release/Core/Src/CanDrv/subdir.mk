################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/CanDrv/CanDrv.c \
../Core/Src/CanDrv/Test_CanDrv.c 

OBJS += \
./Core/Src/CanDrv/CanDrv.o \
./Core/Src/CanDrv/Test_CanDrv.o 

C_DEPS += \
./Core/Src/CanDrv/CanDrv.d \
./Core/Src/CanDrv/Test_CanDrv.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/CanDrv/%.o Core/Src/CanDrv/%.su Core/Src/CanDrv/%.cyclo: ../Core/Src/CanDrv/%.c Core/Src/CanDrv/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../USB_HOST/App -I../USB_HOST/Target -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-CanDrv

clean-Core-2f-Src-2f-CanDrv:
	-$(RM) ./Core/Src/CanDrv/CanDrv.cyclo ./Core/Src/CanDrv/CanDrv.d ./Core/Src/CanDrv/CanDrv.o ./Core/Src/CanDrv/CanDrv.su ./Core/Src/CanDrv/Test_CanDrv.cyclo ./Core/Src/CanDrv/Test_CanDrv.d ./Core/Src/CanDrv/Test_CanDrv.o ./Core/Src/CanDrv/Test_CanDrv.su

.PHONY: clean-Core-2f-Src-2f-CanDrv

