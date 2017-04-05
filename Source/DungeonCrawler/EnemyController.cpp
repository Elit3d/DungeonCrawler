// Fill out your copyright notice in the Description page of Project Settings.

#include "DungeonCrawler.h"
#include "EnemyController.h"

/* AI Specific includes */
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISense_Sight.h"

#include "EnemyCharacter.h"
#include "DungeonCrawlerCharacter.h"

AEnemyController::AEnemyController()
{
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception Component"));
	AIPerception->OnPerceptionUpdated.AddDynamic(this, &AEnemyController::PerceptionSenseUpdate);
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = false;
	SightConfig->SightRadius = 1500.0f;
	SightConfig->LoseSightRadius = 2000.0f;
	AIPerception->ConfigureSense(*SightConfig);

	SelfActor_Key = "SelfActor";
	RoamLocation_Key = "RoamLocation";
	EnemyState_Key = "EnemyState";
	Player_Key = "Player";
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

	Player = Cast<ADungeonCrawlerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	switch (State)
	{
	case ROAMING:
		Roaming(DeltaTime);
		State = EAIState::ROAMING;
		Blackboard->SetValueAsEnum(EnemyState_Key, EAIState::ROAMING);
		break;
	case CHASE:
		break;
	case ATTACK:
		break;
	}

	if (Player != nullptr)
	{
		if (Enemy != nullptr)
		{
			AttackTimer += DeltaTime;
			float Distance = Player->GetDistanceTo(Enemy);

			if (Distance <= 300.f && PlayerSpotted /*&& Enemy->AttackComponent->*/) // might want to change this based off who is attacking
			{
				if (AttackTimer >= 3.0f) // might want to change this based off who is attacking
				{
					AttackTimer = 0.0f;
					IsAttacking = true;
					//State = EAIState::ATTACK;
					//Blackboard->SetValueAsEnum(EnemyState_Key, EAIState::ATTACK);
					Enemy->EnemyAttack();
				}
			}
			else if (PlayerSpotted)
			{
				Enemy->EnemySummon();
			}
			//UE_LOG(LogTemp, Warning, TEXT("%f"), Distance);
		}
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

	//float Distance = Enemy->GetActorLocation().Dist(Enemy->GetActorLocation(), Player->GetActorLocation());

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
	FActorPerceptionBlueprintInfo Info;

	for (int i = 0; i < testActors.Num(); i++)
	{
		GetAIPerceptionComponent()->GetActorsPerception(testActors[i], Info);

		if (Info.LastSensedStimuli.Num() > 0)
		{
			const FAIStimulus Stimulus = Info.LastSensedStimuli[0];

			if (Stimulus.WasSuccessfullySensed())
			{
				// Player in sight
				Player = Cast<ADungeonCrawlerCharacter>(Info.Target);

				if (Player != nullptr)
				{
					PlayerSpotted = true;
					//DelayTimer = 0.0f; // Reset delay timer

					State = EAIState::CHASE;
					BlackboardComp->SetValueAsEnum(EnemyState_Key, EAIState::CHASE);
					BlackboardComp->SetValueAsObject(Player_Key, Player);
				}
			}
			//else
			//{
			//	Guard = Cast<AGuardCharacter>(Info.Target);
			//	Employee = Cast<AEmployeeCharacter>(Info.Target);
			//	// Player out of sight
			//	if (Info.Target == Guard || Info.Target == Employee)
			//	{
			//		// Does not set LastKnownLocation to guard or employee postition
			//	}
			//	else
			//	{
			//		// Sets its to player position
			//		PlayerSpotted = false;
			//		//DetectionCounter = 0.0f;
			//		//StartDetectionCounter = false;
			//		LastKnownLocation = Stimulus.StimulusLocation; // Set last known location
			//		AIState = EAIState::SEARCH; // Change state
			//		BlackboardComp->SetValueAsEnum(EnumKey_Key, EAIState::SEARCH); // Update state in BB
			//	}
			//}
		}
	}
}
