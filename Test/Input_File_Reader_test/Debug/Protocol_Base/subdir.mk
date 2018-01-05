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
	gcc -I../../../base -I../../../dbc -I../../../Input_File_Reader -I../../../String -I../../../DList -I../../../Protocol_Base -I../../../P_Clonable -I../../../P_Iterable -I../../../P_Indexable -I../../../P_DIterable -O0 -g3 -ftest-coverage -fprofile-arcs -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


