#include "UtilityFunctions.h"
#include <cstdlib>
#include <ctime>
#define PI 22.0/7.0

double UtilityFunctions::GenerateRandomDouble(double min, double max) {
    return min + static_cast<double>(rand()) / RAND_MAX * (max - min);
}

void UtilityFunctions::UpdateCameraOrbitPosition(double cameraAzimuth,double camTargetX, double camTargetY, double camTargetZ, double cameraRadius,double* camX, double* camY, double* camZ)
{
    // Convert angles from degrees to radians
    double azimuthRad = cameraAzimuth*PI/180.0;
    double elevationRad = 0;

    // Calculate Cartesian coordinates from spherical coordinates
    *camX = camTargetX + cameraRadius * cos(elevationRad) * cos(azimuthRad);
    *camY = camTargetY + cameraRadius * sin(elevationRad);
    *camZ = camTargetZ + cameraRadius * cos(elevationRad) * sin(azimuthRad);

}

Rotation UtilityFunctions::LerpRotation(Rotation startRotation, Rotation endRotation, float lerpValue)
{
    Rotation result;
    auto Xa = startRotation.x;
    auto Ya = startRotation.y;
    auto Za = startRotation.z;
    auto Xb = endRotation.x;
    auto Yb = endRotation.y;
    auto Zb = endRotation.z;
    //{ a.x + t * (b.x - a.x), a.y + t * (b.y - a.y), a.z + t * (b.z - a.z) };  linear interpolation
    result.x = Xa + lerpValue * (Xb - Xa);
    result.y = Ya + lerpValue * (Yb - Ya);
    result.z = Za + lerpValue * (Zb - Za);

    return result;
}

Scale UtilityFunctions::LerpScale(Scale startScale, Scale endScale, float lerpValue)
{
    Scale result;
    auto Xa = startScale.x;
    auto Ya = startScale.y;
    auto Za = startScale.z;
    auto Xb = endScale.x;
    auto Yb = endScale.y;
    auto Zb = endScale.z;
    //{ a.x + t * (b.x - a.x), a.y + t * (b.y - a.y), a.z + t * (b.z - a.z) };  linear interpolation
    result.x = Xa + lerpValue * (Xb - Xa);
    result.y = Ya + lerpValue * (Yb - Ya);
    result.z = Za + lerpValue * (Zb - Za);

    return result;
}

Position UtilityFunctions::LerpPosition(Position startPosition, Position endPosition, float lerpValue)
{
    Position result;
    auto Xa = startPosition.x;
    auto Ya = startPosition.y;
    auto Za = startPosition.z;
    auto Xb = endPosition.x;
    auto Yb = endPosition.y;
    auto Zb = endPosition.z;
    //{ a.x + t * (b.x - a.x), a.y + t * (b.y - a.y), a.z + t * (b.z - a.z) };  linear interpolation
    result.x = Xa + lerpValue * (Xb - Xa);
    result.y = Ya + lerpValue * (Yb - Ya);
    result.z = Za + lerpValue * (Zb - Za);

    return result;
}

Transform UtilityFunctions::LerpTransform(Transform startTransform, Transform endTransform, float lerpValue)
{
    //  Does linear interpolation for pos,rotate,scale vectors
    Transform result;
    
    auto posXa = startTransform.position.x;
    auto posYa = startTransform.position.y;
    auto posZa = startTransform.position.z;
    auto posXb = endTransform.position.x;
    auto posYb = endTransform.position.y;
    auto posZb = endTransform.position.z;
    //{ a.x + t * (b.x - a.x), a.y + t * (b.y - a.y), a.z + t * (b.z - a.z) };  linear interpolation
    result.position.x = posXa + lerpValue * (posXb - posXa);
    result.position.y = posYa + lerpValue * (posYb - posYa);
    result.position.z = posZa + lerpValue * (posZb - posZa);
    

    auto rotateXa = startTransform.rotation.x;
    auto rotateYa = startTransform.rotation.y;
    auto rotateZa = startTransform.rotation.z;
    auto rotateXb = endTransform.rotation.x;
    auto rotateYb = endTransform.rotation.y;
    auto rotateZb = endTransform.rotation.z;
    //{ a.x + t * (b.x - a.x), a.y + t * (b.y - a.y), a.z + t * (b.z - a.z) };  linear interpolation
    result.rotation.x = rotateXa + lerpValue * (rotateXb - rotateXa);
    result.rotation.y = rotateYa + lerpValue * (rotateYb - rotateYa);
    result.rotation.z = rotateZa + lerpValue * (rotateZb - rotateZa);

    auto scaleXa = startTransform.scale.x;
    auto scaleYa = startTransform.scale.y;
    auto scaleZa = startTransform.scale.z;
    auto scaleXb = endTransform.scale.x;
    auto scaleYb = endTransform.scale.y;
    auto scaleZb = endTransform.scale.z;
    //{ a.x + t * (b.x - a.x), a.y + t * (b.y - a.y), a.z + t * (b.z - a.z) };  linear interpolation
    result.scale.x = scaleXa + lerpValue * (scaleXb - scaleXa);
    result.scale.y = scaleYa + lerpValue * (scaleYb - scaleYa);
    result.scale.z = scaleZa + lerpValue * (scaleZb - scaleZa);
    
    return result;
}
