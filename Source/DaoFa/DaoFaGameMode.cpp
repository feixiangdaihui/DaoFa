// Copyright Epic Games, Inc. All Rights Reserved.

#include "DaoFaGameMode.h"
#include "DaoFaCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADaoFaGameMode::ADaoFaGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
