// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "EnemyController.generated.h"

/**
 * 
 */
UENUM(BlueprintType, Category = "AI State")
enum EAIState
{
	ROAMING,
	CHASE,
	ATTACK
};

UCLASS()
class DUNGEONCRAWLER_API AEnemyController : public AAIController
{
	GENERATED_BODY()
	
	
public:
	AEnemyController();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		TEnumAsByte<EAIState> State;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		bool IsAttacking = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsRangeAttacking = false;

	UFUNCTION()
		virtual void Roaming(float DeltaTime);
	UFUNCTION()
		virtual void PerceptionSenseUpdate(TArray<AActor*> testActors);

	UFUNCTION()
		void BossAttack();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
		class UAIPerceptionComponent *AIPerception;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
		class UAISenseConfig_Sight *SightConfig;

	UFUNCTION(BlueprintCallable, Category=Distance)
		float GetDistanceToPlayer();
private:
	//Behavior Tree Components
	class UBehaviorTree *BehaviorTree;
	class UBlackboardComponent *BlackboardComp;

	class AEnemyCharacter *Enemy;
	class ADungeonCrawlerCharacter *Player;

	FVector RoamLocation;
	FVector SpawnLocation;

	// Blackboard Key Variables
	FName SelfActor_Key;
	FName RoamLocation_Key;
	FName EnemyState_Key;
	FName Player_Key;
	FName Distance_Key;

	float IdleCounter = 0.0f;
	bool FirstLocation = false;
	bool PlayerSpotted = false;

	float AttackTimer = 1.5f;
	float RangetAttackTimer = 0.0f;
	float RandRangeTimer = FMath::RandRange(4.5f, 6.5f);
	float Distance = 0.0f;
};
