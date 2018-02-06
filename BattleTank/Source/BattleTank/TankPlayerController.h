// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 *
 */

class ATank;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	ATankPlayerController();
	UPROPERTY(EditAnywhere)
		float CrossHairXLocation = 0.5;
	UPROPERTY(EditAnywhere)
		float CrossHairYLocation = 0.3;
	UPROPERTY(EditAnywhere)
		float LineTraceRange = 10000000.f;

protected:
	UFUNCTION(BluePrintCallable, Category = "Setup")
		ATank * GetControlledTank() const;
private:


	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector&) const;
	bool GetLookDirection(FVector2D CrosshairsLocation, FVector & LookDirection) const;
	bool GetLookVectorHitLocation(FVector Direction, FVector & HitLocation) const;
};


