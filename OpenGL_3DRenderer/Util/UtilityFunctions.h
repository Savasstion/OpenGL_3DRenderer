#pragma once
#include "../Classes/General/Position.h"
#include "../Classes/General/Rotation.h"
#include "../Classes/General/Scale.h"
#include "../Classes/General/Transform.h"

class UtilityFunctions
{
public:
    static double GenerateRandomDouble(double min, double max);
    static void UpdateCameraOrbitPosition(double cameraAzimuth,double camTargetX, double camTargetY, double camTargetZ, double cameraRadius,double* camX, double* camY, double* camZ);
    static Rotation LerpRotation(Rotation startRotation, Rotation endRotation, float lerpValue);
    static Scale LerpScale(Scale startScale, Scale endScale, float lerpValue);
    static Position LerpPosition(Position startPosition, Position endPosition, float lerpValue);
    static Transform LerpTransform(Transform startTransform, Transform endTransform, float lerpValue);
};
