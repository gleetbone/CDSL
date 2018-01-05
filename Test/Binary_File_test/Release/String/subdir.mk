################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../../../String/String.c \
../../../String/String_utilities.c 

OBJS += \
./String/String.o \
./String/String_utilities.o 

C_DEPS += \
./String/String.d \
./String/String_utilities.d 


# Each subdirectory must supply rules for building sources it contributes
String/String.o: ../../../String/String.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I../../../base -I../../../dbc -I../../../Binary_File -I../../../String -I../../../Raw_Buffer -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

String/String_utilities.o: ../../../String/String_utilities.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I../../../base -I../../../dbc -I../../../Binary_File -I../../../String -I../../../Raw_Buffer -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


