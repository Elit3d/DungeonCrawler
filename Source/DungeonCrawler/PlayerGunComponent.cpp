// Fill out your copyright notice in the Description page of Project Settings.

#include "DungeonCrawler.h"
#include "PlayerGunComponent.h"
#include "Engine.h"
#include "EnemyCharacter.h"

// Sets default values for this component's properties
UPlayerGunComponent::UPlayerGunComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerGunComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPlayerGunComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

bool UPlayerGunComponent::RaycastFire(FVector Start, FVector End, AActor *Ignore, FName Tag)
{
	DrawDebugLine(GetWorld(), Start, End, FColor::Red, true);

	FHitResult Out;
	FCollisionQueryParams Param;
	Param.AddIgnoredActor(Ignore);

	if (GetWorld()->LineTraceSingleByChannel(Out, Start, End, ECollisionChannel::ECC_Visibility, Param))
	{
		if (Out.GetActor() != nullptr)
		{
			if (Out.GetActor()->ActorHasTag("Enemy"))
			{
				AEnemyCharacter *Enemy = Cast<AEnemyCharacter>(Out.GetActor());

				if (Enemy != nullptr)
				{
					Enemy->SetHealth(Enemy->GetHealth() - 1);
				}
				return true;
			}
		}
	}
	return false;
}

