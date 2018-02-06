// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "TankAimingComponent.generated.h"



class AProjectile;
class UTankBarrel;
class UTankTurret;

UENUM()
enum class EFiringStatus : uint8
{
	Reloading,
	Aiming,
	Locked

};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTankAimingComponent();
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void InitializeAimingComponent(UTankBarrel* Barrel, UTankTurret* Turret);
	void SetBarrelReference(UTankBarrel* BarrelToSet);
	void SetTurretReference(UTankTurret* TurretToSet);
	void AimAt(FVector HitLocation);
	bool MoveBarrel(FVector BarrelDirection);
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float LaunchSpeed = 10000.f;
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float ReloadTimeInSeconds = 3;
	double LastFireTime = 0;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBlueprint = nullptr;
	UFUNCTION(BlueprintCallable, Category = "Firing")
		void Fire();
protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringStatus FiringStatus = EFiringStatus::Reloading;

private:
	UTankBarrel * BarrelComponent = nullptr;
	UTankTurret* TurretComponent = nullptr;
	float AimingLaunchSpeed;


};
