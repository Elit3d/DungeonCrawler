// Fill out your copyright notice in the Description page of Project Settings.

#include "DungeonCrawler.h"
#include "DungeonDFSGen.h"

#include "CreateRoomComponent.h"
#include "EnemySpawnerComponent.h"

#include "Engine.h"
#include "EnemyCharacter.h"

// Sets default values
ADungeonDFSGen::ADungeonDFSGen()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RoomComponent = CreateDefaultSubobject<UCreateRoomComponent>(TEXT("RoomComponent"));
	EnemyComponent = CreateDefaultSubobject<UEnemySpawnerComponent>(TEXT("EnemyComponent"));

	GridWidth = 20; // Set grid W
	GridHeight = 20; // Set grid H
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
	NavSys = UNavigationSystem::GetCurrent(GetWorld());
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
				FVector RoomLocation = NavSys->GetRandomReachablePointInRadius(GetWorld(), FVector(15000.0f, 15000.0f, 415.0f), 50000.0f, NULL, NULL);
				RoomLocation.Z += 45.0f; // So it spawns on the floor

				FRotator RandRotation;

				RoomRot[0] = 0.0f;
				RoomRot[1] = 90.0f;
				RoomRot[2] = 180.0f;
				RoomRot[3] = 270.0f;

				RandRotation.Roll = RandRotation.Pitch = 0.0f;
				RandRotation.Yaw = RoomRot[FMath::RandRange(0, 3)];

				if (ActorArray[4] != nullptr)
				{
					Chest = GetWorld()->SpawnActor(ActorArray[4], &RoomLocation, &RandRotation);
					ChestArray.Push(Chest);
				}
			}

			FVector Location = FVector(15000.0f, 15000.0f, 415.0f);
			float Radius = 100000.0f;
			EnemyComponent->SpawnEnemy(Location, Radius);

			AddWallsToGrid();

			// Spawn portal after all enemies are gone
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyCharacter::StaticClass(), FoundEnemyActors);

			if(FoundEnemyActors.Num() == 1)
				TeleportLocation = FoundEnemyActors[0]->GetActorLocation();
			else if (FoundEnemyActors.Num() == NULL )
			{
				if (bTeleportSpawned == false)
				{
					bTeleportSpawned = true;

					if (ActorArray[6] != nullptr)
						TeleportActor = GetWorld()->SpawnActor(ActorArray[6], &TeleportLocation, NULL);
				}
			}
		}
	}

	for (int i = 0; i < Testing.Num(); i++)
	{
		if (Visited[Testing[i].CurrentCell - GridWidth] == true) // NORTH
		{
			if(Border[Testing[i].CurrentCell - GridWidth] == false) // to fix walls not spawning on border
				Testing[i].Direction[0] = true;
		}
		if (Visited[Testing[i].CurrentCell + 1] == true) // EAST
		{
			if (Border[Testing[i].CurrentCell + 1] == false) // to fix walls not spawning on border
				Testing[i].Direction[1] = true;
		}
		if (Visited[Testing[i].CurrentCell + GridWidth] == true) // SOUTH
		{
			if (Border[Testing[i].CurrentCell + GridWidth] == false) // to fix walls not spawning on border
				Testing[i].Direction[2] = true;
		}
		if (Visited[Testing[i].CurrentCell - 1] == true) // WEST
		{
			if (Border[Testing[i].CurrentCell - 1] == false) // to fix walls not spawning on border
				Testing[i].Direction[3] = true;
		}
	}

	// Spawn player on first grid
	if (RoomArray[0] != nullptr)
	{
		if (PlayerSpawned == false && GetWorld()->GetFirstPlayerController()->GetPawn() != nullptr)
		{
			PlayerSpawned = true;
			GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorLocation(FVector(RoomArray[0]->GetActorLocation().X, RoomArray[0]->GetActorLocation().Y, 450.0f));
		}
	}
}

bool ADungeonDFSGen::ChangeDir(int percentage)
{
	return (FMath::RandRange(1, 100 / percentage) == 1 ? true : false);
}

void ADungeonDFSGen::SetLevelTheme(int _theme)
{
	RoomComponent->SetLevelTheme(_theme);
}

