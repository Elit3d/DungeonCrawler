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
void ADungeonDFSGen::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, FString::FromInt(LevelGrid.Num()) + " - " + FString::FromInt(StartX) + " " + FString::FromInt(StartY));
}

void ADungeonDFSGen::CreateGrid()
{
	LevelGrid.SetNum(GridWidth * GridHeight, true);
}

void ADungeonDFSGen::RandomPointOnGrid()
{
	StartX = FMath::RandHelper(GridWidth);
	StartY = FMath::RandHelper(GridHeight);

	//End pos might be setup on runtime -- Last bit on grid placed will be last room
	EndX = FMath::RandHelper(GridWidth);
	EndY = FMath::RandHelper(GridHeight);
}

int32 ADungeonDFSGen::DirectionToTravel()
{
	// Gives a random direction to travel in N E S W -- 0-3
	return FMath::RandHelper(4);
}



