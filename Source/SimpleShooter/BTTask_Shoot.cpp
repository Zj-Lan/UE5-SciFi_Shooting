// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "AIController.h"
#include "ShooterCharacter.h"

UBTTask_Shoot::UBTTask_Shoot()
{
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type ExecuteTask = Super::ExecuteTask(OwnerComp, NodeMemory);

	Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn())->Shoot();
	
	return ExecuteTask;
}
