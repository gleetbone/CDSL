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
	gcc -I../../../base -I../../../dbc -I../../../Configuration -I../../../Input_File_Reader -I../../../String -I../../../DList -I../../../Protocol_Base -I../../../P_Clonable -I../../../P_Indexable -I../../../P_Iterable -I../../../P_DIterable -I../../../HTable -I../../../P_Iterable_kv -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

String/String_utilities.o: ../../../String/String_utilities.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I../../../base -I../../../dbc -I../../../Configuration -I../../../Input_File_Reader -I../../../String -I../../../DList -I../../../Protocol_Base -I../../../P_Clonable -I../../../P_Indexable -I../../../P_Iterable -I../../../P_DIterable -I../../../HTable -I../../../P_Iterable_kv -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


