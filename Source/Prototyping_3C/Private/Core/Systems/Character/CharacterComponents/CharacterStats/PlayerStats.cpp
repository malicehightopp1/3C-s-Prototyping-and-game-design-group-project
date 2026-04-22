// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Systems/Character/CharacterComponents/CharacterStats/PlayerStats.h"

// Sets default values for this component's properties
UPlayerStats::UPlayerStats()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerStats::BeginPlay()
{
	Super::BeginPlay();
	
	MaxHealth = 100.0f;
	CurrentHealth = MaxHealth;
	OnHealthChanged.Broadcast(CurrentHealth, MaxHealth);
}


// Called every frame
void UPlayerStats::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UPlayerStats::HealthChange(float HealthToLose)
{
	CurrentHealth -= HealthToLose;
	
	CurrentHealth = FMath::Clamp(CurrentHealth, 0, MaxHealth);
	
	if (CurrentHealth <= 0.0f)
	{
		UE_LOG(LogTemp, Error, TEXT("Player has died!! (health is less than or equal to 0)"));
	}
	OnHealthChanged.Broadcast(CurrentHealth, MaxHealth);
}

