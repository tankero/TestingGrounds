// Fill out your copyright notice in the Description page of Project Settings.

#include "GunActor.h"
#include "../Testing_GroundProjectile.h"
#include "Components/InputComponent.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGunActor::AGunActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGunActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGunActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGunActor::OnFire()
{

	// try and fire a projectile
	if (ProjectileClass != NULL)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			FVector SpawnLocation =  FP_MuzzleLocation->GetComponentLocation();

			const FRotator SpawnRotation = FP_MuzzleLocation->GetComponentRotation();

			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			// spawn the projectile at the muzzle
			World->SpawnActor<ATesting_GroundProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);

		}
	}
	// try and play the sound if specified
	if (FireSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	// try and play a firing animation if specified
	if (FireAnimation != NULL)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = FP_Gun->GetAnimInstance();
		if (AnimInstance != NULL)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}

