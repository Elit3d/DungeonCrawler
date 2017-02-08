// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DungeonDFSGen.generated.h"

UCLASS()
class DUNGEONCRAWLER_API ADungeonDFSGen : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADungeonDFSGen();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	int RandomDirection();
	
	UPROPERTY(EditAnywhere, Category = "Room Component")
		class UCreateRoomComponent *RoomComponent;
private:
	FVector2D MapWidth;

};
