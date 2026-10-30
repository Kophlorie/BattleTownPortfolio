// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BattleTownPrototypeGameMode.generated.h"

/**
 *  Simple GameMode for a third person game
 */
UCLASS(abstract)
class ABattleTownPrototypeGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	/** Constructor */
	ABattleTownPrototypeGameMode();
};



