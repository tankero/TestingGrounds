// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ActorComponent.h"





// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;


	// ...
}

bool UTankAimingComponent::IsBarrelMoving() const
{
	if (!ensure(BarrelComponent))
	{
		return false;
	}
	return !BarrelComponent->GetForwardVector().Equals(DesiredAimDirection, 0.05);
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();
	CurrentAmmoCount = AmmoMagazine;
}
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringStatus = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringStatus = EFiringStatus::Aiming;
	}
	else
	{
		FiringStatus = EFiringStatus::Locked;
	}
	if (CurrentAmmoCount <= 0)
	{
		FiringStatus = EFiringStatus::OutOfAmmo;
	}
}

void UTankAimingComponent::InitializeAimingComponent(UTankBarrel * Barrel, UTankTurret * Turret)
{
	BarrelComponent = Barrel;
	TurretComponent = Turret;
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	BarrelComponent = BarrelToSet;

}

void UTankAimingComponent::SetTurretReference(UTankTurret * TurretToSet)
{
	TurretComponent = TurretToSet;
}


void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(BarrelComponent))
	{
		return;
	}
	if (!ensure(TurretComponent))
	{
		return;
	}
	AimingLaunchSpeed = LaunchSpeed;
	FVector SuggestedVelocity;
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, SuggestedVelocity, BarrelComponent->GetSocketLocation(FName("Muzzle")), HitLocation, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace);
	if (bHaveAimSolution)
	{
		DesiredAimDirection = SuggestedVelocity.GetSafeNormal();
		MoveBarrel(DesiredAimDirection);

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
	if (FMath::Abs(DeltaDirectionRotator.Yaw) > 180.f)
	{
		TurretComponent->Rotate(-DeltaDirectionRotator.Yaw);
	}
	else
	{
		TurretComponent->Rotate(DeltaDirectionRotator.Yaw);
	}



	return false;
}

void UTankAimingComponent::Fire()
{
	if (FiringStatus != EFiringStatus::Reloading && CurrentAmmoCount > 0)
	{
		CurrentAmmoCount--;
		if (!ensure(ProjectileBlueprint))
		{
			return;
		}
		
		
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, BarrelComponent->GetSocketLocation("Muzzle"), BarrelComponent->GetSocketRotation("Muzzle"));
		Projectile->LaunchProjectile(AimingLaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();

		

	}

}

int32 UTankAimingComponent::GetCurrentAmmoCount() const
{
	return CurrentAmmoCount;
}

EFiringStatus UTankAimingComponent::GetFiringStatus() const
{
	return FiringStatus;
}





