// Fill out your copyright notice in the Description page of Project Settings.
#pragma once


#include "TankPlayerController.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayController not possesing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s"), *(ControlledTank->GetName()));
	}
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AimTowardsCrosshair();
	

}

ATankPlayerController::ATankPlayerController()
{
	
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }
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
			GetControlledTank()->AimAt(OutHitLocation);
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
