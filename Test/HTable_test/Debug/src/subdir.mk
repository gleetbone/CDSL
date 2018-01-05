################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/HTable_test_bucket_count.c \
../src/HTable_test_count.c \
../src/HTable_test_cursor_dispose.c \
../src/HTable_test_cursor_forth.c \
../src/HTable_test_cursor_go.c \
../src/HTable_test_cursor_index.c \
../src/HTable_test_cursor_item_at.c \
../src/HTable_test_cursor_key_at.c \
../src/HTable_test_cursor_make.c \
../src/HTable_test_cursor_start.c \
../src/HTable_test_dispose.c \
../src/HTable_test_dispose_with_contents.c \
../src/HTable_test_forth.c \
../src/HTable_test_go.c \
../src/HTable_test_has.c \
../src/HTable_test_index.c \
../src/HTable_test_is_empty.c \
../src/HTable_test_item.c \
../src/HTable_test_item_at.c \
../src/HTable_test_item_at_index.c \
../src/HTable_test_key_at.c \
../src/HTable_test_key_at_index.c \
../src/HTable_test_keys_as_array.c \
../src/HTable_test_make.c \
../src/HTable_test_make_duplicate_from.c \
../src/HTable_test_make_from.c \
../src/HTable_test_make_from_array.c \
../src/HTable_test_make_n.c \
../src/HTable_test_off.c \
../src/HTable_test_p_clonable.c \
../src/HTable_test_p_iterable_kv.c \
../src/HTable_test_put.c \
../src/HTable_test_remove.c \
../src/HTable_test_remove_and_dispose.c \
../src/HTable_test_replace.c \
../src/HTable_test_replace_and_dispose.c \
../src/HTable_test_set_bucket_count.c \
../src/HTable_test_start.c \
../src/HTable_test_wipe_out.c \
../src/HTable_test_wipe_out_and_dispose.c \
../src/i_Clonable.c \
../src/ii_HTable.c \
../src/ii_Iterable_kv.c \
../src/main.c 

OBJS += \
./src/HTable_test_bucket_count.o \
./src/HTable_test_count.o \
./src/HTable_test_cursor_dispose.o \
./src/HTable_test_cursor_forth.o \
./src/HTable_test_cursor_go.o \
./src/HTable_test_cursor_index.o \
./src/HTable_test_cursor_item_at.o \
./src/HTable_test_cursor_key_at.o \
./src/HTable_test_cursor_make.o \
./src/HTable_test_cursor_start.o \
./src/HTable_test_dispose.o \
./src/HTable_test_dispose_with_contents.o \
./src/HTable_test_forth.o \
./src/HTable_test_go.o \
./src/HTable_test_has.o \
./src/HTable_test_index.o \
./src/HTable_test_is_empty.o \
./src/HTable_test_item.o \
./src/HTable_test_item_at.o \
./src/HTable_test_item_at_index.o \
./src/HTable_test_key_at.o \
./src/HTable_test_key_at_index.o \
./src/HTable_test_keys_as_array.o \
./src/HTable_test_make.o \
./src/HTable_test_make_duplicate_from.o \
./src/HTable_test_make_from.o \
./src/HTable_test_make_from_array.o \
./src/HTable_test_make_n.o \
./src/HTable_test_off.o \
./src/HTable_test_p_clonable.o \
./src/HTable_test_p_iterable_kv.o \
./src/HTable_test_put.o \
./src/HTable_test_remove.o \
./src/HTable_test_remove_and_dispose.o \
./src/HTable_test_replace.o \
./src/HTable_test_replace_and_dispose.o \
./src/HTable_test_set_bucket_count.o \
./src/HTable_test_start.o \
./src/HTable_test_wipe_out.o \
./src/HTable_test_wipe_out_and_dispose.o \
./src/i_Clonable.o \
./src/ii_HTable.o \
./src/ii_Iterable_kv.o \
./src/main.o 

C_DEPS += \
./src/HTable_test_bucket_count.d \
./src/HTable_test_count.d \
./src/HTable_test_cursor_dispose.d \
./src/HTable_test_cursor_forth.d \
./src/HTable_test_cursor_go.d \
./src/HTable_test_cursor_index.d \
./src/HTable_test_cursor_item_at.d \
./src/HTable_test_cursor_key_at.d \
./src/HTable_test_cursor_make.d \
./src/HTable_test_cursor_start.d \
./src/HTable_test_dispose.d \
./src/HTable_test_dispose_with_contents.d \
./src/HTable_test_forth.d \
./src/HTable_test_go.d \
./src/HTable_test_has.d \
./src/HTable_test_index.d \
./src/HTable_test_is_empty.d \
./src/HTable_test_item.d \
./src/HTable_test_item_at.d \
./src/HTable_test_item_at_index.d \
./src/HTable_test_key_at.d \
./src/HTable_test_key_at_index.d \
./src/HTable_test_keys_as_array.d \
./src/HTable_test_make.d \
./src/HTable_test_make_duplicate_from.d \
./src/HTable_test_make_from.d \
./src/HTable_test_make_from_array.d \
./src/HTable_test_make_n.d \
./src/HTable_test_off.d \
./src/HTable_test_p_clonable.d \
./src/HTable_test_p_iterable_kv.d \
./src/HTable_test_put.d \
./src/HTable_test_remove.d \
./src/HTable_test_remove_and_dispose.d \
./src/HTable_test_replace.d \
./src/HTable_test_replace_and_dispose.d \
./src/HTable_test_set_bucket_count.d \
./src/HTable_test_start.d \
./src/HTable_test_wipe_out.d \
./src/HTable_test_wipe_out_and_dispose.d \
./src/i_Clonable.d \
./src/ii_HTable.d \
./src/ii_Iterable_kv.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I../../../dbc -I../../../HTable -I../../../Protocol_Base -I../../../P_Clonable -I../../../base -I../../../P_Iterable_kv -O0 -g3 -ftest-coverage -fprofile-arcs -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


