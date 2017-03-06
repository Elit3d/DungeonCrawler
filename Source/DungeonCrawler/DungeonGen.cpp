// Fill out your copyright notice in the Description page of Project Settings.

#include "DungeonCrawler.h"
#include "DungeonGen.h"


// Sets default values
ADungeonGen::ADungeonGen()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

//	CellY * LevelWidth + CellX;
}

// Called when the game starts or when spawned
void ADungeonGen::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADungeonGen::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ADungeonGen::GenerateLevel()
{
	PreviousRoom = -1;
	CurrentRoom = (CellY * LevelWidth) + CellX;

	for (int i = 1; i < NumberOfRooms; i++)
	{
		MainLoopIndex = i;

		StepsTaken.Add(CurrentRoom);
		RoomPlaced.SetNum(CurrentRoom);
		//check back to allocate room if doesnt work

		if (PreviousRoom == -1)
		{
			//check back on this
			//check if map full 
			//random branch
		}
		else
		{

		}
		break;
	}
}

