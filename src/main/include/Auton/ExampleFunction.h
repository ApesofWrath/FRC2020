#pragma once

#include "BaseFunction.h"
#include <ctre/Phoenix.h>


class ExampleFunction : public BaseFunction {

public:

    ExampleFunction(TalonFX* testTalonL, TalonFX* testTalonR, int seconds_run) : talonL(testTalonL), talonR(testTalonR), seconds_to_run_for(seconds_run) {};
    ~ExampleFunction();

    TalonFX* talonL, *talonR;

    int seconds_to_run_for;

    void Run();

    int dir = 1;

    void KillTask();

    void UpdateTask();

    void OnCompleteTask();

};