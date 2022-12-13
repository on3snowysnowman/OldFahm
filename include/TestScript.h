#pragma once

#include <iostream>

#include "Script.h"

struct TestScript : public Script
{
    TestScript() : Script()
    {
    }

    ~TestScript() {}

    void start() override
    {
        name = "TestScript";
    }

    void update() override
    {

    }
    
};


