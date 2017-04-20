// Fill out your copyright notice in the Description page of Project Settings.

#include "DungeonCrawler.h"
#include "PlayerRaycastComponent.h"
#include "Engine.h"
#include "DungeonCrawlerCharacter.h"
#include "MyGameInstance.h"

// Sets default values for this component's properties
UPlayerRaycastComponent::UPlayerRaycastComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerRaycastComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPlayerRaycastComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UPlayerRaycastComponent::PlayerRaycast(FVector Start, FVector End, AActor *Ignore)
{
	//DrawDebugLine(GetWorld(), Start, End, FColor::Red); // Debug line

	FHitResult out;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Ignore);

	if (GetWorld()->LineTraceSingleByChannel(out, Start, End, ECollisionChannel::ECC_Visibility, Params))
	{
		//UE_LOG(LogTemp, Warning, TEXT("%s"), out.GetActor()->GetName());
		if (GetWorld()->GetFirstPlayerController()->WasInputKeyJustPressed(EKeys::F))
		{
			if (out.GetActor() != nullptr)
			{
				if (out.GetActor()->ActorHasTag("Health"))
				{
					UMyGameInstance* Instance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());

					if (Instance != nullptr)
					{
						if (Instance->GetHealth() < 100)
						{
							Instance->SetHealth(Instance->GetHealth() + 5);
						}
					}
				}
				if (out.GetActor()->ActorHasTag("Ammo"))
					UE_LOG(LogTemp, Warning, TEXT("Ammo Picked Up"));
				if (out.GetActor()->ActorHasTag("Item"))
				{
					out.GetActor()->Destroy();
				}
			}
		}
	}
}

