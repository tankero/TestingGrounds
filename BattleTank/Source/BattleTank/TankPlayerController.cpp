// TankeroProductions
#pragma once


#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (!GetPawn())
	{
		return;
	}
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure (AimingComponent))
	{
		return;
	}
	FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AimTowardsCrosshair();
	

}

ATankPlayerController::ATankPlayerController()
{
	
}

void ATankPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank))
		{
			return;
		}
		PossessedTank->OnTankDeath.AddUniqueDynamic(this, &ATankPlayerController::OnTankDeath);
	}
}

void ATankPlayerController::OnTankDeath()
{
	
	StartSpectatingOnly();
}


void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; }
	FVector HitLocation;
	bool bGotHitLocation = GetSightRayHitLocation(HitLocation);
	if (bGotHitLocation)
	{
		AimingComponent->AimAt(HitLocation);
	}

}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D crosshairsLocation = { ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation };
	FVector LookDirection;
	if (GetLookDirection(crosshairsLocation, LookDirection))
	{
		return GetLookVectorHitLocation(LookDirection, OutHitLocation);
		
	}
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D CrosshairsLocation, FVector& LookDirection) const
{
	FVector CameraPosition;
	return DeprojectScreenPositionToWorld
	(
		CrosshairsLocation.X,
		CrosshairsLocation.Y,
		CameraPosition,
		LookDirection
	);
}
bool ATankPlayerController::GetLookVectorHitLocation(FVector Direction, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (Direction * LineTraceRange);
	
	if (GetWorld()->LineTraceSingleByChannel
	(
		HitResult,
		StartLocation,
		EndLocation,
		ECC_Camera
	))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	
	return false;
}
