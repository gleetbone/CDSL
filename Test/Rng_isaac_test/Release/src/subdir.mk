################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Rng_isaac_gaussian_test_dispose.c \
../src/Rng_isaac_gaussian_test_f32_item.c \
../src/Rng_isaac_gaussian_test_f64_item.c \
../src/Rng_isaac_gaussian_test_forth.c \
../src/Rng_isaac_gaussian_test_make.c \
../src/Rng_isaac_gaussian_test_make_with_seed.c \
../src/Rng_isaac_test_dispose.c \
../src/Rng_isaac_test_f32_item.c \
../src/Rng_isaac_test_f64_item.c \
../src/Rng_isaac_test_forth.c \
../src/Rng_isaac_test_i32_item.c \
../src/Rng_isaac_test_i64_item.c \
../src/Rng_isaac_test_make.c \
../src/Rng_isaac_test_make_with_seed.c \
../src/Rng_isaac_test_u32_item.c \
../src/Rng_isaac_test_u64_item.c \
../src/main.c 

OBJS += \
./src/Rng_isaac_gaussian_test_dispose.o \
./src/Rng_isaac_gaussian_test_f32_item.o \
./src/Rng_isaac_gaussian_test_f64_item.o \
./src/Rng_isaac_gaussian_test_forth.o \
./src/Rng_isaac_gaussian_test_make.o \
./src/Rng_isaac_gaussian_test_make_with_seed.o \
./src/Rng_isaac_test_dispose.o \
./src/Rng_isaac_test_f32_item.o \
./src/Rng_isaac_test_f64_item.o \
./src/Rng_isaac_test_forth.o \
./src/Rng_isaac_test_i32_item.o \
./src/Rng_isaac_test_i64_item.o \
./src/Rng_isaac_test_make.o \
./src/Rng_isaac_test_make_with_seed.o \
./src/Rng_isaac_test_u32_item.o \
./src/Rng_isaac_test_u64_item.o \
./src/main.o 

C_DEPS += \
./src/Rng_isaac_gaussian_test_dispose.d \
./src/Rng_isaac_gaussian_test_f32_item.d \
./src/Rng_isaac_gaussian_test_f64_item.d \
./src/Rng_isaac_gaussian_test_forth.d \
./src/Rng_isaac_gaussian_test_make.d \
./src/Rng_isaac_gaussian_test_make_with_seed.d \
./src/Rng_isaac_test_dispose.d \
./src/Rng_isaac_test_f32_item.d \
./src/Rng_isaac_test_f64_item.d \
./src/Rng_isaac_test_forth.d \
./src/Rng_isaac_test_i32_item.d \
./src/Rng_isaac_test_i64_item.d \
./src/Rng_isaac_test_make.d \
./src/Rng_isaac_test_make_with_seed.d \
./src/Rng_isaac_test_u32_item.d \
./src/Rng_isaac_test_u64_item.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I../../../base -I../../../dbc -I../../../Rng_Isaac -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


