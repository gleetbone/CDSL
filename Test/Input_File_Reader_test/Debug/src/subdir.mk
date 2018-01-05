################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/ifr_test_empty.c \
../src/ifr_test_make.c \
../src/ifr_test_multiline.c \
../src/ifr_test_one_line.c \
../src/ifr_test_one_line_comment.c \
../src/ifr_test_quotes.c \
../src/ifr_test_three_line.c \
../src/ifr_test_two_line.c \
../src/main.c 

OBJS += \
./src/ifr_test_empty.o \
./src/ifr_test_make.o \
./src/ifr_test_multiline.o \
./src/ifr_test_one_line.o \
./src/ifr_test_one_line_comment.o \
./src/ifr_test_quotes.o \
./src/ifr_test_three_line.o \
./src/ifr_test_two_line.o \
./src/main.o 

C_DEPS += \
./src/ifr_test_empty.d \
./src/ifr_test_make.d \
./src/ifr_test_multiline.d \
./src/ifr_test_one_line.d \
./src/ifr_test_one_line_comment.d \
./src/ifr_test_quotes.d \
./src/ifr_test_three_line.d \
./src/ifr_test_two_line.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I../../../base -I../../../dbc -I../../../Input_File_Reader -I../../../String -I../../../DList -I../../../Protocol_Base -I../../../P_Clonable -I../../../P_Iterable -I../../../P_Indexable -I../../../P_DIterable -O0 -g3 -ftest-coverage -fprofile-arcs -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


