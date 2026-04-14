// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerInteraction.generated.h"


class ABaseCharacter;

UINTERFACE(MinimalAPI, Blueprintable)
class UPlayerInteraction : public UInterface
{
	GENERATED_BODY()
	
};


class IPlayerInteraction //Must match the UPlayerInteraction
{
	GENERATED_BODY()

public:
	UFUNCTION() virtual void Interaction(ABaseCharacter* player) = 0;
};
