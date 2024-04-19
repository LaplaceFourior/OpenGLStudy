#pragma once

class Time
{
public:
    static void Init();
    static float GetDeltaTime(); 
    static void Update(); 

private:
    static float lastFrameTime;
    static float deltaTime; 
};