################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/configuration_test_dispose.c \
../src/configuration_test_has.c \
../src/configuration_test_item.c \
../src/configuration_test_list_items.c \
../src/configuration_test_make.c \
../src/configuration_test_put.c \
../src/configuration_test_set_from_file.c \
../src/configuration_test_superkey_has.c \
../src/configuration_test_superkey_item.c \
../src/configuration_test_superkey_list_items.c \
../src/main.c 

OBJS += \
./src/configuration_test_dispose.o \
./src/configuration_test_has.o \
./src/configuration_test_item.o \
./src/configuration_test_list_items.o \
./src/configuration_test_make.o \
./src/configuration_test_put.o \
./src/configuration_test_set_from_file.o \
./src/configuration_test_superkey_has.o \
./src/configuration_test_superkey_item.o \
./src/configuration_test_superkey_list_items.o \
./src/main.o 

C_DEPS += \
./src/configuration_test_dispose.d \
./src/configuration_test_has.d \
./src/configuration_test_item.d \
./src/configuration_test_list_items.d \
./src/configuration_test_make.d \
./src/configuration_test_put.d \
./src/configuration_test_set_from_file.d \
./src/configuration_test_superkey_has.d \
./src/configuration_test_superkey_item.d \
./src/configuration_test_superkey_list_items.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I../../../base -I../../../dbc -I../../../Configuration -I../../../Input_File_Reader -I../../../String -I../../../DList -I../../../Protocol_Base -I../../../P_Clonable -I../../../P_Indexable -I../../../P_Iterable -I../../../P_DIterable -I../../../HTable -I../../../P_Iterable_kv -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


