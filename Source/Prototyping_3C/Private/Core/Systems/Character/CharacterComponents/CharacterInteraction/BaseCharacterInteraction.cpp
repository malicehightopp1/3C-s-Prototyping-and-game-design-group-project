// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Systems/Character/CharacterComponents/CharacterInteraction/BaseCharacterInteraction.h"

#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "Core/Systems/Interaction/PlayerInteraction.h"
#include "Core/Systems/Interaction/Items/Item.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UBaseCharacterInteraction::UBaseCharacterInteraction()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UBaseCharacterInteraction::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UBaseCharacterInteraction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

