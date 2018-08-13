// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PatrolRouteComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TESTING_GROUND_API UPatrolRouteComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UFUNCTION()
	TArray<AActor*> GetPatrolPoints();

private:
	UPROPERTY(EditInstanceOnly, Category = "Patrol Route")
		TArray<AActor*> PatrolPoints;

	

};
