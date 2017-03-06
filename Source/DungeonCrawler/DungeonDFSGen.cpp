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

	//CreateGrid();
	//RandomPointOnGrid();

	//dirArray.SetNum(4, true);

	//for (int i = 0; i < dirArray.Num(); i++)
	//{
	//	dirArray[i] = 10;
	//}
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

	CreateLevel(); // Setup level on first play
}

// Called every frame
void ADungeonDFSGen::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
			if (ChestArray.Num() <= maxChestSpawn)
			{
				FVector RoomLocation = FVector(0, 0, 0);
				if (ActorArray[3] != nullptr)
				{
					Chest = GetWorld()->SpawnActor(ActorArray[3], &RoomLocation, NULL);
					ChestArray.Push(Chest);
				}
			}
		}
	}

	//Check surrounding tiles
	if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::T))
	{
		int RoomSize = 10;
		int GridSpacing = 100;
		FVector RoomLocation = GetTransform().GetLocation();
		//RoomLocation.X += (float)CellX * (RoomSize * GridSpacing);
		//RoomLocation.Y += (float)CellY * (RoomSize * GridSpacing);
		//RoomLocation.Z += 350;

		for (int i = 0; i < Testing.Num(); i++)
		{
			if (Visited[Testing[i].CurrentCell - 20] == false) // NORTH
			{
				
				GetWorld()->SpawnActor(ActorArray[2], &RoomLocation, NULL);
			}
			if (Visited[Testing[i].CurrentCell + 1] == false) // EAST
			{
				//Testing[i].Direction[1] = true;
				GetWorld()->SpawnActor(ActorArray[2], &RoomLocation, NULL);
			}
			if (Visited[Testing[i].CurrentCell + 20] == false) // SOUTH
			{
				//Testing[i].Direction[2] = true;
				GetWorld()->SpawnActor(ActorArray[2], &RoomLocation, NULL);
			}
			if (Visited[Testing[i].CurrentCell - 1] == false) // WEST
			{
				//Testing[i].Direction[3] = true;
				GetWorld()->SpawnActor(ActorArray[2], &RoomLocation, NULL);
			}
		}
	}

	//	//SURROUNDING TILES THAT ARE FALSE WILL BE A WALL https://www.youtube.com/watch?v=wb6u2JImsyE
	//}

	if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::C))
	{
		//CreateLevel(); // Clears the arrays and stuff
		UE_LOG(LogTemp, Warning, TEXT("%d "), RoomComponent->GetWeightedRandom());
	}
}

int ADungeonDFSGen::GetFirstTravelDir()
{
	for (int i = 0; i < dirArray.Num(); i++)
		return FMath::RandHelper(dirArray[i]);
	return 0;
}

void ADungeonDFSGen::CreateGrid()
{
	LevelGrid.SetNum(GridWidth * GridHeight, true);
}

bool ADungeonDFSGen::ChangeDir(int percentage)
{
	return (FMath::RandRange(1, 100 / percentage) == 1 ? true : false);
}

void ADungeonDFSGen::RandomPointOnGrid()
{
	//CellX = FMath::RandHelper(GridWidth-1);
	//CellY = FMath::RandHelper(GridHeight-1);
	CellX = GridWidth / 2; // mid X
	CellY = GridHeight / 2; // mid Y
	CellArray.Push(FVector2D(CellX, CellY));
}

