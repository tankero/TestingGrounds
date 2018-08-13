// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrolRouteComponent.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto PatrolRouteComponent = OwnerComp.GetAIOwner()->GetPawn()->FindComponentByClass<UPatrolRouteComponent>();
	if (!ensure(PatrolRouteComponent))
	{
		return EBTNodeResult::Failed;
	}
	auto PatrolPoints = PatrolRouteComponent->GetPatrolPoints();
	auto PatrolLength = PatrolPoints.Num();
	if (!ensure(PatrolLength > 0))
	{
		return EBTNodeResult::Failed;
	}
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	BlackboardComp->SetValueAsObject(ObjectKey.SelectedKeyName, PatrolPoints[Index]);
	Index++;
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, (Index % PatrolLength));
	
	return EBTNodeResult::Succeeded;
}
