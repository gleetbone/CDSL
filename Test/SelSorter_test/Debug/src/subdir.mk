################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/SelSorter_test_all.c \
../src/i_Indexable.c \
../src/i_SelSorter.c \
../src/i_Sequence.c \
../src/i_Sorter.c \
../src/main.c \
../src/test_sort.c 

OBJS += \
./src/SelSorter_test_all.o \
./src/i_Indexable.o \
./src/i_SelSorter.o \
./src/i_Sequence.o \
./src/i_Sorter.o \
./src/main.o \
./src/test_sort.o 

C_DEPS += \
./src/SelSorter_test_all.d \
./src/i_Indexable.d \
./src/i_SelSorter.d \
./src/i_Sequence.d \
./src/i_Sorter.d \
./src/main.d \
./src/test_sort.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I../../../base -I../../../dbc -I../../../SelSorter -I../../../Protocol_Base -I../../../P_Clonable -I../../../P_Sorter -I../../../Sequence -I../../../P_Indexable -O0 -g3 -ftest-coverage -fprofile-arcs -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


