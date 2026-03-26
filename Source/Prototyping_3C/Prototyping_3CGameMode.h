// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Prototyping_3CGameMode.generated.h"

/**
 *  Simple GameMode for a third person game
 */
UCLASS(abstract)
class APrototyping_3CGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	/** Constructor */
	APrototyping_3CGameMode();
};



