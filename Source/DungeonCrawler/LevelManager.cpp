// Fill out your copyright notice in the Description page of Project Settings.

#include "DungeonCrawler.h"
#include "LevelManager.h"

#include "DungeonDFSGen.h"
// Sets default values
ALevelManager::ALevelManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALevelManager::BeginPlay()
{
	Super::BeginPlay();
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADungeonDFSGen::StaticClass(), DungeonActor);
}

// Called every frame
void ALevelManager::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	for (AActor *Actor : DungeonActor)
	{
		DFS_Gen = Cast<ADungeonDFSGen>(Actor);

		if (DFS_Gen != nullptr)
		{
			if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::E)) // check that all enemies are dead
			{
				DFS_Gen->CreateLevel();
				int Theme = FMath::RandHelper(4); // 4 different themes to chose from
				DFS_Gen->SetLevelTheme(Theme);
			}
		}
	}
}

