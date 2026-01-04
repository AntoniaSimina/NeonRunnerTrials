// Copyright Epic Games, Inc. All Rights Reserved.

#include "NeonRunnerTrialsGameMode.h"
#include "NeonRunnerTrialsCharacter.h"
#include "UObject/ConstructorHelpers.h"

ANeonRunnerTrialsGameMode::ANeonRunnerTrialsGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
