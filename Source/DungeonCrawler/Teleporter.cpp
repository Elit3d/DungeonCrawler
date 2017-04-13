// Fill out your copyright notice in the Description page of Project Settings.

#include "DungeonCrawler.h"
#include "Teleporter.h"
#include "DungeonCrawlerCharacter.h"
#include "DungeonDFSGen.h"
#include "MyGameInstance.h"

// Sets default values
ATeleporter::ATeleporter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ATeleporter::OnOverlapBegin);
	Collider->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void ATeleporter::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADungeonDFSGen::StaticClass(), FoundActor);
}

// Called every frame
void ATeleporter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (bStartCounter)
	{
		Counter += DeltaTime;
		DisableInput(GetWorld()->GetFirstPlayerController()); // Stop the player from moving whilst teleporting
		if (Counter >= 3.0f)
		{
			Counter = 0.0f;

			for (AActor* TActor : FoundActor)
			{
				ADungeonDFSGen* MyActor = Cast<ADungeonDFSGen>(TActor);

				if (MyActor != nullptr)
				{
					UMyGameInstance *Instance = Cast<UMyGameInstance>(GetGameInstance());
					if (Instance != nullptr)
					{
						if(Instance->GetLevelID() + 1 == 4)
						{
							// Load boss level
							UGameplayStatics::OpenLevel(GetWorld(), "BossLevel");
						}
						else
						{
							UGameplayStatics::OpenLevel(GetWorld(), "Dungeon1"); // Reload level so we can show the loading bar again
							MyActor->CreateLevel();
							int Theme = FMath::RandHelper(4);
							UE_LOG(LogTemp, Warning, TEXT("theme that we are going to is %d"), Theme);
							MyActor->SetLevelTheme(Theme);
							Instance->SetLevelID(Instance->GetLevelID() + 1);
						}
					}
				}
			}
		}
	}
}

void ATeleporter::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	Character = Cast<ADungeonCrawlerCharacter>(OtherActor); //cast OtherActor to character, checks the overlapping actor

	if (Character != nullptr) // check that it isnt null to avoid any crashes
	{
		bStartCounter = true;
	}
}

