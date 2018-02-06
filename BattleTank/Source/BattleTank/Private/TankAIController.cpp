// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankAimingComponent.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	auto ControlledTank = Cast<ATank>(GetPawn());
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (PlayerTank)
	{
		MoveToActor(PlayerTank, AcceptanceRadius);

		ControlledTank->AimingComponent->AimAt(PlayerTank->GetActorLocation());
		ControlledTank->AimingComponent->Fire();
	}
}

ATankAIController::ATankAIController()
{
	PrimaryActorTick.bCanEverTick = true;
}


