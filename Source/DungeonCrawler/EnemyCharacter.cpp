// Fill out your copyright notice in the Description page of Project Settings.

#include "DungeonCrawler.h"
#include "EnemyCharacter.h"

#include "AIHealthComponent.h"
#include "AIAttackComponent.h"
// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UAIHealthComponent>(TEXT("Health Component"));
	AttackComponent = CreateDefaultSubobject<UAIAttackComponent>(TEXT("Attack Component"));
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemyCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void AEnemyCharacter::EnemyAttack()
{
	AttackComponent->EnemyAttack();
}
