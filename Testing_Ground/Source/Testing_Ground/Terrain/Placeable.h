// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Placeable.generated.h"

UCLASS()
class TESTING_GROUND_API APlaceable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlaceable();

	UPROPERTY(EditAnywhere, Category = "Setup" )
		bool Scaleable = false;

	UPROPERTY(EditAnywhere, Category = "Setup")
		float Radius = 1.f;

	UPROPERTY(EditAnywhere, Category = "Setup")
		float MinimumScale = 1.f;

	UPROPERTY(EditAnywhere, Category = "Setup")
		float MaximumScale = 1.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
