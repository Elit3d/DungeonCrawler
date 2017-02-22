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

	CreateGrid();
	RandomPointOnGrid();
}

void ADungeonDFSGen::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	// Create a grid and populate it with static mesh based off the DFS perhaps
}

// Called when the game starts or when spawned
void ADungeonDFSGen::BeginPlay()
{
	Super::BeginPlay();

	Visited.SetNum(GridWidth * GridHeight, true);
	StartLocation = CurrentStep = (CellY * GridWidth) + CellX;
}

// Called every frame
void ADungeonDFSGen::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, FString::FromInt(LevelGrid.Num()) + " - " + FString::FromInt(StartX) + " " + FString::FromInt(StartY) + " = " + FString::FromInt(StartX+1) + " " + FString::FromInt(StartY+1));
	//GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, FString::FromInt(CellX) + " - " + FString::FromInt(CellY));
	//GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, /*Visited(CellX, CellY) ? "True" : "False" + */ FString::FromInt(CellX) + " - " + FString::FromInt(CellY) );
//	GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, FString::FromInt(dir) + " - " + FString::FromInt(dir1));
	int Calc = CellX + CellY;
	//int Calc2 = (CellY * GridWidth) + CellX + 1;
	//GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, FString::FromInt(EndLocation) /*+ " - Calc 1: " + FString::FromInt(Calc)*/ + " - Calc 2: " + FString::FromInt((CellY * GridWidth) + CellX) + " " + FString::FromInt(CellY));
	//DirectionToTravel();

	timer += DeltaTime;
	if (timer >= maxTimer)
	{
		if (RoomCounter < NumberOfRooms)
		{
			timer = 0.0f;
			DFSAlgorithm();
		}
		else
		{
			//CellChecker();
		}
	}

	//Check surrounding tiles
	for (int i = 0; i < Testing.Num(); i++)
	{
		if (Visited[Testing[i].CurrentCell - 20] == true) // NORTH
		{
			Testing[i].Direction[0] = true;
		}
		if (Visited[Testing[i].CurrentCell + 1] == true) // EAST
		{
			Testing[i].Direction[1] = true;
		}
		if (Visited[Testing[i].CurrentCell + 20] == true) // SOUTH
		{
			Testing[i].Direction[2] = true;
		}
		if (Visited[Testing[i].CurrentCell - 1] == true) // WEST
		{
			Testing[i].Direction[3] = true;
		}

		//SURROUNDING TILES THAT ARE FALSE WILL BE A WALL https://www.youtube.com/watch?v=wb6u2JImsyE
	}
}

void ADungeonDFSGen::CreateGrid()
{
	LevelGrid.SetNum(GridWidth * GridHeight, true);
}

void ADungeonDFSGen::RandomPointOnGrid()
{
	//CellX = FMath::RandHelper(GridWidth);
	//CellY = FMath::RandHelper(GridHeight);
	CellX = GridWidth / 2; // mid X
	CellY = GridHeight / 2; // mid Y
}

void ADungeonDFSGen::DFSAlgorithm()
{
	if (Visited.Num() < 0) return;
	// Exceeds min bounds
	if (CurrentStep - GridWidth <= 0 || CurrentStep + GridWidth <= 0) return;
	// Exceeds max bounds
	if (CurrentStep - GridWidth >= GridWidth * GridHeight || CurrentStep + GridWidth >= GridWidth * GridHeight) return;

	int RoomSize = 5;
	int GridSpacing = 100;
	CurrentStep = (CellY * GridWidth) + CellX;
	FVector RoomLocation = GetTransform().GetLocation();
	RoomLocation.X += (float)CellX * (RoomSize * GridSpacing);
	RoomLocation.Y += (float)CellY * (RoomSize * GridSpacing);
	RoomLocation.Z += 350;

	dir = FMath::RandHelper(4);

	// rand mesh but this will be replaced
	rand++;

	if (rand > 1)
	{
		rand = 0;
	}

	// end rand mesh but this will be replaced

	switch (dir)
	{
	case 0: // North
		if (Visited[CurrentStep - GridWidth] == false)
		{
			CellY--; //goes down by 20

			if (ActorArray[rand] != nullptr)
				Room = GetWorld()->SpawnActor(ActorArray[rand], &RoomLocation, NULL);

			RoomCounter++;
			//RoomArray.Push(CurrentStep);
			TestStruct.CurrentCell = CurrentStep;
			TestStruct.Direction.SetNum(4, true);
			Testing.Add(TestStruct);
		}
		break;
	case 1: // East
		if (Visited[CurrentStep + 1] == false)
		{
			CellX++; //goes up by 1

			if (ActorArray[rand] != nullptr)
				Room = GetWorld()->SpawnActor(ActorArray[rand], &RoomLocation, NULL);

			RoomCounter++;
			//RoomArray.Push(CurrentStep);
			TestStruct.CurrentCell = CurrentStep;
			TestStruct.Direction.SetNum(4, true);
			Testing.Add(TestStruct);
		}
		break;
	case 2: // South
		if (Visited[CurrentStep + GridWidth] == false)
		{
			CellY++; //goes up by 20

			if (ActorArray[rand] != nullptr)
				Room = GetWorld()->SpawnActor(ActorArray[rand], &RoomLocation, NULL);

			RoomCounter++;
			//RoomArray.Push(CurrentStep);
			TestStruct.CurrentCell = CurrentStep;
			TestStruct.Direction.SetNum(4, true);
			Testing.Add(TestStruct);
		}
		break;
	case 3: // West
		if (Visited[CurrentStep - 1] == false)
		{
			CellX--; //goes down by 1

			if (ActorArray[rand] != nullptr)
				Room = GetWorld()->SpawnActor(ActorArray[rand], &RoomLocation, NULL);

			RoomCounter++;
			//RoomArray.Push(CurrentStep);
			TestStruct.CurrentCell = CurrentStep;
			TestStruct.Direction.SetNum(4, true);
			Testing.Add(TestStruct);
		}
		break;
	}

	Visited[CurrentStep] = true;

	if (RoomCounter >= 10)
	{
		EndLocation = CurrentStep;
	}
}

void ADungeonDFSGen::CellChecker()
{
	int RoomSize = 5;
	int GridSpacing = 100;
	FVector RoomLocation = GetTransform().GetLocation();
	RoomLocation.X += (float)CellX * (RoomSize * GridSpacing);
	RoomLocation.Y += (float)CellY * (RoomSize * GridSpacing);
	RoomLocation.Z += 350;
	FRotator RoomRotation;

	//for (int i = 0; i < RoomArray.Num(); i++)
	//{
	//	if (Visited[RoomArray[i] + 20] == true && Visited[RoomArray[i] - 1] == true && Visited[RoomArray[i] - 20] == true && Visited[RoomArray[i] + 1] == true) // top left corner
	//	{
	//		RoomRotation.Yaw = 75.f;
	//		Room = GetWorld()->SpawnActor(ActorArray[0], &RoomLocation, &RoomRotation);
	//	}
	//	else if (Visited[RoomArray[i] + 1] == false)
	//	{
	//		RoomRotation.Yaw = 180.f;
	//	}
	//	else
	//	{

	//	}
	//}
}

