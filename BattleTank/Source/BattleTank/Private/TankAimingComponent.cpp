// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ActorComponent.h"





// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

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
	FVector suggestedVelocity;
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, suggestedVelocity, BarrelComponent->GetSocketLocation(FName("Muzzle")), HitLocation, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace);
	if (bHaveAimSolution)
	{
		auto DesiredAimDirection = suggestedVelocity.GetSafeNormal();
		MoveBarrel(DesiredAimDirection);
		UE_LOG(LogTemp, Warning, TEXT("%f: Firing Solution Found by %s"), GetWorld()->GetTimeSeconds(), *GetOwner()->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%f: No firing solution found by: %s"), GetWorld()->GetTimeSeconds(), *GetOwner()->GetName());
	}
	
}

bool UTankAimingComponent::MoveBarrel(FVector BarrelDirection)
{
	//Translate target vector to rotation.

	auto BarrelRotation = BarrelComponent->GetForwardVector().Rotation();
	auto AimAsRotator = BarrelDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotation;


	BarrelComponent->Elevate(DeltaRotator.Pitch);
			

	return false;
}

