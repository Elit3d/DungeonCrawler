// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DungeonGen.generated.h"

USTRUCT()
struct FConnectedRooms
{
	GENERATED_BODY()

	bool NORTH;
	bool EAST;
	bool SOUTH;
	bool WEST;
};

UCLASS()
class DUNGEONCRAWLER_API ADungeonGen : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADungeonGen();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;


	void GenerateLevel();

	int CellX;
	int CellY;

	TArray<AActor*> Rooms;

	int CurrentRoom;
	int PreviousRoom;
	int ExtraConnectionAttempt;

	TArray<bool*> RoomPlaced;
	TArray<bool*> Visited;
	TArray<FConnectedRooms> ConnectedRooms;

	// Level Properties
	FVector StartPosition;

	FVector2D LevelDimension;
	FVector2D RoomDimension;

	int NumberOfRooms;

	float BranchChance;
	int MaxBranchLength;

	int ExtraConnections;

	int LevelWidth;
	int LevelHeight;

	TArray<int> StepsTaken;
	int MainLoopIndex;
};
