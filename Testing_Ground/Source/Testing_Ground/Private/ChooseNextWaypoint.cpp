// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrollingGuard.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto OwnerAi = OwnerComp.GetAIOwner();
	auto OwnerGuard = Cast<APatrollingGuard>(OwnerAi->GetPawn());
	auto PatrolPoints = OwnerGuard->PatrolPoints;
	auto PatrolLength = PatrolPoints.Num();
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	BlackboardComp->SetValueAsObject(ObjectKey.SelectedKeyName, PatrolPoints[Index]);
	Index++;
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, (Index % PatrolLength));
	
	return EBTNodeResult::Succeeded;
}
