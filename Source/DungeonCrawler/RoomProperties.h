// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "RoomProperties.generated.h"

UCLASS()
class DUNGEONCRAWLER_API ARoomProperties : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoomProperties();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere, Category=Walls)
		TArray<AActor*> WallsTop;
	UPROPERTY(EditAnywhere, Category = Walls)
		TArray<AActor*> WallsRight;
	UPROPERTY(EditAnywhere, Category = Walls)
		TArray<AActor*> WallsBottom;
	UPROPERTY(EditAnywhere, Category = Walls)
		TArray<AActor*> WallsLeft;
private:
	int width;
	int height;
	int x;
	int y;
	int amountOfRooms;
//	int positionOfWall;
	int doorPosition; //0 = top //1 = right //2 = bottom //3 = left
};
