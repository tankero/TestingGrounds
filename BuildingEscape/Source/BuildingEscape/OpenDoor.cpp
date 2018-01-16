// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"



// Sets default values for this component's properties

UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	AActor* Owner = GetOwner();
	FString OwnerName = GetOwner()->GetName();
	FString Vector = GetOwner()->GetActorLocation().ToString();

	UE_LOG(LogTemp, Warning, TEXT("Position Report Logging in on %s at position %s"), *OwnerName, *Vector);
	auto Rotation = GetOwner()->GetTransform().GetRotation();
	UE_LOG(LogTemp, Warning, TEXT("Rotation of door set to %s"), *Rotation.ToString());
	GetOwner()->SetActorRotation(FRotator{ 0.0f, -135.0f, 0.0f });
	UE_LOG(LogTemp, Warning, TEXT("Rotation of door set to %s"), *Rotation.ToString());
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	// ...
}

