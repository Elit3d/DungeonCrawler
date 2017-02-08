// Fill out your copyright notice in the Description page of Project Settings.

#include "DungeonCrawler.h"
#include "ChestGeneration.h"
#include "ItemManagerComponent.h"

// Sets default values
AChestGeneration::AChestGeneration()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = Root;

	ChestLid = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChestLid"));
	ChestLid->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	ChestLid->SetRelativeScale3D(FVector(50.f, 50.f, 50.f));
	ChestLid->SetupAttachment(RootComponent);

	ChestBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChestBody"));
	ChestBody->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	ChestBody->SetRelativeScale3D(FVector(50.f, 50.f, 50.f));
	ChestBody->SetupAttachment(RootComponent);

	SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));
	SpawnArea->SetupAttachment(ChestBody);

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->OnComponentBeginOverlap.AddDynamic(this, &AChestGeneration::OnOverlapBegin);
	Collider->OnComponentEndOverlap.AddDynamic(this, &AChestGeneration::OnOverlapEnd);
	Collider->SetupAttachment(RootComponent); 

	ItemManager = CreateDefaultSubobject<UItemManagerComponent>(TEXT("ItemManager"));
}

// Called when the game starts or when spawned
void AChestGeneration::BeginPlay()
{
	Super::BeginPlay();

	//ItemList = Cast<AItemManager>(ItemListActor); // Cast to the ItemList
	RandItemToSpawn = FMath::RandRange(0, ItemManager->ItemArray.Num()); // Pick rand item between 0 and end of array list
	itemsToSpawn = FMath::RandRange(minSpawnAmount, maxSpawnAmount);
}

// Called every frame
void AChestGeneration::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//AItemManager *ItemManager = Cast<AItemManager>(ItemList);
	//ItemManager->TestFunc();

	if (Collide)
	{
		// If collided, and Interaction key pressed - Open chest
		if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::F))
		{
			Open = true;
		}
	}

	if (ItemManager != nullptr)
	{
		if (Open)
		{
			FRotator CurrentRot = ChestLid->GetComponentRotation();
			FRotator TargetRot = FRotator(0.f, 0.f, -90.f);
			FRotator ChestInterp = FMath::RInterpConstantTo(CurrentRot, TargetRot, DeltaTime, InterpSpeed);
			ChestLid->SetWorldRotation(ChestInterp);

			if (CurrentRot.Roll <= -89.f)
			{
				itemSpawnCounter++;
				//Amount to spawn
				if (itemSpawnCounter <= itemsToSpawn)
					GetWorld()->SpawnActor<AActor>(ItemManager->ItemArray[0], FVector(SpawnArea->GetComponentLocation().X, SpawnArea->GetComponentLocation().Y, SpawnArea->GetComponentLocation().Z), FRotator(0.f, 0.f, 0.f));
			}
		}
	}
	//spawn random item of random rarity with a velocity
	//set velocity on spawned object z to 1.0 
	//set velocity on spawned object xy to rand - NO MORE THAN .2
}

void AChestGeneration::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	Collide = true;
}

void AChestGeneration::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	Collide = false;
}

