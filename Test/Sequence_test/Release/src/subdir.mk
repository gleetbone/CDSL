################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Sequence_test_as_array.c \
../src/Sequence_test_capacity.c \
../src/Sequence_test_clone.c \
../src/Sequence_test_count.c \
../src/Sequence_test_deep_clone.c \
../src/Sequence_test_dispose.c \
../src/Sequence_test_dispose_with_contents.c \
../src/Sequence_test_ensure_count.c \
../src/Sequence_test_is_empty.c \
../src/Sequence_test_item.c \
../src/Sequence_test_make.c \
../src/Sequence_test_make_from_array.c \
../src/Sequence_test_make_n.c \
../src/Sequence_test_p_clonable.c \
../src/Sequence_test_p_indexable.c \
../src/Sequence_test_protocol.c \
../src/Sequence_test_put.c \
../src/Sequence_test_replace.c \
../src/Sequence_test_replace_and_dispose.c \
../src/Sequence_test_set_capacity.c \
../src/Sequence_test_set_count.c \
../src/Sequence_test_wipe_out.c \
../src/Sequence_test_wipe_out_and_dispose.c \
../src/int_Clonable.c \
../src/int_Indexable.c \
../src/int_Sequence.c \
../src/main.c 

OBJS += \
./src/Sequence_test_as_array.o \
./src/Sequence_test_capacity.o \
./src/Sequence_test_clone.o \
./src/Sequence_test_count.o \
./src/Sequence_test_deep_clone.o \
./src/Sequence_test_dispose.o \
./src/Sequence_test_dispose_with_contents.o \
./src/Sequence_test_ensure_count.o \
./src/Sequence_test_is_empty.o \
./src/Sequence_test_item.o \
./src/Sequence_test_make.o \
./src/Sequence_test_make_from_array.o \
./src/Sequence_test_make_n.o \
./src/Sequence_test_p_clonable.o \
./src/Sequence_test_p_indexable.o \
./src/Sequence_test_protocol.o \
./src/Sequence_test_put.o \
./src/Sequence_test_replace.o \
./src/Sequence_test_replace_and_dispose.o \
./src/Sequence_test_set_capacity.o \
./src/Sequence_test_set_count.o \
./src/Sequence_test_wipe_out.o \
./src/Sequence_test_wipe_out_and_dispose.o \
./src/int_Clonable.o \
./src/int_Indexable.o \
./src/int_Sequence.o \
./src/main.o 

C_DEPS += \
./src/Sequence_test_as_array.d \
./src/Sequence_test_capacity.d \
./src/Sequence_test_clone.d \
./src/Sequence_test_count.d \
./src/Sequence_test_deep_clone.d \
./src/Sequence_test_dispose.d \
./src/Sequence_test_dispose_with_contents.d \
./src/Sequence_test_ensure_count.d \
./src/Sequence_test_is_empty.d \
./src/Sequence_test_item.d \
./src/Sequence_test_make.d \
./src/Sequence_test_make_from_array.d \
./src/Sequence_test_make_n.d \
./src/Sequence_test_p_clonable.d \
./src/Sequence_test_p_indexable.d \
./src/Sequence_test_protocol.d \
./src/Sequence_test_put.d \
./src/Sequence_test_replace.d \
./src/Sequence_test_replace_and_dispose.d \
./src/Sequence_test_set_capacity.d \
./src/Sequence_test_set_count.d \
./src/Sequence_test_wipe_out.d \
./src/Sequence_test_wipe_out_and_dispose.d \
./src/int_Clonable.d \
./src/int_Indexable.d \
./src/int_Sequence.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I../../../base -I../../../dbc -I../../../Sequence -I../../../Protocol_Base -I../../../P_Clonable -I../../../P_Indexable -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


