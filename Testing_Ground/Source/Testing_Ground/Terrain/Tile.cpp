// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"


// Sets default values
ATile::ATile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


void ATile::PlaceActors(TSubclassOf<AActor> Placeable)
{
	TArray<FVector> pointCollection;
	FBox* Box;
	FVector Origin;
	AActor* PlacedActor;

	if (Placeable == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Placeable class was null"))
			return;
	}

	if (!ensure(Origin != FVector(0, 0, 0)))
	{
		UE_LOG(LogTemp, Warning, TEXT("Origin failed to set properly"))
			return;
	};
	FVector min = FVector(0, -2000, 0);
	FVector max = FVector(4000, 2000, 0);
	Box = new FBox(min, max);
	for (size_t i = 0; i < 2; i++)
	{
		FVector candidatePoint = FMath::RandPointInBox(*Box);
		bool invalidPoint = false;

		do
		{
			invalidPoint = FVector::Distance(candidatePoint, min) < 5.f || FVector::Distance(candidatePoint, max) < 5.f;
			if (PlaceablesArray.Num() > 0 && !invalidPoint)
			{
				for (size_t i = 0; i < PlaceablesArray.Num() - 1; i++)
				{
					invalidPoint = (FVector::Distance(PlaceablesArray[i]->GetActorLocation(), candidatePoint) < 5.f);

				}

			}

		} while (invalidPoint);

		pointCollection.Add(candidatePoint);
		FVector retrievedPoint = pointCollection.Last();
		PlacedActor = GetWorld()->SpawnActor<AActor>(Placeable);
		PlacedActor->SetActorRelativeLocation(candidatePoint);
		PlacedActor->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
		PlaceablesArray.Add(PlacedActor);

	}


	return;
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

