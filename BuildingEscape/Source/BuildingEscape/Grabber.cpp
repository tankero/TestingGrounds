// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "Grabber.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandleComponent();
	SetupInputComponent();

}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(TraceGrabberLineEnd());
	}
}

//Protect against missing Physics Handle Component
void UGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("The object named: %s has a grabber component but no Physics Handle!"), *GetOwner()->GetName());
	}
}

//Initialize Input for Grabber
void UGrabber::SetupInputComponent()
{
	Input = GetOwner()->FindComponentByClass<UInputComponent>();

	if (Input)
	{
		Input->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		Input->BindAction("Grab", IE_Released, this, &UGrabber::Drop);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("The object named: %s doesn't have an input component"), *GetOwner()->GetName());
	}

}

//Activate Physics Handle
void UGrabber::Grab()
{
	FHitResult grabbed = GetPhysicsBodyInReach();
	if (grabbed.IsValidBlockingHit())
	{
		auto ComponentToGrab = grabbed.GetComponent();
		PhysicsHandle->GrabComponent(
			ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation(),
			true);
	}
}

//Deactivate Physics Handle
void UGrabber::Drop()
{
	PhysicsHandle->ReleaseComponent();
}

//Ray-cast only when Physics Handle is activated
FHitResult UGrabber::GetPhysicsBodyInReach() const
{

	FVector PlayerLocation = GetOwner()->GetActorLocation();
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	FHitResult result;
	GetWorld()->LineTraceSingleByObjectType(result, PlayerLocation, TraceGrabberLineEnd(), FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParams);
	return result;
}

//Vector at the end of the physics handle
FVector UGrabber::TraceGrabberLineEnd() const
{
	FVector PlayerLocation;
	FRotator PlayerRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerLocation, PlayerRotation);
	FVector LineTraceEnd = PlayerLocation + (PlayerRotation.Vector() * Reach);
	return LineTraceEnd;
}
