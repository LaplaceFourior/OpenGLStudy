#pragma once

class Time
{
public:
    static void Init();
    static float GetDeltaTime(); // 获取两帧之间的时间差
    static void Update(); // 在每帧开始时调用以更新时间

private:
    static float lastFrameTime;
    static float deltaTime; // 当前帧与上一帧之间的时间差
};