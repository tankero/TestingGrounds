// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"


// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


void ATile::PlaceActors()
{
	TArray<FVector> pointCollection;
	FBox* Box;
	TArray<UActorComponent*> MeshArray = GetComponentsByClass(UStaticMeshComponent::StaticClass());
	UStaticMeshComponent* Floor;
	FVector Origin;
	
	for (size_t i = 0; i < MeshArray.Num(); i++)
	{
		
		UE_LOG(LogTemp, Warning, TEXT("%s"), *MeshArray[i]->GetName());
		if (MeshArray[i]->ComponentHasTag("Floor"))
		{
			Floor = (UStaticMeshComponent*) MeshArray[i];
			Origin = Floor->GetComponentLocation();
			if (!ensure(Origin != FVector(0, 0, 0)))
			{
				UE_LOG(LogTemp, Warning, TEXT("Origin failed to set properly"))
					return;
			};
			Box = new FBox(Floor->GetStaticMesh()->GetBoundingBox());
			for (size_t i = 0; i < 5; i++)
			{
				pointCollection.Add(FMath::RandPointInBox(*Box));
				FVector retrievedPoint = pointCollection.Last() + Origin;
				PlaceablesArray.Add(GetWorld()->SpawnActor<AActor>(Placeable, FVector(retrievedPoint.X, retrievedPoint.Y, 60.f), FRotator::ZeroRotator));

			}
			
			return;
		}
	};
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	PlaceActors();
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

