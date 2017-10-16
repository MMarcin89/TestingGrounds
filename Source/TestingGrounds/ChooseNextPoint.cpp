// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Classes/AIController.h "
#include "PatrollingGuard.h"


EBTNodeResult::Type UChooseNextPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//GetPatrolPoints
	auto AIController = OwnerComp.GetAIOwner();
	auto ControlledPawn = AIController->GetControlledPawn();
	auto Guard = Cast<APatrollingGuard>(ControlledPawn);
	auto TargetPoints = Guard->TargetPoints;
	//SetNextMovePointNumber
	auto Blackboard = OwnerComp.GetBlackboardComponent();
	auto Index = Blackboard->GetValueAsInt(IndexKey.SelectedKeyName);
	Blackboard->SetValueAsObject(NextMovePoint.SelectedKeyName, TargetPoints[Index]);

	//CycleIndex
	auto NextMoveNumber=(Index+1)% TargetPoints.Num();
	
	Blackboard->SetValueAsInt(IndexKey.SelectedKeyName,NextMoveNumber );

	//UE_LOG(LogTemp,Warning,TEXT("aa %i"),Index)
	return EBTNodeResult::Succeeded;
}