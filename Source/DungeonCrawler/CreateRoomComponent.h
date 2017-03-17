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

	int GetWeightedRandom();


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
	UPROPERTY(EditAnywhere, Category = "Static Room Mesh")
		TArray<TSubclassOf<class AActor>> Rooms;
	UPROPERTY(EditAnywhere, Category = "Static Room Mesh")
		TArray<TSubclassOf<class AActor>> JungleRooms;
	UPROPERTY(EditAnywhere, Category = "Random Room Chance")
		TArray<int32> ChanceOfRoom; // Gives us a value of the room being spawned

	UPROPERTY(EditAnywhere, Category = "Level Spawn Actor")
		AActor *Chest;
	UPROPERTY(EditAnywhere, Category = "Level Spawn Actor")
		TArray<TSubclassOf<class AActor>> AI;

	int GetTheme();
	void SetLevelTheme(int _theme);
private:
	int theme;
};
