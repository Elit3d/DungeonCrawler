// Fill out your copyright notice in the Description page of Project Settings.

#include "DungeonCrawler.h"
#include "CreateRoomComponent.h"


// Sets default values for this component's properties
UCreateRoomComponent::UCreateRoomComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCreateRoomComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	//Rooms.SetNum(NumOfRoomMesh, true); // do this in code

	for (int i = 0; i < Rooms.Num(); i++)
	{
		if (Rooms.Num() != NULL && Rooms.Num() <= 10)
		{
			ChanceOfRoom.SetNum(Rooms.Num(), true);
			ChanceOfRoom[0] = 200;
			ChanceOfRoom[i] = 5;
		}
	}


}


// Called every frame
void UCreateRoomComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
	
}


// in DFS call this for the array number [GetWeightedRandom()] and call Rooms for the new spawnactor
int UCreateRoomComponent::GetWeightedRandom()
{
	int total = 0;

	int WeightedRandom = FMath::RandHelper(245);

	for (int i = 0; i < ChanceOfRoom.Num(); i++)
	{
		total += ChanceOfRoom[i];

		if (WeightedRandom < total)
		{
			return i;

			break;
		}
	}
	return 0;
}

int UCreateRoomComponent::GetTheme()
{
	return theme;
}

void UCreateRoomComponent::SetLevelTheme(int _theme)
{
	theme = _theme;
}

