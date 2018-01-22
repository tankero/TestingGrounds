// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Components/SceneComponent.h"
#include "Components/PrimitiveComponent.h"






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

	Owner = GetOwner();
	OwnerName = Owner->GetName();
	ClosedAngle = Owner->GetActorRotation().Yaw;
	OpenAngle +=ClosedAngle;

	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("The object named: %s doesn't have a Pressure Plate component"), *GetOwner()->GetName());
	}

}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (GetTotalMassOfActorsOnPlate() > TriggerMass && !bOpened)
	{
		bOpened = true;
		OnOpenRequest.Broadcast();
		
	}
	if (GetTotalMassOfActorsOnPlate() < TriggerMass && bOpened)
	{
		bOpened = false;
		OnCloseRequest.Broadcast();
	}

	// ...
}

float UOpenDoor::GetTotalMassOfActorsOnPlate() const
{
	float TotalMass = 0.f;

	TArray<AActor*> OverlappingActors;
	if (!PressurePlate)
	{
		return TotalMass;
	}
	PressurePlate->GetOverlappingActors(OverlappingActors);

	for (auto* actor : OverlappingActors)
	{
		UPrimitiveComponent* primitive = actor->FindComponentByClass<UPrimitiveComponent>();
		TotalMass += primitive->GetMass();
	}
	return TotalMass;
}

float UOpenDoor::GetOpenAngle()
{
	return OpenAngle;
}

float UOpenDoor::GetClosedAngle()
{
	return ClosedAngle;
}


