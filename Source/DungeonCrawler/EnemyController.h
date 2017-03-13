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

	UFUNCTION()
		void Roaming(float DeltaTime);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
		class UAIPerceptionComponent *AIPerception;

	UFUNCTION()
		void PerceptionSenseUpdate(TArray<AActor*> testActors);
private:
	//Behavior Tree Components
	class UBehaviorTree *BehaviorTree;
	class UBlackboardComponent *BlackboardComp;

	class AEnemyCharacter *Enemy;

	FVector RoamLocation;
	FVector SpawnLocation;

	// Blackboard Key Variables
	FName SelfActor_Key;
	FName RoamLocation_Key;
	FName EnemyState_Key;

	float IdleCounter = 0.0f;
	bool FirstLocation = false;
};