void ADungeonDFSGen::RandomPointOnGrid()
{
	CellX = GridWidth / 2; // mid X
	CellY = GridHeight / 2; // mid Y
}

void ADungeonDFSGen::DFSAlgorithm()
{
	if (ChangeDir(15.0f) == true) // 10% chance
		dir = 3;
	else
		dir = FMath::RandHelper(3); // Only chose 1 of 3 directions to go // Stops end point being close to first point

	if (CanMoveCheck())
	{
		switch (dir)
		{
		case 0: // North
			if (Visited[CurrentStep - GridWidth] == false
				&& CurrentStep - GridWidth > GridWidth)
			{
				CellY--; //goes down by 20

				AddRoomToGrid();
			}
			break;
		case 1: // East
			if (Visited[CurrentStep + 1] == false
				&& CurrentStep + 1 < Visited.Num())
			{
				CellX++; //goes up by 1

				AddRoomToGrid();
			}
			break;
		case 2: // South
			if (Visited[CurrentStep + GridWidth] == false
				&& CurrentStep + GridWidth < Visited.Num() - GridWidth)
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
			{
				CellY--; //goes down by 20
				CurrentStep = (CellY * GridWidth) + CellX;
			}
			break;
		case 1: // East
			if (CurrentStep + 1 < Visited.Num() - 1 && Border[CurrentStep + 1] == false)
			{
				CellX++; //goes up by 1
				CurrentStep = (CellY * GridWidth) + CellX;
			}
			break;
		case 2: // South
			if (CurrentStep + GridWidth < Visited.Num() - GridWidth && Border[CurrentStep + GridWidth] == false)
			{
				CellY++; //goes up by 20
				CurrentStep = (CellY * GridWidth) + CellX;
			}
			break;
		case 3: // West
			if (CurrentStep - 1 > 0 && Border[CurrentStep - 1] == false)
			{
				CellX--; //goes down by 1
				CurrentStep = (CellY * GridWidth) + CellX;
			}
			break;
		}
	}

	Visited[CurrentStep] = true;
}

void ADungeonDFSGen::AddRoomToGrid()
{
	CurrentStep = (CellY * GridWidth) + CellX;

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

	RandRotation.Roll = RandRotation.Pitch = 0.0f;
	RandRotation.Yaw = RoomRot[FMath::RandRange(0, 3)];

	if (RoomComponent->Rooms[RoomComponent->GetWeightedRandom()] != nullptr)
	{
		if (RoomComponent->GetTheme() < 3)
		{
			switch (RoomComponent->GetTheme())
			{
			case 0:
				//UE_LOG(LogTemp, Warning, TEXT("NORMAL THEME"));
				Room = GetWorld()->SpawnActor(RoomComponent->Rooms[RoomComponent->GetWeightedRandom()], &RoomLocation, &RandRotation);
				break;
			case 1:
				//UE_LOG(LogTemp, Warning, TEXT("JUNGLE THEME"));
				Room = GetWorld()->SpawnActor(RoomComponent->JungleRooms[RoomComponent->GetWeightedRandom()], &RoomLocation, &RandRotation);
				break;
			case 2:
				//UE_LOG(LogTemp, Warning, TEXT("DESERT THEME"));
				Room = GetWorld()->SpawnActor(RoomComponent->SandRooms[RoomComponent->GetWeightedRandom()], &RoomLocation, &RandRotation);
				break;
			//case 3:
			//	//UE_LOG(LogTemp, Warning, TEXT("HELL THEME"));
			//	Room = GetWorld()->SpawnActor(RoomComponent->Rooms[RoomComponent->GetWeightedRandom()], &RoomLocation, &RandRotation);
			//	break;
			}
			RoomArray.Push(Room);
		}

		TestStruct.CurrentCell = CurrentStep;
		TestStruct.Direction.SetNum(4, true);
		Testing.Add(TestStruct);

		GridLocation.Push(RoomLocation); // Store all the locations for wall use?
	}

	RoomCounter++;
}

