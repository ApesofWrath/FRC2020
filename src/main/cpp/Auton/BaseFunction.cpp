#include "Auton/BaseFunction.h"

BaseFunction::BaseFunction() {
    
}

BaseFunction::~BaseFunction() {

}

void BaseFunction::CompleteTask() {
    OnCompleteTask();
    taskStarted = false;
}

void BaseFunction::BeginTask() {
    if (!taskStarted) {
        Run();
        taskStarted = true;
        timeTaskStarted = std::time(nullptr);
    }
}

double BaseFunction::TimeSinceTaskStarted() {
    return std::difftime(std::time(nullptr), timeTaskStarted);
}