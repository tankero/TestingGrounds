// TankeroProductions
#pragma once


#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "GameFramework/PlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
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



void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; }
	FVector HitLocation;
	GetSightRayHitLocation(HitLocation);
	

}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D crosshairsLocation = { ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation };
	FVector LookDirection;
	if (GetLookDirection(crosshairsLocation, LookDirection))
	{
		if (GetLookVectorHitLocation(LookDirection, OutHitLocation))
		{
			AimingComponent->AimAt(OutHitLocation);
		}
	}
	return true;
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
		ECC_Visibility
	))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	
	return false;
}
