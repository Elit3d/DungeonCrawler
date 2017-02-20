// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "RoomSetup.generated.h"

UCLASS()
class DUNGEONCRAWLER_API ARoomSetup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoomSetup();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere)
		USceneComponent *Root;
	UPROPERTY(EditAnywhere)
		USphereComponent* SpawnPoint1;
	UPROPERTY(EditAnywhere)
		USphereComponent* SpawnPoint2;
	UPROPERTY(EditAnywhere)
		USphereComponent* SpawnPoint3;
};
