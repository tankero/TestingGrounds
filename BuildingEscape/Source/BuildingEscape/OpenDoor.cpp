// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Components/SceneComponent.h"





// Sets default values for this component's properties

UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UOpenDoor::OpenDoor()
{
	FString RotationString = GetOwner()->GetTransform().GetRotation().ToString();
	
	auto Rotation = GetOwner()->GetTransform().GetRotation();
	GetOwner()->SetActorRotation(FRotator{ 0.f, OpenAngle, 0.f });
	RotationString = GetOwner()->GetTransform().GetRotation().ToString();
	
}
void UOpenDoor::CloseDoor()
{
	FString RotationString = GetOwner()->GetTransform().GetRotation().ToString();
	auto Rotation = GetOwner()->GetTransform().GetRotation();
	
	GetOwner()->SetActorRotation(FRotator{ 0.f, ClosedAngle, 0.f });
	RotationString = GetOwner()->GetTransform().GetRotation().ToString();
	
}
// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	ActorTrigger = GetWorld()->GetFirstPlayerController()->GetPawn();
	Owner = GetOwner();
	OwnerName = Owner->GetName();
	ClosedAngle = Owner->GetActorRotation().Yaw;
	OpenAngle = ClosedAngle + 90.0f;
	
	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (PressurePlate->IsOverlappingActor(ActorTrigger) && !bOpened)
	{
		bOpened = true;
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();

		
	}
	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorClosedDelay && bOpened)
	{
		bOpened = false;
		CloseDoor();
	}
	
	// ...
}

