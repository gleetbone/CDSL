################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/directory_test_close.c \
../src/directory_test_create.c \
../src/directory_test_create_mode.c \
../src/directory_test_delete.c \
../src/directory_test_delete_files.c \
../src/directory_test_directories.c \
../src/directory_test_directories_count.c \
../src/directory_test_directories_cstring.c \
../src/directory_test_dispose.c \
../src/directory_test_end_of_input.c \
../src/directory_test_exists.c \
../src/directory_test_filenames.c \
../src/directory_test_filenames_count.c \
../src/directory_test_filenames_cstring.c \
../src/directory_test_is_closed.c \
../src/directory_test_is_empty.c \
../src/directory_test_is_open_read.c \
../src/directory_test_is_readable.c \
../src/directory_test_last_entry.c \
../src/directory_test_last_entry_cstring.c \
../src/directory_test_links.c \
../src/directory_test_links_count.c \
../src/directory_test_links_cstring.c \
../src/directory_test_make.c \
../src/directory_test_make_cstring.c \
../src/directory_test_name.c \
../src/directory_test_name_cstring.c \
../src/directory_test_open_read.c \
../src/directory_test_read_next_entry.c \
../src/directory_test_recursive_create.c \
../src/directory_test_recursive_delete.c \
../src/main.c 

OBJS += \
./src/directory_test_close.o \
./src/directory_test_create.o \
./src/directory_test_create_mode.o \
./src/directory_test_delete.o \
./src/directory_test_delete_files.o \
./src/directory_test_directories.o \
./src/directory_test_directories_count.o \
./src/directory_test_directories_cstring.o \
./src/directory_test_dispose.o \
./src/directory_test_end_of_input.o \
./src/directory_test_exists.o \
./src/directory_test_filenames.o \
./src/directory_test_filenames_count.o \
./src/directory_test_filenames_cstring.o \
./src/directory_test_is_closed.o \
./src/directory_test_is_empty.o \
./src/directory_test_is_open_read.o \
./src/directory_test_is_readable.o \
./src/directory_test_last_entry.o \
./src/directory_test_last_entry_cstring.o \
./src/directory_test_links.o \
./src/directory_test_links_count.o \
./src/directory_test_links_cstring.o \
./src/directory_test_make.o \
./src/directory_test_make_cstring.o \
./src/directory_test_name.o \
./src/directory_test_name_cstring.o \
./src/directory_test_open_read.o \
./src/directory_test_read_next_entry.o \
./src/directory_test_recursive_create.o \
./src/directory_test_recursive_delete.o \
./src/main.o 

C_DEPS += \
./src/directory_test_close.d \
./src/directory_test_create.d \
./src/directory_test_create_mode.d \
./src/directory_test_delete.d \
./src/directory_test_delete_files.d \
./src/directory_test_directories.d \
./src/directory_test_directories_count.d \
./src/directory_test_directories_cstring.d \
./src/directory_test_dispose.d \
./src/directory_test_end_of_input.d \
./src/directory_test_exists.d \
./src/directory_test_filenames.d \
./src/directory_test_filenames_count.d \
./src/directory_test_filenames_cstring.d \
./src/directory_test_is_closed.d \
./src/directory_test_is_empty.d \
./src/directory_test_is_open_read.d \
./src/directory_test_is_readable.d \
./src/directory_test_last_entry.d \
./src/directory_test_last_entry_cstring.d \
./src/directory_test_links.d \
./src/directory_test_links_count.d \
./src/directory_test_links_cstring.d \
./src/directory_test_make.d \
./src/directory_test_make_cstring.d \
./src/directory_test_name.d \
./src/directory_test_name_cstring.d \
./src/directory_test_open_read.d \
./src/directory_test_read_next_entry.d \
./src/directory_test_recursive_create.d \
./src/directory_test_recursive_delete.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I../../../base -I../../../dbc -I../../../Directory -I../../../String -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


