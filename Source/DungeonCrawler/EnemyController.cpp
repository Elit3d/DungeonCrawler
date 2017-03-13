// Fill out your copyright notice in the Description page of Project Settings.

#include "DungeonCrawler.h"
#include "EnemyController.h"

/* AI Specific includes */
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Perception/AIPerceptionComponent.h"

#include "EnemyCharacter.h"

AEnemyController::AEnemyController()
{
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

	AIPerception = GetAIPerceptionComponent();
	AIPerception->OnPerceptionUpdated.AddDynamic(this, &AEnemyController::PerceptionSenseUpdate);

	SelfActor_Key = "SelfActor";
	RoamLocation_Key = "RoamLocation";
	EnemyState_Key = "EnemyState";
}

void AEnemyController::BeginPlay()
{
	Super::BeginPlay();

	State = EAIState::ROAMING;
	Blackboard->SetValueAsEnum(EnemyState_Key, EAIState::ROAMING);
}

void AEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (State)
	{
	case ROAMING:
		Roaming(DeltaTime);
		Blackboard->SetValueAsEnum(EnemyState_Key, EAIState::ROAMING);
		break;
	case CHASE:
		break;
	case ATTACK:
		break;
	}
}

void AEnemyController::Roaming(float DeltaTime)
{
	Enemy = Cast<AEnemyCharacter>(Blackboard->GetValueAsObject(SelfActor_Key)); // Set guard as selfactor from BB

	UNavigationSystem* NavSys = UNavigationSystem::GetCurrent(GetWorld());

	/*if (Enemy->GetActorLocation().Equals(SpawnLocation, 100.0f))
	{
		RoamLocation = NavSys->GetRandomReachablePointInRadius(GetWorld(), SpawnLocation, 200.0f, NULL, NULL);
		Blackboard->SetValueAsVector(RoamLocation_Key, RoamLocation);
	}*/
	if (FirstLocation == false)
	{
		FirstLocation = true;
		RoamLocation = NavSys->GetRandomReachablePointInRadius(GetWorld(), Enemy->GetActorLocation(), 50000.0f, NULL, NULL);
		Blackboard->SetValueAsVector(RoamLocation_Key, RoamLocation);
	}
	else if (Enemy->GetActorLocation().Equals(RoamLocation, 100.0f)) // guard location equal to target location with tolerence
	{
		IdleCounter += DeltaTime;
		if (IdleCounter >= 3.0f)
		{
			IdleCounter = 0.0f;
			RoamLocation = NavSys->GetRandomReachablePointInRadius(GetWorld(), FVector(15000.0f, 15000.0f, Enemy->GetActorLocation().Z), 50000.0f, NULL, NULL);
			Blackboard->SetValueAsVector(RoamLocation_Key, RoamLocation);
		}
	}
}

void AEnemyController::PerceptionSenseUpdate(TArray<AActor*> testActors)
{
	// Add sense stuff here
}
