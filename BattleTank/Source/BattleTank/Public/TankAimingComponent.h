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
	Locked,
	OutOfAmmo

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

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		int32 AmmoMagazine = 5;

	UFUNCTION(BlueprintCallable, Category = "Firing")
		int32 GetCurrentAmmoCount() const;

	EFiringStatus GetFiringStatus() const;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringStatus FiringStatus = EFiringStatus::Reloading;

private:
	bool IsBarrelMoving() const;
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	UTankBarrel * BarrelComponent = nullptr;
	UTankTurret* TurretComponent = nullptr;
	FVector DesiredAimDirection;
	float AimingLaunchSpeed;
	int32 CurrentAmmoCount;

};
