// Copyright Epic Games, Inc. All Rights Reserved.

#include "MazeOfNightmaresGameMode.h"
#include "MazeOfNightmaresCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMazeOfNightmaresGameMode::AMazeOfNightmaresGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
