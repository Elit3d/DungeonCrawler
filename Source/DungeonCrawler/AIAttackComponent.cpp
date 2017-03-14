// Fill out your copyright notice in the Description page of Project Settings.

#include "DungeonCrawler.h"
#include "AIAttackComponent.h"


// Sets default values for this component's properties
UAIAttackComponent::UAIAttackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAIAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAIAttackComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UAIAttackComponent::EnemyAttack()
{
	switch (AttackType)
	{
	case EAttackType::AT_Melee:
		UE_LOG(LogTemp, Warning, TEXT("Attacking player...MELEE"));
		break;
	case EAttackType::AT_Range:
		UE_LOG(LogTemp, Warning, TEXT("Attacking player...RANGE"));
		break;
	case EAttackType::AT_Magic:
		UE_LOG(LogTemp, Warning, TEXT("Attacking player...MAGIC"));
		break;
	}
}

