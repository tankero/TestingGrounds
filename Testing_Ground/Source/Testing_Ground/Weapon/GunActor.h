// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GunActor.generated.h"

UCLASS(config = Game)
class AGunActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGunActor();
	/** Fires a projectile. */
	void OnFire();

	UFUNCTION(BlueprintCallable)
		void FireWeapon();
	
	UFUNCTION(BlueprintCallable)
		void StopFiring();

	UFUNCTION()
		void OnReload();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* FP_Gun;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USceneComponent* FP_MuzzleLocation;

	/** Projectile class to spawn */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
		TSubclassOf<class ATesting_GroundProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class UAnimMontage* P1FireAnimation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class UAnimMontage* P3FireAnimation;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
		class UAnimInstance* P1AnimInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
		class UAnimInstance* P3AnimInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
		float FiringRate = 0.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
		bool ReadyToFire;



private:
	
	FTimerHandle ReloadTimerHandle;

	bool Firing;

};
