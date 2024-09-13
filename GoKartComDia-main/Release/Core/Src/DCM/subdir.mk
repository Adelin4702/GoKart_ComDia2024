################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/DCM/DCM.c \
../Core/Src/DCM/Dcm_DID.c \
../Core/Src/DCM/Dcm_Service_ClearDiagnosticInformation.c \
../Core/Src/DCM/Dcm_Service_DiagnosticSessionControl.c \
../Core/Src/DCM/Dcm_Service_ReadDTCInformation.c \
../Core/Src/DCM/Dcm_Service_ReadDataByIdentifier.c \
../Core/Src/DCM/Dcm_Service_ReadMemoryByAddress.c \
../Core/Src/DCM/Dcm_Service_RoutineControl.c \
../Core/Src/DCM/Dcm_Service_SecurityAccess.c \
../Core/Src/DCM/Dcm_Service_WriteDataByIdentifier.c \
../Core/Src/DCM/Dcm_Service_WriteMemoryByAddress.c 

OBJS += \
./Core/Src/DCM/DCM.o \
./Core/Src/DCM/Dcm_DID.o \
./Core/Src/DCM/Dcm_Service_ClearDiagnosticInformation.o \
./Core/Src/DCM/Dcm_Service_DiagnosticSessionControl.o \
./Core/Src/DCM/Dcm_Service_ReadDTCInformation.o \
./Core/Src/DCM/Dcm_Service_ReadDataByIdentifier.o \
./Core/Src/DCM/Dcm_Service_ReadMemoryByAddress.o \
./Core/Src/DCM/Dcm_Service_RoutineControl.o \
./Core/Src/DCM/Dcm_Service_SecurityAccess.o \
./Core/Src/DCM/Dcm_Service_WriteDataByIdentifier.o \
./Core/Src/DCM/Dcm_Service_WriteMemoryByAddress.o 

C_DEPS += \
./Core/Src/DCM/DCM.d \
./Core/Src/DCM/Dcm_DID.d \
./Core/Src/DCM/Dcm_Service_ClearDiagnosticInformation.d \
./Core/Src/DCM/Dcm_Service_DiagnosticSessionControl.d \
./Core/Src/DCM/Dcm_Service_ReadDTCInformation.d \
./Core/Src/DCM/Dcm_Service_ReadDataByIdentifier.d \
./Core/Src/DCM/Dcm_Service_ReadMemoryByAddress.d \
./Core/Src/DCM/Dcm_Service_RoutineControl.d \
./Core/Src/DCM/Dcm_Service_SecurityAccess.d \
./Core/Src/DCM/Dcm_Service_WriteDataByIdentifier.d \
./Core/Src/DCM/Dcm_Service_WriteMemoryByAddress.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/DCM/%.o Core/Src/DCM/%.su Core/Src/DCM/%.cyclo: ../Core/Src/DCM/%.c Core/Src/DCM/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../USB_HOST/App -I../USB_HOST/Target -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-DCM

clean-Core-2f-Src-2f-DCM:
	-$(RM) ./Core/Src/DCM/DCM.cyclo ./Core/Src/DCM/DCM.d ./Core/Src/DCM/DCM.o ./Core/Src/DCM/DCM.su ./Core/Src/DCM/Dcm_DID.cyclo ./Core/Src/DCM/Dcm_DID.d ./Core/Src/DCM/Dcm_DID.o ./Core/Src/DCM/Dcm_DID.su ./Core/Src/DCM/Dcm_Service_ClearDiagnosticInformation.cyclo ./Core/Src/DCM/Dcm_Service_ClearDiagnosticInformation.d ./Core/Src/DCM/Dcm_Service_ClearDiagnosticInformation.o ./Core/Src/DCM/Dcm_Service_ClearDiagnosticInformation.su ./Core/Src/DCM/Dcm_Service_DiagnosticSessionControl.cyclo ./Core/Src/DCM/Dcm_Service_DiagnosticSessionControl.d ./Core/Src/DCM/Dcm_Service_DiagnosticSessionControl.o ./Core/Src/DCM/Dcm_Service_DiagnosticSessionControl.su ./Core/Src/DCM/Dcm_Service_ReadDTCInformation.cyclo ./Core/Src/DCM/Dcm_Service_ReadDTCInformation.d ./Core/Src/DCM/Dcm_Service_ReadDTCInformation.o ./Core/Src/DCM/Dcm_Service_ReadDTCInformation.su ./Core/Src/DCM/Dcm_Service_ReadDataByIdentifier.cyclo ./Core/Src/DCM/Dcm_Service_ReadDataByIdentifier.d ./Core/Src/DCM/Dcm_Service_ReadDataByIdentifier.o ./Core/Src/DCM/Dcm_Service_ReadDataByIdentifier.su ./Core/Src/DCM/Dcm_Service_ReadMemoryByAddress.cyclo ./Core/Src/DCM/Dcm_Service_ReadMemoryByAddress.d ./Core/Src/DCM/Dcm_Service_ReadMemoryByAddress.o ./Core/Src/DCM/Dcm_Service_ReadMemoryByAddress.su ./Core/Src/DCM/Dcm_Service_RoutineControl.cyclo ./Core/Src/DCM/Dcm_Service_RoutineControl.d ./Core/Src/DCM/Dcm_Service_RoutineControl.o ./Core/Src/DCM/Dcm_Service_RoutineControl.su ./Core/Src/DCM/Dcm_Service_SecurityAccess.cyclo ./Core/Src/DCM/Dcm_Service_SecurityAccess.d ./Core/Src/DCM/Dcm_Service_SecurityAccess.o ./Core/Src/DCM/Dcm_Service_SecurityAccess.su ./Core/Src/DCM/Dcm_Service_WriteDataByIdentifier.cyclo ./Core/Src/DCM/Dcm_Service_WriteDataByIdentifier.d ./Core/Src/DCM/Dcm_Service_WriteDataByIdentifier.o ./Core/Src/DCM/Dcm_Service_WriteDataByIdentifier.su ./Core/Src/DCM/Dcm_Service_WriteMemoryByAddress.cyclo ./Core/Src/DCM/Dcm_Service_WriteMemoryByAddress.d ./Core/Src/DCM/Dcm_Service_WriteMemoryByAddress.o ./Core/Src/DCM/Dcm_Service_WriteMemoryByAddress.su

.PHONY: clean-Core-2f-Src-2f-DCM

