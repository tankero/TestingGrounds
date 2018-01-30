// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
public:
	UPROPERTY(EditAnywhere, Category = Setup)
		float RotationalSpeed = 20.f;

	void Rotate(float TargetAngle);
	
};