void ADungeonDFSGen::DFSAlgorithm()
{

	CurrentStep = (CellY * GridWidth) + CellX;

	//dirTravelTime = FMath::RandRange(3, 5);

	if (ChangeDir(15.0f) == true) // 10% chance
	{
		dir = 3;
	}
	else
		dir = FMath::RandHelper(3); // Only chose 1 of 3 directions to go // Stops end point being close to first point
	


	//int WeightedRandom = FMath::RandHelper(100);

	//int total = 0;

	//for (int i = 0; i < dirArray.Num(); i++)
	//{
	//	total += dirArray[i];

	//	if (WeightedRandom < total)
	//	{
	//		FString Print = FString::FromInt((CellY * GridWidth) + CellX) + " - total: " + FString::FromInt(total) + " - weighted: " + FString::FromInt(WeightedRandom);
	//		UE_LOG(LogTemp, Warning, TEXT("%s"), *Print);

	//		switch (i)
	//		{
	//		case 0: // North
	//			if (Visited[CurrentStep - GridWidth] == false)
	//			{
	//				CellY--; //goes down by 20

	//				if (ActorArray[rand] != nullptr)
	//					Room = GetWorld()->SpawnActor(ActorArray[rand], &RoomLocation, NULL);

	//				RoomCounter++;
	//				//RoomArray.Push(CurrentStep);
	//				TestStruct.CurrentCell = CurrentStep;
	//				TestStruct.Direction.SetNum(4, true);
	//				Testing.Add(TestStruct);

	//				for (size_t j = 0; j < dirArray.Num(); j++)
	//				{
	//					if (i == j)
	//						dirArray[i] = MaxChance;
	//					else
	//						dirArray[j] = MinChance;
	//				}
	//			}
	//			break;
	//		case 1: // East
	//			if (Visited[CurrentStep + 1] == false)
	//			{
	//				CellX++; //goes up by 1

	//				if (ActorArray[rand] != nullptr)
	//					Room = GetWorld()->SpawnActor(ActorArray[rand], &RoomLocation, NULL);

	//				RoomCounter++;
	//				//RoomArray.Push(CurrentStep);
	//				TestStruct.CurrentCell = CurrentStep;
	//				TestStruct.Direction.SetNum(4, true);
	//				Testing.Add(TestStruct);

	//				for (size_t j = 0; j < dirArray.Num(); j++)
	//				{
	//					if (i == j)
	//						dirArray[i] = MaxChance;
	//					else
	//						dirArray[j] = MinChance;
	//				}
	//			}
	//			break;
	//		case 2: // South
	//			if (Visited[CurrentStep + GridWidth] == false)
	//			{
	//				CellY++; //goes up by 20

	//				if (ActorArray[rand] != nullptr)
	//					Room = GetWorld()->SpawnActor(ActorArray[rand], &RoomLocation, NULL);

	//				RoomCounter++;
	//				//RoomArray.Push(CurrentStep);
	//				TestStruct.CurrentCell = CurrentStep;
	//				TestStruct.Direction.SetNum(4, true);
	//				Testing.Add(TestStruct);

	//				for (size_t j = 0; j < dirArray.Num(); j++)
	//				{
	//					if (i == j)
	//						dirArray[i] = MaxChance;
	//					else
	//						dirArray[j] = MinChance;
	//				}
	//			}
	//			break;
	//		case 3: // West
	//			if (Visited[CurrentStep - 1] == false)
	//			{
	//				CellX--; //goes down by 1

	//				if (ActorArray[rand] != nullptr)
	//					Room = GetWorld()->SpawnActor(ActorArray[rand], &RoomLocation, NULL);

	//				RoomCounter++;
	//				//RoomArray.Push(CurrentStep);
	//				TestStruct.CurrentCell = CurrentStep;
	//				TestStruct.Direction.SetNum(4, true);
	//				Testing.Add(TestStruct);

	//				for (size_t j = 0; j < dirArray.Num(); j++)
	//				{
	//					if (i == j)
	//						dirArray[i] = MaxChance;
	//					else
	//						dirArray[j] = MinChance;
	//				}
	//			}
	//			break;
	//		}
	//		break;
	//	}
	//}
	// rand mesh but this will be replaced

	/*rand++;

	if (rand > 1)
	{
		rand = 0;
	}*/

	// end rand mesh but this will be replaced

	//FString Print = FString::FromInt((CellY * GridWidth) + CellX);
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *Print);

	if (CanMoveCheck())
	{
		switch (dir)
		{
		case 0: // North
			if (Visited[CurrentStep - GridWidth] == false 
				&& CurrentStep - GridWidth > GridWidth && northCounter <= dirTravelTime)
			{
				CellY--; //goes down by 20

				AddRoomToGrid();
			}
			break;
		case 1: // East
			if (Visited[CurrentStep + 1] == false 
				&& CurrentStep + 1 < Visited.Num() && eastCounter <= dirTravelTime)
			{
				CellX++; //goes up by 1

				AddRoomToGrid();
			}
			break;
		case 2: // South
			if (Visited[CurrentStep + GridWidth] == false 
				&& CurrentStep + GridWidth < Visited.Num() - GridWidth && southCounter <= dirTravelTime)
			{
				CellY++; //goes up by 20

				AddRoomToGrid();
			}
			break;
		case 3: // West
			if (Visited[CurrentStep - 1] == false && CurrentStep - 1 > 0)
			{
				CellX--; //goes down by 1

				AddRoomToGrid();
			}
			break;
		}
	}
	else
	{
		switch (dir)
		{
		case 0: // North
			if (CurrentStep - GridWidth > GridWidth && Border[CurrentStep - GridWidth] == false)
				CellY--; //goes down by 20
			break;
		case 1: // East
			if (CurrentStep + 1 < Visited.Num() - 1 && Border[CurrentStep + 1] == false)
				CellX++; //goes up by 1
			break;
		case 2: // South
			if (CurrentStep + GridWidth < Visited.Num() - GridWidth && Border[CurrentStep + GridWidth] == false)
				CellY++; //goes up by 20
			break;
		case 3: // West
			if (CurrentStep - 1 > 0 && Border[CurrentStep - 1] == false)
				CellX--; //goes down by 1
			break;
		}
	}

	Visited[CurrentStep] = true;

	/*if (RoomCounter >= 10)
	{
		EndLocation = CurrentStep;
	}*/
}

