#include "MyGameMode.h"

AMyGameMode::AMyGameMode()
{
	FSoftClassPath PawnClassPath(TEXT("/Game/Blueprints/Character/BP_PlayerCharacter.BP_PlayerCharacter_C"));
	TSoftClassPtr<APawn> PawnClassRef(PawnClassPath);

	if (UClass* LoadedPawnClass = PawnClassRef.LoadSynchronous())
	{
		DefaultPawnClass = LoadedPawnClass;
		UE_LOG(LogTemp, Warning, TEXT("Soft loaded pawn: %s"), *DefaultPawnClass->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to soft load BP_PlayerCharacter."));
	}
}
