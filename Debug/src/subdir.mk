################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/gamestate.cpp \
../src/logmain.cpp \
../src/main.cpp \
../src/player.cpp 

OBJS += \
./src/gamestate.o \
./src/logmain.o \
./src/main.o \
./src/player.o 

CPP_DEPS += \
./src/gamestate.d \
./src/logmain.d \
./src/main.d \
./src/player.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1y -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


