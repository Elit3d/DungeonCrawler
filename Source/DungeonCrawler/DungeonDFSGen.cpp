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

	Visited.SetNum(LevelGrid.Num());
}

// Called every frame
void ADungeonDFSGen::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, FString::FromInt(LevelGrid.Num()) + " - " + FString::FromInt(StartX) + " " + FString::FromInt(StartY) + " = " + FString::FromInt(StartX+1) + " " + FString::FromInt(StartY+1));
	//GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, FString::FromInt(CellX) + " - " + FString::FromInt(CellY));
	//GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, /*Visited(CellX, CellY) ? "True" : "False" + */ FString::FromInt(CellX) + " - " + FString::FromInt(CellY) );

	int Calc = (CellY * GridWidth) + CellX;
	//int Calc2 = (CellY * GridWidth) + CellX + 1;
	GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, FString::FromInt(dir) + " - Calc 1: " + FString::FromInt(Calc) /*+ " - Calc 2: " + FString::FromInt(Calc2)*/);
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

void ADungeonDFSGen::DFSAlgorithm()
{
	dir = FMath::RandHelper(4);

	switch (dir)
	{
	case 0: // North
		//if (Visited[CurrentStep - 10] != true)
			CellY--; //goes down by 10
		break;
	case 1: // East
		//if (Visited[CurrentStep + 1] == false)
			CellX++; //goes up by 1
		break;
	case 2: // South
		//if (Visited[CurrentStep + 10] != true)
			CellY++; //goes up by 10
		break;
	case 3: // West
		//if (Visited[CurrentStep - 1] == false)
			CellX--; //goes down by 1
		break;
	}

		int RoomSize = 5;
		int GridSpacing = 100;
		CurrentStep = (CellY * GridWidth) + CellX;
		FVector RoomLocation = GetTransform().GetLocation();
		RoomLocation.X += (float)CellX * (RoomSize * GridSpacing);
		RoomLocation.Y += (float)CellY * (RoomSize * GridSpacing);
		RoomLocation.Z += 350;
		AActor *Room = GetWorld()->SpawnActor(ActorArray[0], &RoomLocation, NULL);
		Visited[CurrentStep] = true;
}

