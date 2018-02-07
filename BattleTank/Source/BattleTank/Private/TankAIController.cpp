// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "GameFramework/PlayerController.h"



void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetPawn();
	if (!ensure (ControlledTank))
	{
		return;
	}
	AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	auto ControlledTank = GetPawn();
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (PlayerTank)
	{
		MoveToActor(PlayerTank, AcceptanceRadius);

		AimingComponent->AimAt(PlayerTank->GetActorLocation());
		AimingComponent->Fire();
	}
}

ATankAIController::ATankAIController()
{
	PrimaryActorTick.bCanEverTick = true;
}


