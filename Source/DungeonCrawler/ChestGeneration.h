// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ChestGeneration.generated.h"

UCLASS()
class DUNGEONCRAWLER_API AChestGeneration : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChestGeneration();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	UPROPERTY(EditAnywhere)
		USceneComponent *Root;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent *ChestLid;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent *ChestBody;
	UPROPERTY(EditAnywhere)
		UBoxComponent *Collider;
	UPROPERTY(EditAnywhere)
		UBoxComponent *SpawnArea;


	UPROPERTY(EditAnywhere, Category = "ItemManager")
		class UItemManagerComponent *ItemManager;

	//UPROPERTY(EditAnywhere, Category = ItemManager)
		//class AItemManager *ItemList;
	//UPROPERTY(EditAnywhere, Category = ItemManager)
		//AActor *ItemListActor; // Could make this TSubclassOf and point it to the base blueprint
	UPROPERTY(EditAnywhere, Category = ItemManager)
		int minSpawnAmount = 0; // Min amount of items aloud to spawn in a chest
	UPROPERTY(EditAnywhere, Category = ItemManager)
		int maxSpawnAmount = 10; // Max amount of items aloud to spawn in a chest

	UPROPERTY(EditAnywhere, Category = Chest)
		float InterpSpeed = 100.f;
private:
	int itemSpawnCounter = 0; // Counter to decide how many items to spawn
	int itemsToSpawn = 0; // Amount of items to spawn 
	int RandItemToSpawn = 0; // Chose an item to spawn from the array

	bool Collide = false; // Is collided
	bool Open = false; // Is chest open
};
