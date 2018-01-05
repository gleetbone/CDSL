################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../../../Protocol_Base/Protocol_Base.c 

OBJS += \
./Protocol_Base/Protocol_Base.o 

C_DEPS += \
./Protocol_Base/Protocol_Base.d 


# Each subdirectory must supply rules for building sources it contributes
Protocol_Base/Protocol_Base.o: ../../../Protocol_Base/Protocol_Base.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I../../../base -I../../../dbc -I../../../Protocol_Base -I../../../P_Iterable_kv -I../../../P_Clonable -I../../../BSTree_kv -I../../../P_DIterable_kv -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


