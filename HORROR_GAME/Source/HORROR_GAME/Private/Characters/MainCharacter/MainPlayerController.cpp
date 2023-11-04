#include "Characters/MainCharacter/MainPlayerController.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"

AMainPlayerController::AMainPlayerController()
{
	character = nullptr;
}

void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		enhancedInputComponent->BindAction(moveAction, ETriggerEvent::Triggered, this, &AMainPlayerController::Move);
		enhancedInputComponent->BindAction(sprintAction, ETriggerEvent::Triggered, this, &AMainPlayerController::Sprint);
		enhancedInputComponent->BindAction(sprintAction, ETriggerEvent::Completed, this, &AMainPlayerController::StopSprinting);
	}
}

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		subsystem->AddMappingContext(playerInputContext, 0);
	}

	character = Cast<AMainCharacter>(GetPawn());
	movementComponent = character->GetCharacterMovement();
}

void AMainPlayerController::Move(const FInputActionValue& value)
{
	const FVector2D movementVector = value.Get<FVector2D>();

	const FVector forward = character->GetActorForwardVector();
	character->AddMovementInput(forward, movementVector.Y);

	const FVector right = character->GetActorRightVector();
	character->AddMovementInput(right, movementVector.X);
}

void AMainPlayerController::Sprint()
{
	if (character)
	{
		movementComponent->MaxWalkSpeed = 1000.0f;
	}
}

void AMainPlayerController::StopSprinting()
{
	if (character)
	{
		movementComponent->MaxWalkSpeed = 600.0f;
	}
}

