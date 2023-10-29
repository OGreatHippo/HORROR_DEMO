#include "Characters/MainCharacter/MainPlayerController.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "Engine/LocalPlayer.h"

AMainPlayerController::AMainPlayerController()
{
}

void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		enhancedInputComponent->BindAction(moveAction, ETriggerEvent::Triggered, this, &AMainPlayerController::Move);
	}
}

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		subsystem->AddMappingContext(playerInputContext, 0);
	}
}

void AMainPlayerController::Move(const FInputActionValue& value)
{
	const FVector2D movementVector = value.Get<FVector2D>();

	APawn* controlledPawn = GetPawn();

	const FVector forward = controlledPawn->GetActorForwardVector();
	controlledPawn->AddMovementInput(forward, movementVector.Y);

	const FVector right = controlledPawn->GetActorRightVector();
	controlledPawn->AddMovementInput(right, movementVector.X);	
}

