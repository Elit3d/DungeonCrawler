// Fill out your copyright notice in the Description page of Project Settings.

#include "DungeonCrawler.h"
#include "MyGameInstance.h"



UMyGameInstance::UMyGameInstance()
{

}

void UMyGameInstance::SetHealth(float _Health)
{
	Health = _Health;
}

float UMyGameInstance::GetHealth()
{
	return Health;
}

void UMyGameInstance::SetLevelID(int _ID)
{
	LevelID = _ID;
}

int UMyGameInstance::GetLevelID()
{
	return LevelID;
}

