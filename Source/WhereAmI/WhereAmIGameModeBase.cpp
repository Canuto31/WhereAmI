// Copyright Epic Games, Inc. All Rights Reserved.


#include "WhereAmIGameModeBase.h"

#include "PlayerCharacter.h"

AWhereAmIGameModeBase::AWhereAmIGameModeBase()
{
	DefaultPawnClass = APlayerCharacter::StaticClass(); //Definition of the player character into the default pawn class in the game mode code
}
