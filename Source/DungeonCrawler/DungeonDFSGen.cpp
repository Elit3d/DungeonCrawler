// Fill out your copyright notice in the Description page of Project Settings.

#include "DungeonCrawler.h"
#include "DungeonDFSGen.h"

#include "CreateRoomComponent.h"

// Sets default values
ADungeonDFSGen::ADungeonDFSGen()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RoomComponent = CreateDefaultSubobject<UCreateRoomComponent>(TEXT("RoomComponent"));
}

// Called when the game starts or when spawned
void ADungeonDFSGen::BeginPlay()
{
	Super::BeginPlay();
	
	MapWidth.X = 100;
	MapWidth.Y = 100;

	// Create a grid and populate it with static mesh based off the DFS perhaps
}

// Called every frame
void ADungeonDFSGen::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

int ADungeonDFSGen::RandomDirection()
{
	// Gives a random direction to travel in N E S W
	return FMath::RandRange(1,4);
}

