// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DungeonDFSGen.generated.h"

UCLASS()
class DUNGEONCRAWLER_API ADungeonDFSGen : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADungeonDFSGen();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void CreateGrid();
	void RandomPointOnGrid();

	void CheckNeighbourGrid();

	void DFSAlgorithm();
	
	UPROPERTY(EditAnywhere, Category = "Level Properties")
		int32 GridWidth;
	UPROPERTY(EditAnywhere, Category = "Level Properties")
		int32 GridHeight;
	UPROPERTY(EditAnywhere, Category = "Room Component")
		class UCreateRoomComponent *RoomComponent;

	// 2d grid stored as 1d array
	TArray< TWeakObjectPtr<AActor> > LevelGrid;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Actors)
		TArray< TSubclassOf<class AActor> > ActorArray;

	UPROPERTY(EditAnywhere)
		TArray<bool> Visited;
private:
	// Starting Grid Point
	int32 CellX;
	int32 CellY;

	int CurrentStep = 0;
	int NumberOfRooms = 50; // how many steps to take

	float timer = 0.0f;
	float maxTimer = 5.0f;
	int32 dir;
};
