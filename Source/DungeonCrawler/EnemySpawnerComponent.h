// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "EnemySpawnerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONCRAWLER_API UEnemySpawnerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemySpawnerComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	void SpawnEnemy(float X, float Y, float Z, float Radius);
	
	FVector SpawnLocation(float X, float Y, float Z, float Radius);

	UPROPERTY(EditAnywhere)
		TArray<AActor*> EnemyArray;
	UPROPERTY(EditAnywhere)
		TArray< TSubclassOf<class AActor> > EnemyActors;

	void ClearEnemy();
private:
	UNavigationSystem* NavSystem;
	AActor* Enemy;
	int RandNumber = 0;
	int SpawnCounter = 0;
	int MaxSpawn = 10;
};
