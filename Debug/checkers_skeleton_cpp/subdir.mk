################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../checkers_skeleton_cpp/gamestate.cpp \
../checkers_skeleton_cpp/main.cpp \
../checkers_skeleton_cpp/player.cpp 

OBJS += \
./checkers_skeleton_cpp/gamestate.o \
./checkers_skeleton_cpp/main.o \
./checkers_skeleton_cpp/player.o 

CPP_DEPS += \
./checkers_skeleton_cpp/gamestate.d \
./checkers_skeleton_cpp/main.d \
./checkers_skeleton_cpp/player.d 


# Each subdirectory must supply rules for building sources it contributes
checkers_skeleton_cpp/%.o: ../checkers_skeleton_cpp/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


