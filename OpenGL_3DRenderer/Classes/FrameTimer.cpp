#include "FrameTimer.h"

void FrameTimer::Init(int requestedFPS)
{
    QueryPerformanceFrequency(&timerFreq);
    QueryPerformanceCounter(&timeNow);
    QueryPerformanceCounter(&timePrev);

    this->requestedFPS = requestedFPS;

    intervalsPerFrame = timerFreq.QuadPart / requestedFPS;
}

int FrameTimer::GetFramesToUpdate()
{
    int framesToUpdate = 0;
    QueryPerformanceCounter(&timeNow);

    deltaTime = timeNow.QuadPart - timePrev.QuadPart;

    framesToUpdate = (int)(deltaTime / intervalsPerFrame);

    if(framesToUpdate != 0)
        QueryPerformanceCounter(&timePrev);
    
    return framesToUpdate;
}

float FrameTimer::GetDeltaTime()
{
    // deltaTime is only accurate when framesToupdate != 0, so better only call this function when framesToUpdate >= 1
    float deltaTimeInSeconds = static_cast<float>(deltaTime) / timerFreq.QuadPart;
    return deltaTimeInSeconds;
}
