// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class DUNGEONCRAWLER_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere, Category="Health Component")
		class UAIHealthComponent *HealthComponent;
	UPROPERTY(EditAnywhere, Category = "Attack Component")
		class UAIAttackComponent *AttackComponent;

	void EnemyAttack();
	void EnemySummon();
	void EnemyRangeAttack();

	UFUNCTION(BlueprintCallable, Category="Health")
		float GetHealth();
	void SetHealth(float _health);

	void HandleSummoning();
	UFUNCTION(BlueprintCallable, Category=Summon)
		void SummonSpawning(); // To call in anim BP only

	UPROPERTY(EditAnywhere, Category = "Summoning")
		bool bEnemyCanSummon = false;
	UPROPERTY(BlueprintReadWrite)
		bool bSummonOtherEnemy = false;
	UPROPERTY(EditAnywhere, Category = "Summoning")
		int MaxSummon = 0;
	UPROPERTY(EditAnywhere, Category = "Summoning")
		TSubclassOf<AEnemyCharacter> ThisCharacter;
	UPROPERTY(EditAnywhere, Category = "Range Actor")
		TSubclassOf<AActor> RangeProjectile;

	float counter = 0;
private:
	class ADungeonCrawlerCharacter *Player;
	TArray<AActor*> SummonedArray;
	FVector EnemyLocation;
	FRotator ForwardSpawn;
	float CastTimer = 0.0f;
};
