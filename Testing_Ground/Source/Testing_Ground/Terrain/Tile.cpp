// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include "Placeable.h"

// Sets default values
ATile::ATile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


void ATile::PlaceActors(TArray<TSubclassOf<APlaceable>> Placeables, int MinPlaced, int MaxPlaced)
{


	int counter = FMath::RandRange(MinPlaced, MaxPlaced);

	for (size_t i = 0; i < counter; i++)
	{
		int randomIndex = FMath::RandRange(0, (Placeables.Num() - 1));
		TSubclassOf<APlaceable> Placeable = Placeables[randomIndex];
		if (Placeable == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Placeable was null"))
				return;
		}
		APlaceable* templatePlaceable = Placeable.GetDefaultObject();
		float rotation = FMath::RandRange(-180.f, 180.f);
		float randomizedScale = FMath::RandRange(templatePlaceable->MinimumScale, templatePlaceable->MaximumScale);
		float scaledRadius = templatePlaceable->Scaleable ? templatePlaceable->Radius * randomizedScale : templatePlaceable->Radius;
		FVector* EmptyPoint = GetEmptyPoint(scaledRadius);
		if (EmptyPoint == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Could not find valid place point"))
				continue;
		}

		PlaceActor(Placeable, *EmptyPoint, rotation, randomizedScale);
	}



	return;
}

bool ATile::CastSphere(FVector Location, float Radius)
{
	FHitResult hitResult;
	auto result = GetWorld()->SweepSingleByChannel(hitResult, Location, Location, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(Radius));
	FColor Color;
	Color = result ? FColor::Red : FColor::Green;
	//DrawDebugSphere(GetWorld(), Location, Radius*30, 5, Color, true);
	return result;
}

FVector* ATile::GetEmptyPoint(float Radius)
{
	FVector min = FVector(0, -2000, 0);
	FVector max = FVector(4000, 2000, 0);
	FBox* Box = new FBox(min, max);
	Box->MoveTo(GetActorLocation());
	for (size_t i = 0; i < 100; i++)
	{

		candidatePoint = FMath::RandPointInBox(*Box);

		if (!CastSphere(candidatePoint, Radius))
		{


			return &candidatePoint;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Attempt failed"))
		return nullptr;
}

void ATile::PlaceActor(TSubclassOf<APlaceable> Placeable, FVector PlacePoint, float Rotation, float Scale)
{
	APlaceable* PlacedActor = GetWorld()->SpawnActor<APlaceable>(Placeable);
	if (PlacedActor != nullptr)
	{
		PlacedActor->SetActorRelativeLocation(PlacePoint);
		PlacedActor->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
		PlacedActor->SetActorRotation(FRotator(0.f, Rotation, 0.f));
		if (PlacedActor->Scaleable) PlacedActor->SetActorScale3D(FVector(Scale));
	}
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
