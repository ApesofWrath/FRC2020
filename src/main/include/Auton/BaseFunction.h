#pragma once

#include <ctime>

class BaseFunction {
public:
    BaseFunction();
    ~BaseFunction();
    
    bool taskStarted, taskComplete;

    std::time_t timeTaskStarted;

    void BeginTask();
    virtual void Run()=0;
    bool HasTaskStarted() const { return taskStarted; }
    bool TaskRunning();
    virtual void KillTask()=0;
    virtual void OnCompleteTask()=0;
    virtual void UpdateTask()=0;
    void CompleteTask();
    double TimeSinceTaskStarted();

};