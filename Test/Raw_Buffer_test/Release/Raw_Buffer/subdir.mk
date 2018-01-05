################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../../../Raw_Buffer/Raw_Buffer.c 

OBJS += \
./Raw_Buffer/Raw_Buffer.o 

C_DEPS += \
./Raw_Buffer/Raw_Buffer.d 


# Each subdirectory must supply rules for building sources it contributes
Raw_Buffer/Raw_Buffer.o: ../../../Raw_Buffer/Raw_Buffer.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I../../../base -I../../../dbc -I../../../Raw_Buffer -I../../../String -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


