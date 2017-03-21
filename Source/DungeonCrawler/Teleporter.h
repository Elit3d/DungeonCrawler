// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Teleporter.generated.h"

UCLASS()
class DUNGEONCRAWLER_API ATeleporter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATeleporter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	USceneComponent *Root;
	USphereComponent *Collider;

	TArray<AActor*> FoundActor;
private:
	class ADungeonCrawlerCharacter *Character;
	bool bStartCounter = false;
	float Counter = 0.0f;
};
