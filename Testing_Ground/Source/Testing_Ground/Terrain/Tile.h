// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Placeable.h"
#include "DrawDebugHelpers.h"
#include "Tile.generated.h"



UCLASS()
class TESTING_GROUND_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();


	UPROPERTY(BlueprintReadWrite, Category = "Setup")
		TArray<AActor*> PlaceablesArray;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void PlaceActors(TSubclassOf<AActor> Placeable, int MinPlaced, int MaxPlaced, float Radius);

private:

	bool CastSphere(FVector Location, float Radius);
	FVector *GetEmptyPoint(float Radius);
	void PlaceActor(TSubclassOf<AActor> Placeable, FVector PlacePoint);
	
	
};
