// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"


// Sets default values
ATile::ATile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


void ATile::PlaceActors(TSubclassOf<AActor> Placeable, int MinPlaced, int MaxPlaced, float Radius)
{
	TArray<FVector> pointCollection;

	//AActor* PlacedActor;
	if (Placeable == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Placeable class was null"))
			return;
	}
	int counter = FMath::RandRange(MinPlaced, MaxPlaced);
	for (size_t i = 0; i < counter; i++)
	{
		FVector* EmptyPoint = GetEmptyPoint(Radius);
		if (EmptyPoint == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Could not find valid place point"))
				return;
		}
		PlaceActor(Placeable, *EmptyPoint);
	}



	return;
}

bool ATile::CastSphere(FVector Location, float Radius)
{
	FHitResult hitResult;
	auto result = GetWorld()->SweepSingleByChannel(hitResult, Location, Location, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(Radius));
	FColor Color;
	Color = result ? FColor::Red : FColor::Green;
	DrawDebugSphere(GetWorld(), Location, Radius, 36, Color, true);
	return result;
}

FVector* ATile::GetEmptyPoint(float Radius)
{
	FVector min = FVector(0, -2000, 0);
	FVector max = FVector(4000, 2000, 0);
	FBox* Box = new FBox(min, max);
	for (size_t i = 0; i < 20; i++)
	{

		candidatePoint = FMath::RandPointInBox(*Box);

		if (CastSphere(candidatePoint, Radius))
		{
			candidatePoint;
			return &candidatePoint;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Attempt failed"))
	return nullptr;
}

void ATile::PlaceActor(TSubclassOf<AActor> Placeable, FVector PlacePoint)
{
	AActor* PlacedActor = GetWorld()->SpawnActor<AActor>(Placeable);
	PlacedActor->SetActorRelativeLocation(PlacePoint);
	PlacedActor->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
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

