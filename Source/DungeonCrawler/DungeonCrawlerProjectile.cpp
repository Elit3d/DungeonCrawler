// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "DungeonCrawler.h"
#include "DungeonCrawlerProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "EnemyCharacter.h"

#include "DungeonCrawlerCharacter.h"
#include "MyGameInstance.h"

ADungeonCrawlerProjectile::ADungeonCrawlerProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->RelativeRotation = FRotator(0.0f, 0.0f, 0.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &ADungeonCrawlerProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	ExplodeParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ExplosionParticle"));
	ExplodeParticle->bAutoActivate = true;
	// Die after 3 seconds by default
	//InitialLifeSpan = 3.0f;
	PrimaryActorTick.bCanEverTick = true;
}

void ADungeonCrawlerProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//Enemy = Cast<AEnemyCharacter>(OtherActor);
	Character = Cast<ADungeonCrawlerCharacter>(OtherActor);

	if (Character != nullptr)
	{
		UMyGameInstance *Instance = Cast<UMyGameInstance>(GetGameInstance());
		
		if (Instance != nullptr)
		{
			Instance->SetHealth(Instance->GetHealth() - 10);
		}

		this->Destroy();
	}
}

void ADungeonCrawlerProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UE_LOG(LogTemp, Warning, TEXT("TICKING "));

	counter += DeltaTime;

	if (counter >= 3.0f)
	{
		// apply radial damage when explode
		// also play attached sound
		counter = 0.0f;
		ExplodeParticle->SetHiddenInGame(false);
		this->Destroy();
	}
}
