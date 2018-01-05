################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../../../Input_File_Reader/Input_File_Reader.c \
../../../Input_File_Reader/s_DList.c 

OBJS += \
./Input_File_Reader/Input_File_Reader.o \
./Input_File_Reader/s_DList.o 

C_DEPS += \
./Input_File_Reader/Input_File_Reader.d \
./Input_File_Reader/s_DList.d 


# Each subdirectory must supply rules for building sources it contributes
Input_File_Reader/Input_File_Reader.o: ../../../Input_File_Reader/Input_File_Reader.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I../../../base -I../../../dbc -I../../../Input_File_Reader -I../../../String -I../../../DList -I../../../Protocol_Base -I../../../P_Clonable -I../../../P_Iterable -I../../../P_Indexable -I../../../P_DIterable -O0 -g3 -ftest-coverage -fprofile-arcs -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Input_File_Reader/s_DList.o: ../../../Input_File_Reader/s_DList.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I../../../base -I../../../dbc -I../../../Input_File_Reader -I../../../String -I../../../DList -I../../../Protocol_Base -I../../../P_Clonable -I../../../P_Iterable -I../../../P_Indexable -I../../../P_DIterable -O0 -g3 -ftest-coverage -fprofile-arcs -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


