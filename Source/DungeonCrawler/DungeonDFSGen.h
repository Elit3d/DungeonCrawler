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
	GENERATED_USTRUCT_BODY();

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

	void RandomPointOnGrid();

	void DFSAlgorithm();

	void AddRoomToGrid();
	void AddWallsToGrid();
	void WallProperties(int X, int Y);

	UFUNCTION(BlueprintCallable, Category = "Dungeon Level Creation")
		void CreateLevel(); // Clears off values to create a new level

	bool CanMoveCheck(); // Checks the neighbour cells to make sure that we can still move

	bool ChangeDir(int percentage); // Percentage of chance to go to dir 4
	
	UPROPERTY(EditAnywhere, Category = "Level Properties")
		int32 GridWidth;
	UPROPERTY(EditAnywhere, Category = "Level Properties")
		int32 GridHeight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Properties")
		float NumberOfRooms = 10; // how many steps to take
	UPROPERTY(EditAnywhere, Category = "Level Properties")
		int StartLocation; // Starting Grid Point

	// Components
	UPROPERTY(EditAnywhere, Category = "Room Component")
		class UCreateRoomComponent *RoomComponent;
	UPROPERTY(EditAnywhere, Category = "Enemy Component")
		class UEnemySpawnerComponent *EnemyComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Actors)
		TArray< TSubclassOf<class AActor> > ActorArray;

	UPROPERTY(EditAnywhere)
		TArray<bool> Visited;
	UPROPERTY(EditAnywhere)
		TArray<bool> Border;
	UPROPERTY(EditAnywhere)
		TArray<AActor*> RoomArray;


	UPROPERTY(EditAnywhere, Category=Timer)
		float maxTimer = 1.0f;

	UPROPERTY(EditAnywhere, Category="Tester Struct")
		TArray<FTestStruct> Testing;
	UPROPERTY(EditAnywhere, Category = "Tester Struct")
		FTestStruct TestStruct;
	UPROPERTY(EditAnywhere, Category = "Direction Array")
		TArray<int32> dirArray;
	UPROPERTY(EditAnywhere, Category = "Direction Array")
		int InitDirection;

	UPROPERTY(EditAnywhere, Category = "Direction Chance")
		int MinChance = 15;
	UPROPERTY(EditAnywhere, Category = "Direction Chance")
		int MaxChance = 30;

	UPROPERTY(EditAnywhere, Category = "Grid Properties")
		TArray<int32> CellArray;

	UPROPERTY(EditAnywhere, Category = "Grid Location")
		TArray<FVector> GridLocation;

	UPROPERTY(EditAnywhere, Category = "Level Walls")
		TArray<AActor*> WallArray;
	UPROPERTY(EditAnywhere, Category = "Level Walls")
		TArray<TSubclassOf<class AChestGeneration>> ChestGen;
	UPROPERTY(EditAnywhere, Category = "Enemy Array")
		TArray<AActor*> EnemyArray;

	void SetLevelTheme(int _theme);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float RoomCounter = 0;
private:
	int EndLocation;

	int32 CellX;
	int32 CellY;

	int CurrentStep = 0;

	float timer = 0.0f;
	int32 dir;

	int rand=0;

	int testCOunter = 0;
	AActor *Room;
	AActor *Chest;
	AActor *Wall;
	AActor *Enemy;
	TArray<AActor*> ChestArray;
	EDirectionCheck DirectionCheck;
	int Sum = 0;

	int maxChestSpawn = 0;

	float RoomRot[4];

	FVector PlayerStart;

	int counter1 = 0;
	int CurrentWallCell = 0;

	FVector WallLocation;

	bool PlayerSpawned = false;

	TArray<AActor*> FoundEnemyActors;
	bool bTeleportSpawned = false;
	AActor *TeleportActor;
	FVector TeleportLocation;
	UNavigationSystem* NavSys;
};
