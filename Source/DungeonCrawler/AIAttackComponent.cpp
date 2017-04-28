// Fill out your copyright notice in the Description page of Project Settings.

#include "DungeonCrawler.h"
#include "AIAttackComponent.h"

#include "Engine.h"

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



bool UAIAttackComponent::RayCastAttack(FVector Start, FVector End, AActor* IgnoreActor, AActor* Actor)
{
	DrawDebugLine(GetWorld(), Start, End, FColor::Red);

	FHitResult out;

	FCollisionQueryParams params;
	params.AddIgnoredActor(IgnoreActor);

	if (GetWorld()->LineTraceSingleByChannel(out, Start, End, ECollisionChannel::ECC_Visibility, params))
	{
		if (out.GetActor() == Actor)
		{
			return true;
		}
	}
	return false;
}

void UAIAttackComponent::EnemyAttack()
{
	//switch (AttackType)
	//{
	//case EAttackType::AT_Melee:
	//	UE_LOG(LogTemp, Warning, TEXT("Attacking player...MELEE"));
	//	if (RayCastAttack(FVector(0, 0, 0), FVector(0, 0, 0), AActor))
	//	{
	//		GetWorld()->
	//	}
	//	break;
	//case EAttackType::AT_Range:
	//	UE_LOG(LogTemp, Warning, TEXT("Attacking player...RANGE"));
	//	break;
	//case EAttackType::AT_Magic:
	//	UE_LOG(LogTemp, Warning, TEXT("Attacking player...MAGIC"));
	//	break;
	//}
}

void UAIAttackComponent::SpawnProjectile()
{
}

EAttackType UAIAttackComponent::GetAttackType()
{
	return CurrentAttack;
}

void UAIAttackComponent::SetAttackType(EAttackType AttackType)
{
	CurrentAttack = AttackType;
}


