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

	float GetHealth();
	void SetHealth(float _health);
private:
	class ADungeonCrawlerCharacter *Player;
};
