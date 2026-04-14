// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class UPhysicsHandleComponent;
class UCameraComponent;

UCLASS()
class ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UFUNCTION() void Interact(const FInputActionValue& Value);
	UFUNCTION() void Grab();
	UFUNCTION() void Release();

	UPROPERTY(VisibleAnywhere, Category = "Player") UPhysicsHandleComponent* PhysicsHandle;
	UPROPERTY(EditDefaultsOnly, Category = "Player | input") UInputAction* InteractionAction;
	UPROPERTY(EditDefaultsOnly, Category = "Player | input") UInputAction* GrabAction;
	
	UPROPERTY(VisibleAnywhere, Category = "Player | Camera") UCameraComponent* PlayerCameraRef;
};
