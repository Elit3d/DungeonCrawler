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

#include "AIAttackComponent.h"
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
	Distance_Key = "Distance";
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
	Enemy = Cast<AEnemyCharacter>(Blackboard->GetValueAsObject(SelfActor_Key)); // Set guard as selfactor from BB

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
			RangetAttackTimer += DeltaTime;
			float Distance = Player->GetDistanceTo(Enemy);

			if (PlayerSpotted)
			{
				if (Enemy->GetHealth() > 0)
				{
					FRotator LookAtPlayer = (Player->GetActorLocation() - Enemy->GetActorLocation()).Rotation();
					LookAtPlayer.Pitch = 0.0f;
					Enemy->SetActorRotation(LookAtPlayer);
					
					float RandTimer = FMath::RandRange(1.5f, 3.5f);

					if (AttackTimer >= 2.0f)
					{
						AttackTimer = 0.0f;
						IsAttacking = true;
						Enemy->EnemyAttack();
					}

					if (RangetAttackTimer >= RandRangeTimer)
					{
						RandRangeTimer = FMath::RandRange(4.5f, 6.5f);
						RangetAttackTimer = 0.0f;
						IsRangeAttacking = true;
						Enemy->EnemyRangeAttack();
					}

					Enemy->EnemySummon();
				}
			}
		}
	}
}

void AEnemyController::Roaming(float DeltaTime)
{
	Enemy = Cast<AEnemyCharacter>(Blackboard->GetValueAsObject(SelfActor_Key)); // Set guard as selfactor from BB

	UNavigationSystem* NavSys = UNavigationSystem::GetCurrent(GetWorld());

	if (Enemy != nullptr)
	{
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
		}
	}
}

void AEnemyController::BossAttack()
{
}

float AEnemyController::GetDistanceToPlayer()
{
	if (Player != nullptr && Enemy != nullptr)
		return Player->GetDistanceTo(Enemy);
	else
		return 0;
}
