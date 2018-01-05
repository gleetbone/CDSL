################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../../../Binary_File/Binary_File.c 

OBJS += \
./Binary_File/Binary_File.o 

C_DEPS += \
./Binary_File/Binary_File.d 


# Each subdirectory must supply rules for building sources it contributes
Binary_File/Binary_File.o: ../../../Binary_File/Binary_File.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I../../../base -I../../../dbc -I../../../Binary_File -I../../../String -I../../../Raw_Buffer -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


