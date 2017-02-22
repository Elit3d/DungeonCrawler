// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DungeonDFSGen.generated.h"

UENUM(BlueprintType)
enum EDirectionCheck
{
	NORTH,
	EAST,
	SOUTH,
	WEST
};

USTRUCT(BlueprintType)
struct FTestStruct
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room")
		TArray<bool> Direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room")
		int CurrentCell;
};

UCLASS()
class DUNGEONCRAWLER_API ADungeonDFSGen : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADungeonDFSGen();

	// before begin play but after contructor
	virtual void PostInitializeComponents() override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;


	void CreateGrid();
	void RandomPointOnGrid();

	void CheckNeighbourGrid();

	void DFSAlgorithm();
	void CellChecker();
	
	UPROPERTY(EditAnywhere, Category = "Level Properties")
		int32 GridWidth;
	UPROPERTY(EditAnywhere, Category = "Level Properties")
		int32 GridHeight;
	UPROPERTY(EditAnywhere, Category = "Level Properties")
		int NumberOfRooms = 10; // how many steps to take

	UPROPERTY(EditAnywhere, Category = "Room Component")
		class UCreateRoomComponent *RoomComponent;

	// 2d grid stored as 1d array
	TArray< TWeakObjectPtr<AActor> > LevelGrid;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Actors)
		TArray< TSubclassOf<class AActor> > ActorArray;

	UPROPERTY(EditAnywhere)
		TArray<bool> Visited;

	//UPROPERTY(EditAnywhere)
	//	TArray<int> RoomArray;

	UPROPERTY(EditAnywhere, Category=Timer)
		float maxTimer = 1.0f;


	UPROPERTY(EditAnywhere, Category="Tester Struct")
		TArray<FTestStruct> Testing;
	UPROPERTY(EditAnywhere, Category = "Tester Struct")
		FTestStruct TestStruct;
	UPROPERTY(EditAnywhere, Category = "Direction Array")
	TArray<int32> dirArray;
private:
	// Starting Grid Point
	int StartLocation;
	int EndLocation;

	int32 CellX;
	int32 CellY;

	int CurrentStep = 0;
	int RoomCounter = 0;

	float timer = 0.0f;
	int32 dir;
	int rand=0;

	int testCOunter = 0;
	AActor *Room;
	EDirectionCheck DirectionCheck;
};
