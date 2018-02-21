// TankeroProductions

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 *
 */


class UTankAimingComponent;

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
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent* AimCompRef);
private:

	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
		void OnTankDeath();


	UTankAimingComponent* AimingComponent;
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector&) const;
	bool GetLookDirection(FVector2D CrosshairsLocation, FVector & LookDirection) const;
	bool GetLookVectorHitLocation(FVector Direction, FVector & HitLocation) const;
};


