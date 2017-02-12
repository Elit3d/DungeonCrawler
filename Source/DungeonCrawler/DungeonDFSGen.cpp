// Fill out your copyright notice in the Description page of Project Settings.

#include "DungeonCrawler.h"
#include "DungeonDFSGen.h"

#include "CreateRoomComponent.h"
#include "Engine.h"

// Sets default values
ADungeonDFSGen::ADungeonDFSGen()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RoomComponent = CreateDefaultSubobject<UCreateRoomComponent>(TEXT("RoomComponent"));

	GridWidth = 20;
	GridHeight = 20;
}

// Called when the game starts or when spawned
void ADungeonDFSGen::BeginPlay()
{
	Super::BeginPlay();

	// Create a grid and populate it with static mesh based off the DFS perhaps
	CreateGrid();
	RandomPointOnGrid();
}

// Called every frame
void ADungeonDFSGen::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//	GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, FString::FromInt(LevelGrid.Num()) + " - " + FString::FromInt(StartX) + " " + FString::FromInt(StartY) + " = " + FString::FromInt(StartX+1) + " " + FString::FromInt(StartY+1));
	GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, FString::FromInt(CellX) + " - " + FString::FromInt(CellY));
	//DirectionToTravel();

	timer += DeltaTime;
	if (timer >= maxTimer)
	{
		//if (CurrentStep <= NumberOfRooms)
		{
			CurrentStep++;
			timer = 0.0f;
			DFSAlgorithm();
		}
	}
}

void ADungeonDFSGen::CreateGrid()
{
	LevelGrid.SetNum(GridWidth * GridHeight, true);
}

void ADungeonDFSGen::RandomPointOnGrid()
{
	CellX = FMath::RandHelper(GridWidth);
	CellY = FMath::RandHelper(GridHeight);
}

int32 ADungeonDFSGen::DirectionToTravel()
{
	// Gives a random direction to travel in N E S W -- 0-3
	return FMath::RandHelper(4);
}

AActor * ADungeonDFSGen::GetGridActor(int32 x, int32 y)
{
	if (LevelGrid.IsValidIndex(GridWidth * y + x) == true)
		return Cast<AActor>(LevelGrid[GridWidth * y + x].Get());
	return NULL;
}

void ADungeonDFSGen::DFSAlgorithm()
{
	//if (CellX > 0 && CellY > 0)
	{
		int32 dir = FMath::RandHelper(4);

		switch (dir)
		{
		case 0: // North
			CellY--;
			break;
		case 1: // East
			CellX++;
			break;
		case 2: // South
			CellY++;
			break;
		case 3: // West
			CellX--;
			break;
		}

		int RoomSize = 5;
		int GridSpacing = 100;
		FVector loc = GetTransform().GetLocation();
		loc.X += (float)CellX * (RoomSize * GridSpacing);
		loc.Y += (float)CellY * (RoomSize * GridSpacing);
		loc.Z += 350;
		AActor * pActor = GetWorld()->SpawnActor(ActorArray[0], &loc, NULL);
		//LevelGrid[GridWidth * CellY + CellX] = pActor; //giving an index out of bounds
	}
}



