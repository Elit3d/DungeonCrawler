// Fill out your copyright notice in the Description page of Project Settings.

#include "DungeonCrawler.h"
#include "EnemySpawnerComponent.h"


// Sets default values for this component's properties
UEnemySpawnerComponent::UEnemySpawnerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnemySpawnerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	NavSystem = UNavigationSystem::GetCurrent(GetWorld());
}


// Called every frame
void UEnemySpawnerComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UEnemySpawnerComponent::SpawnEnemy(FVector Location, float Radius)
{
	SpawnCounter++;
	if (SpawnCounter <= MaxSpawn)
	{
		FVector EnemySpawnLocation = NavSystem->GetRandomReachablePointInRadius(GetWorld(), Location, Radius, NULL, NULL);

		RandNumber = FMath::RandHelper(5);

		for (size_t i = 0; i < EnemyActors.Num(); i++)
		{
			if (EnemyActors[i] != nullptr)
			{
				Enemy = GetWorld()->SpawnActor(EnemyActors[RandNumber], &EnemySpawnLocation, NULL);
			}
		}
		EnemyArray.Push(Enemy);
	}
}

FVector UEnemySpawnerComponent::SpawnLocation(float X, float Y, float Z, float Radius)
{
	return NavSystem->GetRandomReachablePointInRadius(GetWorld(), FVector(X, Y, Z), Radius, NULL, NULL);
}

void UEnemySpawnerComponent::ClearEnemy()
{
	EnemyArray.Empty();
	SpawnCounter = 0;
}

