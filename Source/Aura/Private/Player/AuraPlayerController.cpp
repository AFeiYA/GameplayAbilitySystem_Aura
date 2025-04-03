// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	//entity changed on the server will be sent down to the clients.
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	
	CursorTrace();
}
void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;
	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());
	/**
	 * Line trace from cursor. There are several scenarios:
	 * A. LastActor is null and ThisActor is null
	 *		- Do nothing
	 * B. LastActor is null and ThisActor is valid
	 *		- Highlight This Actor
	 * C. LastActor is valid and This Actor is null
	 *		- UnHighlight LastActor
	 * D. Both actors are valid, but LasterActor != ThisActor
	 *		- UnHighlight LastActor , and Highlight ThisActor
	 * E. Both actors are valid, and they are the same actor.
	 *		- Do nothing
	 */
	if (LastActor==nullptr)
	{
		if (ThisActor==nullptr)
		{
			// Case A
		}
		else
		{
			ThisActor->HighlightActor();// Case B
		}
	}
	else
	{
		if (ThisActor==nullptr)
		{
			LastActor->UnHighlightActor();// Case C
		}
		else // both actors are valid
		{
			if (ThisActor!=LastActor) // Case D
			{
				ThisActor->HighlightActor();
				LastActor->UnHighlightActor();
			}
			else
			{
				// Case E
			}
		}
	}
}
void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);
	// subsystem is singleton only one can be existed in  
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	//assert 
	check(Subsystem);
	Subsystem->AddMappingContext(AuraContext,0);
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);	
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
	
	
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2d InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);
	// because Move is called every frame,
	// it might be earlier then APawn is valid. so check pointer is not null instead of using check(APawn) to assert.
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
	
}
