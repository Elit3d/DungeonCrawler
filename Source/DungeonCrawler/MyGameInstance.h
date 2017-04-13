// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONCRAWLER_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UMyGameInstance();

	UFUNCTION(BlueprintCallable, Category=Health)
		void SetHealth(float _Health);
	UFUNCTION(BlueprintCallable, Category = Health)
		float GetHealth();
	UFUNCTION(BlueprintCallable, Category = Health)
		void SetLevelID(int _ID);
	UFUNCTION(BlueprintCallable, Category = Health)
		int GetLevelID();
private:
	float Health = 100;
	int LevelID = 0;
};
