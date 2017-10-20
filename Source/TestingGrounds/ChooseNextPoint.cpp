// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Classes/AIController.h "
#include "PatrolRoute.h"


EBTNodeResult::Type UChooseNextPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//GetPatrolPoints
	auto ControlledPawn = OwnerComp.GetAIOwner()->GetControlledPawn();
	auto PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRoute>();

	if (!ensure(PatrolRoute)) { return EBTNodeResult::Failed; }

	
	//SetNextMovePointNumber
	auto TargetPts = PatrolRoute->GetTargetPts();
	if (!ensure(TargetPts.Num())) { return EBTNodeResult::Failed; }

	auto Blackboard = OwnerComp.GetBlackboardComponent();
	auto Index = Blackboard->GetValueAsInt(IndexKey.SelectedKeyName);
	Blackboard->SetValueAsObject(NextMovePoint.SelectedKeyName, TargetPts[Index]);

	//CycleIndex
	auto NextMoveNumber=(Index+1)% TargetPts.Num();
	
	Blackboard->SetValueAsInt(IndexKey.SelectedKeyName,NextMoveNumber );

	//UE_LOG(LogTemp,Warning,TEXT("aa %i"),Index)
	return EBTNodeResult::Succeeded;
}