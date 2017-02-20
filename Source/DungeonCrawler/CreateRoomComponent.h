// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CreateRoomComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONCRAWLER_API UCreateRoomComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCreateRoomComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UPROPERTY(EditAnywhere, Category = "Room Properties")
		int Width = 5;
	UPROPERTY(EditAnywhere, Category = "Room Properties")
		int Height = 5;
	UPROPERTY(EditAnywhere, Category = "Room Properties")
		int X = 0;
	UPROPERTY(EditAnywhere, Category = "Room Properties")
		int Y = 0;
	UPROPERTY(EditAnywhere, Category = "Room Properties")
		int NumberOfRooms = 20;
	UPROPERTY(EditAnywhere, Category = "Static Mesh")
		TArray<TSubclassOf<class ARoomSetup>> Rooms;
	//UPROPERTY(EditAnywhere, Category = "Chest spawns")
	//	TArray<ATargetPoint*> TargetPoint;
private:
};
