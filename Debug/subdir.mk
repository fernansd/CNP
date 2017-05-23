################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CNPEvaluator.cpp \
../CNPInstance.cpp \
../CNPSimulatedAnnealing.cpp \
../CNPSolGenerator.cpp \
../CNPSolution.cpp \
../Timer.cpp \
../main.cpp \
../seeds.cpp 

OBJS += \
./CNPEvaluator.o \
./CNPInstance.o \
./CNPSimulatedAnnealing.o \
./CNPSolGenerator.o \
./CNPSolution.o \
./Timer.o \
./main.o \
./seeds.o 

CPP_DEPS += \
./CNPEvaluator.d \
./CNPInstance.d \
./CNPSimulatedAnnealing.d \
./CNPSolGenerator.d \
./CNPSolution.d \
./Timer.d \
./main.d \
./seeds.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I"/home/fernando/workspace/P5Metaheuristicas/include" -O3 -g3 -pg -pedantic -pedantic-errors -Wall -Wextra -Werror -Wconversion -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


