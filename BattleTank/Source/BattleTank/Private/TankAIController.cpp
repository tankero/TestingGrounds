// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"
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
		if (AimingComponent->GetFiringStatus() == EFiringStatus::Locked)
		{
			AimingComponent->Fire();
		}
	}
}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank))
		{
			return;
		}
		PossessedTank->OnTankDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
	}
}

void ATankAIController::OnTankDeath()
{
	if (!ensure(GetPawn()))
	{
		return;
	}
	GetPawn()->DetachFromControllerPendingDestroy();
}

ATankAIController::ATankAIController()
{
	PrimaryActorTick.bCanEverTick = true;
}


