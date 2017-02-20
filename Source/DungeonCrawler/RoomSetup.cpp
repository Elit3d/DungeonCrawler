// Fill out your copyright notice in the Description page of Project Settings.

#include "DungeonCrawler.h"
#include "RoomSetup.h"

#include "Engine/TargetPoint.h"
// Sets default values
ARoomSetup::ARoomSetup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	SpawnPoint1 = CreateDefaultSubobject<USphereComponent>(TEXT("SpawnPoint1"));
	SpawnPoint1->SetupAttachment(RootComponent);
	SpawnPoint2 = CreateDefaultSubobject<USphereComponent>(TEXT("SpawnPoint2"));
	SpawnPoint2->SetupAttachment(RootComponent);
	SpawnPoint3 = CreateDefaultSubobject<USphereComponent>(TEXT("SpawnPoint3"));
	SpawnPoint3->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ARoomSetup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoomSetup::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

