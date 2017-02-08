// Fill out your copyright notice in the Description page of Project Settings.

#include "DungeonCrawler.h"
#include "RoomProperties.h"


const int NUM_OF_WALLS = 4;

// Sets default values
ARoomProperties::ARoomProperties()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARoomProperties::BeginPlay()
{
	Super::BeginPlay();

	switch (doorPosition)
	{
	case 0://0 = top
		break;
	case 1://1 = right
		break;
	case 2://2 = bottom
		break;
	case 3://3 = left
		break;
	}
}

// Called every frame
void ARoomProperties::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

