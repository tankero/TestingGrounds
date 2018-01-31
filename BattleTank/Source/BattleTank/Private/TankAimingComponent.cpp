// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ActorComponent.h"





// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	

	// ...
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	BarrelComponent = BarrelToSet;

}

void UTankAimingComponent::SetTurretReference(UTankTurret * TurretToSet)
{
	TurretComponent = TurretToSet;
}


void UTankAimingComponent::AimAt(FVector& HitLocation, float LaunchSpeed)
{
	if (!BarrelComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Barrel Component Found: %s"), *GetOwner()->GetName())
			return;
	}
	if (!TurretComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Turret Component Found: %s"), *GetOwner()->GetName())
			return;
	}
	FVector SuggestedVelocity;
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, SuggestedVelocity, BarrelComponent->GetSocketLocation(FName("Muzzle")), HitLocation, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace);
	if (bHaveAimSolution)
	{
		auto DesiredAimDirection = SuggestedVelocity.GetSafeNormal();
		MoveBarrel(DesiredAimDirection);
		
	}
	else
	{
		
	}

}

bool UTankAimingComponent::MoveBarrel(FVector BarrelDirection)
{
	//Translate target vector to rotation.
	auto BarrelRotation = BarrelComponent->GetForwardVector().Rotation();
	auto AimAsRotator = BarrelDirection.ToOrientationRotator();
	auto DeltaElevationRotator = AimAsRotator - BarrelRotation;
	auto TurretRotation = TurretComponent->GetForwardVector().Rotation();
	auto DeltaDirectionRotator = AimAsRotator - TurretRotation;
	

	BarrelComponent->Elevate(DeltaElevationRotator.Pitch);
	TurretComponent->Rotate(DeltaDirectionRotator.Yaw);


	return false;
}

