// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "DungeonCrawler.h"
#include "DungeonCrawlerGameMode.h"
#include "DungeonCrawlerHUD.h"
#include "DungeonCrawlerCharacter.h"

ADungeonCrawlerGameMode::ADungeonCrawlerGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ADungeonCrawlerHUD::StaticClass();
}
