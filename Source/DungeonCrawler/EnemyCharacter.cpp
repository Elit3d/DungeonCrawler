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

	EnemyAttack();

	if (GetHealth() <= 0)
	{
		Destroy();
	}
}

void AEnemyCharacter::EnemyAttack()
{
	//AttackComponent->EnemyAttack();

	Player = Cast<ADungeonCrawlerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	switch (AttackComponent->AttackType)
	{
	case EAttackType::AT_Melee:
		UE_LOG(LogTemp, Warning, TEXT("Attacking player...MELEE"));

		if (AttackComponent->RayCastAttack(GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 250.0f, this, Player))
		{
			//HIT TAKE DAMAGE
			//HealthComponent->SetHealth(HealthComponent->GetHealth() - 1); -- NOT THIS AS IT IS THE ENEMIES HEALTH AND NOT THE PLAYERS
		}
		break;
	case EAttackType::AT_Range:
		UE_LOG(LogTemp, Warning, TEXT("Attacking player...RANGE"));

		if (AttackComponent->RayCastAttack(GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 1000.0f, this, Player))
		{
			//HIT TAKE DAMAGE
			//Spawn projectile (dont deal direct damage here)
			//HealthComponent->SetHealth(HealthComponent->GetHealth() - 1); -- NOT THIS AS IT IS THE ENEMIES HEALTH AND NOT THE PLAYERS
		}
		break;
	case EAttackType::AT_Magic:
		UE_LOG(LogTemp, Warning, TEXT("Attacking player...MAGIC"));

		if (AttackComponent->RayCastAttack(GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 1000.0f, this, Player))
		{
		}
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