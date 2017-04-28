// Fill out your copyright notice in the Description page of Project Settings.

#include "DungeonCrawler.h"
#include "EnemyCharacter.h"

#include "AIHealthComponent.h"
#include "AIAttackComponent.h"
#include "DungeonCrawlerCharacter.h"
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

	counter += DeltaTime;

	//UE_LOG(LogTemp, Warning, TEXT("%f timer"), counter);

	//EnemyAttack();

	if (GetHealth() <= 0)
	{
		//Destroy();
	}
}

void AEnemyCharacter::EnemyAttack()
{
	//AttackComponent->EnemyAttack();

	Player = Cast<ADungeonCrawlerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	switch (AttackComponent->AttackType)
	{
	case EAttackType::AT_Melee:
		//UE_LOG(LogTemp, Warning, TEXT("Attacking player...MELEE"));
		//t = 0;
		if (AttackComponent->RayCastAttack(GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 250.0f, this, Player))
		{
			//HIT TAKE DAMAGE
			//HealthComponent->SetHealth(HealthComponent->GetHealth() - 1); -- NOT THIS AS IT IS THE ENEMIES HEALTH AND NOT THE PLAYERS
		}
		break;
	case EAttackType::AT_Range:
		break;
	case EAttackType::AT_Magic:
		//UE_LOG(LogTemp, Warning, TEXT("Attacking player...MAGIC"));
		//t = 2;
		if (AttackComponent->RayCastAttack(GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 1000.0f, this, Player))
		{
		}
		break;
	}
}

void AEnemyCharacter::EnemySummon()
{
	// Handles summoning

	if (counter >= RandTimer)
	{
		HandleSummoning();
		RandTimer = FMath::RandRange(3, 10);
		counter = 0;
	}
}

void AEnemyCharacter::EnemyRangeAttack()
{
	switch (AttackComponent->AttackType)
	{
	case EAttackType::AT_Melee:
		break;
	case EAttackType::AT_Range:
		EnemyLocation = GetActorLocation();
		ForwardSpawn = GetActorForwardVector().Rotation();

		if (RangeProjectile != nullptr)
			GetWorld()->SpawnActor(RangeProjectile, &EnemyLocation, &ForwardSpawn);

		if (AttackComponent->RayCastAttack(GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 1000.0f, this, Player))
		{
			//HIT TAKE DAMAGE
			//Spawn projectile (dont deal direct damage here)
			//HealthComponent->SetHealth(HealthComponent->GetHealth() - 1); -- NOT THIS AS IT IS THE ENEMIES HEALTH AND NOT THE PLAYERS
		}
		break;
	case EAttackType::AT_Magic:
		break;
	}
}

float AEnemyCharacter::GetHealth()
{
	return HealthComponent->GetHealth();
}

void AEnemyCharacter::SetHealth(float _health)
{
	HealthComponent->SetHealth(_health);
}

void AEnemyCharacter::HandleSummoning()
{
	if (bEnemyCanSummon)
	{
		bSummonOtherEnemy = true;
	}
}

void AEnemyCharacter::SummonSpawning()
{
	FVector SummonLocation = GetActorLocation();
	FRotator SummonRotation = GetActorForwardVector().Rotation();
	AActor *Summon = GetWorld()->SpawnActor(ThisCharacter, &SummonLocation, &SummonRotation);
	SummonedArray.Push(Summon);
}