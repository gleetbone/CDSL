################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/BSearcher_test_all.c \
../src/i_BSearcher.c \
../src/i_Indexable.c \
../src/i_Searcher.c \
../src/i_Sequence.c \
../src/main.c \
../src/test_search.c 

OBJS += \
./src/BSearcher_test_all.o \
./src/i_BSearcher.o \
./src/i_Indexable.o \
./src/i_Searcher.o \
./src/i_Sequence.o \
./src/main.o \
./src/test_search.o 

C_DEPS += \
./src/BSearcher_test_all.d \
./src/i_BSearcher.d \
./src/i_Indexable.d \
./src/i_Searcher.d \
./src/i_Sequence.d \
./src/main.d \
./src/test_search.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I../../../base -I../../../dbc -I../../../BSearcher -I../../../Protocol_Base -I../../../P_Searcher -I../../../P_Clonable -I../../../P_Indexable -I../../../Sequence -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


