// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Systems/Character/Base/BaseCharacter.h"

#include "EnhancedInputComponent.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "Core/Systems/Interaction/PlayerInteraction.h"
#include "Core/Systems/Interaction/Items/Item.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	// Find the PhysicsHandleComponent on the owner
	PhysicsHandle = FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("BaseCharacterInteraction: No UPhysicsHandleComponent"));
	}

	// Find the camera component on the owner
	PlayerCameraRef = FindComponentByClass<UCameraComponent>();
	if (!PlayerCameraRef)
	{
		UE_LOG(LogTemp, Error, TEXT("BaseCharacterInteraction: No UCameraComponent found"));
	}
	if (InteractionWidgetClass)
	{
		InteractionWidget = CreateWidget<UUserWidget>(GetWorld(), InteractionWidgetClass);
		if (InteractionWidget)
		{
			InteractionWidget->AddToViewport();
			InteractionWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	if (PlayerWidgetClass)
	{
		PlayerWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerWidgetClass);
		if (PlayerWidget)
		{
			PlayerWidget->AddToViewport();
			PlayerWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	if (!PhysicsHandle || !PlayerCameraRef) return;
	
	if (PhysicsHandle->GetGrabbedComponent())
	{
		FVector TargetLocation(
			PlayerCameraRef->GetComponentLocation() + (PlayerCameraRef->GetForwardVector() * 200.f));

		PhysicsHandle->SetTargetLocation(TargetLocation);
	}
	
	CheckForInteractable();
}

void ABaseCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComp->BindAction(InteractionAction, ETriggerEvent::Started, this, &ABaseCharacter::Interact);

		EnhancedInputComp->BindAction(GrabAction, ETriggerEvent::Started, this, &ABaseCharacter::Grab);
		EnhancedInputComp->BindAction(GrabAction, ETriggerEvent::Completed, this, &ABaseCharacter::Release);
	}
}

void ABaseCharacter::Interact(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Error, TEXT("BaseCharacterInteraction: Interact"));
	FHitResult* Hit = new FHitResult();
	FVector start = PlayerCameraRef->GetComponentLocation();
	FVector end = start + (PlayerCameraRef->GetForwardVector() * 1000);

	UKismetSystemLibrary::SphereTraceSingle(this, start, end, 5.0f, UEngineTypes::ConvertToTraceType(ECC_Visibility),
	false, TArray<AActor*>(), EDrawDebugTrace::Persistent, *Hit, true);
    
	if (Hit->GetActor() != nullptr)
	{
		if (Hit->GetActor()->GetClass()->ImplementsInterface(UPlayerInteraction::StaticClass()))
		{
			IPlayerInteraction::Execute_blueprintInteraction(Hit->GetActor(), this);
		}
	}
}

void ABaseCharacter::Grab()
{
	FHitResult Hit;
	FVector start = PlayerCameraRef->GetComponentLocation();
	FVector end = start + (PlayerCameraRef->GetForwardVector() * 500);

	ECollisionChannel GrabChannel = ECollisionChannel::ECC_Visibility;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());
	DrawDebugLine(
		GetWorld(),
		start,
		end,
		FColor::Yellow,
		false,
		2.0f,
		0,
		2.0f
		);
	if (GetWorld()->LineTraceSingleByChannel(Hit, start,end, GrabChannel, CollisionParams))
	{
		AItem* HitItem = Cast<AItem>(Hit.GetActor());
		
		if (HitItem != nullptr) //need a check for the if statement
		{
			UE_LOG(LogTemp, Warning, TEXT("%s"), *HitItem->GetName());
			UPrimitiveComponent* comp = Hit.GetComponent();
			PhysicsHandle->GrabComponentAtLocation(
			comp,
			NAME_None,
			Hit.ImpactPoint
			);
			HitItem->bIsHeld = true;
		}
	}
	
}

void ABaseCharacter::Release()
{
	if (PhysicsHandle->GetGrabbedComponent())
	{
		PhysicsHandle->ReleaseComponent();
	}
}

void ABaseCharacter::CheckForInteractable()
{
	FHitResult Hit;
	FVector Start = PlayerCameraRef->GetComponentLocation();
	FVector End = Start + (PlayerCameraRef->GetForwardVector() * 1000.f);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params);

	AActor* HitActor = bHit ? Hit.GetActor() : nullptr;

	// Only update if our look target has changed
	if (HitActor == CurrentLookTarget) return;
	CurrentLookTarget = HitActor;

	bool bIsInteractable = HitActor &&
		HitActor->GetClass()->ImplementsInterface(UPlayerInteraction::StaticClass());

	if (InteractionWidget)
	{
		InteractionWidget->SetVisibility(
			bIsInteractable ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}
}

