// Copyright Epic Games, Inc. All Rights Reserved.

#include "VoxelPlanetGameMode.h"
#include "VoxelPlanetHUD.h"
#include "VoxelPlanetCharacter.h"
#include "UObject/ConstructorHelpers.h"

AVoxelPlanetGameMode::AVoxelPlanetGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AVoxelPlanetHUD::StaticClass();
}
