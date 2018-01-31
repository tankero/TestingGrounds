// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

UTankTurret::UTankTurret()
{
	bAbsoluteRotation = true;
}

void UTankTurret::Rotate(float RelativeSpeed)
{

	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.f, 1.f);
	auto RotationChange = RelativeSpeed * RotationalSpeed * GetWorld()->DeltaTimeSeconds;
	auto RawNewDirection = RelativeRotation.Yaw + RotationChange;
	
	SetRelativeRotation(FRotator(0.f, RawNewDirection, 0.f));
	
}