void ADungeonDFSGen::AddRoomToGrid()
{
	int RoomSize = 10;
	int GridSpacing = 100;
	FVector RoomLocation = GetTransform().GetLocation();
	RoomLocation.X += (float)CellX * (RoomSize * GridSpacing);
	RoomLocation.Y += (float)CellY * (RoomSize * GridSpacing);
	RoomLocation.Z += 350;

	FRotator RandRotation;

	RoomRot[0] = 0.0f;
	RoomRot[1] = 90.0f;
	RoomRot[2] = 180.0f;
	RoomRot[3] = 270.0f;

	for (int i = 0; i < 4; i++)
	{
		RandRotation.Yaw = RoomRot[FMath::RandRange(0, 4)];
	}

	if (RoomComponent->Rooms[RoomComponent->GetWeightedRandom()] != nullptr)
	{
		Room = GetWorld()->SpawnActor(RoomComponent->Rooms[RoomComponent->GetWeightedRandom()], &RoomLocation, &RandRotation);
		RoomArray.Push(Room);
	}

	RoomCounter++;
	//RoomArray.Push(CurrentStep);
	TestStruct.CurrentCell = CurrentStep;
	TestStruct.Direction.SetNum(4, true);
	Testing.Add(TestStruct);
}

void ADungeonDFSGen::CreateLevel()
{
	Visited.Empty(); // Clear the Array
	Testing.Empty(); // Clear the Array

	for (int i = 0; i < RoomArray.Num(); i++)
	{
		if(RoomArray[i] != nullptr)
			RoomArray[i]->Destroy();
	}
	RoomArray.Empty();

	for (int i = 0; i < ChestArray.Num(); i++)
	{
		if (ChestArray[i] != nullptr)
			ChestArray[i]->Destroy();
	}
	ChestArray.Empty();

	RoomCounter = 0;

	CreateGrid();
	RandomPointOnGrid();

	//Setup the grid
	Visited.SetNum(GridWidth * GridHeight, true); // Set up the grid
	Border.SetNum(GridWidth * GridHeight, true);
	StartLocation = CurrentStep = (CellY * GridWidth) + CellX; // Create start and current step location

	// Border Stuff
	for (int i = 0; i < GridWidth; i++)
	{
		// Normal border checks
		Visited[i] = true; // Top border
		Visited[i*GridWidth] = true; // Left border
		Visited[GridWidth - 1 + i*GridWidth] = true; // Right border
		Visited[GridWidth*GridHeight - GridWidth + i] = true; // Bottom border
															  // For backtracking
		Border[i] = true; // Top border
		Border[i*GridWidth] = true; // Left border
		Border[GridWidth - 1 + i*GridWidth] = true; // Right border
		Border[GridWidth*GridHeight - GridWidth + i] = true; // Bottom border
	}

	maxChestSpawn = FMath::RandRange(5,10);
}

bool ADungeonDFSGen::CanMoveCheck()
{
	if (Visited[CurrentStep + 1] && Visited[CurrentStep - 1]
		&& Visited[CurrentStep + GridWidth] && Visited[CurrentStep - GridWidth])
		return false;
	return true;
}