void ADungeonDFSGen::AddWallsToGrid()
{
	for (int i = 0; i < Testing.Num(); i++)
	{
		if(Testing[i].Direction[0] == false) // North
		{
			WallProperties(0, -1000);

			Testing[i].Direction[0] = true;
		}
		if (Testing[i].Direction[1] == false) // East 
		{
			WallProperties(1000, 0);

			Testing[i].Direction[1] = true;
		}
		if (Testing[i].Direction[2] == false) // South
		{
			WallProperties(0, 1000);

			Testing[i].Direction[2] = true;
		}
		if (Testing[i].Direction[3] == false) // West
		{
			WallProperties(-1000, 0);

			Testing[i].Direction[3] = true;
		}

		CurrentWallCell++;
	}
}

void ADungeonDFSGen::WallProperties(int X, int Y)
{
	//push back wall just like the floor
	WallLocation = FVector(GridLocation[CurrentWallCell].X + X, GridLocation[CurrentWallCell].Y + Y, GridLocation[CurrentWallCell].Z);
	WallLocation.Z += 400;

	if (RoomComponent->GetTheme() < 3)
	{
		switch (RoomComponent->GetTheme())
		{
		case 0:
			//UE_LOG(LogTemp, Warning, TEXT("NORMAL THEME"));
			if (RoomComponent->Walls[0] != nullptr)
				Wall = GetWorld()->SpawnActor(RoomComponent->Walls[0], &WallLocation, NULL);
			break;
		case 1:
			//UE_LOG(LogTemp, Warning, TEXT("JUNGLE THEME"));
			if (RoomComponent->Walls[1] != nullptr)
				Wall = GetWorld()->SpawnActor(RoomComponent->Walls[1], &WallLocation, NULL);
			break;
		case 2:
			//UE_LOG(LogTemp, Warning, TEXT("DESERT THEME"));
			if (RoomComponent->Walls[2] != nullptr)
				Wall = GetWorld()->SpawnActor(RoomComponent->Walls[2], &WallLocation, NULL);
			break;
		//case 3:
		//	//UE_LOG(LogTemp, Warning, TEXT("HELL THEME"));
		//	if (RoomComponent->Walls[3] != nullptr)
		//		Wall = GetWorld()->SpawnActor(RoomComponent->Walls[3], &WallLocation, NULL);
		//	break;
		}
		WallArray.Push(Wall);
	}

	//Wall = GetWorld()->SpawnActor(ActorArray[0], &WallLocation, NULL);
	//WallArray.Push(Wall);
}

void ADungeonDFSGen::CreateLevel()
{
	Visited.Empty(); // Clear the Array
	Border.Empty(); // Clear the Array
	Testing.Empty(); // Clear the Array
	GridLocation.Empty(); // Clear the Array

	if(TeleportActor != nullptr)
		TeleportActor->Destroy();

	for (int i = 0; i < RoomArray.Num(); i++)
	{
		if (RoomArray[i] != nullptr)
			RoomArray[i]->Destroy();
	}
	RoomArray.Empty();

	for (int i = 0; i < ChestArray.Num(); i++)
	{
		if (ChestArray[i] != nullptr)
			ChestArray[i]->Destroy();
	}
	ChestArray.Empty();

	for (int i = 0; i < WallArray.Num(); i++)
	{
		if(WallArray[i] != nullptr)
			WallArray[i]->Destroy();
	}
	WallArray.Empty();

	//for (int i = 0; i < FoundEnemyActors.Num(); i++)
	//{
	//	if(FoundEnemyActors[i] != nullptr)
	//		EnemyArray[i]->Destroy();
	//}
	//EnemyArray.Empty();

	EnemyComponent->ClearEnemy();

	RoomCounter = 0;
	CurrentWallCell = 0;
	PlayerSpawned = false;
	bTeleportSpawned = false;

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

	maxChestSpawn = FMath::RandRange(3, 5);

	// Pick theme
	int Theme = FMath::RandHelper(3);
	SetLevelTheme(Theme);
}

bool ADungeonDFSGen::CanMoveCheck()
{
	if (Visited[CurrentStep + 1] && Visited[CurrentStep - 1]
		&& Visited[CurrentStep + GridWidth] && Visited[CurrentStep - GridWidth])
		return false;
	return true;
}