// Copyright Epic Games, Inc. All Rights Reserved.

#include "CubeShifterGameMode.h"
#include "CubeShifterHUD.h"
#include "CubeShifterCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACubeShifterGameMode::ACubeShifterGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ACubeShifterHUD::StaticClass();
}
