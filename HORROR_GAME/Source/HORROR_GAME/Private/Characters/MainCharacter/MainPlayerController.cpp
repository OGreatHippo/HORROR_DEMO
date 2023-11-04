#include "Characters/MainCharacter/MainPlayerController.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"

AMainPlayerController::AMainPlayerController()
{
	character = nullptr;
	movementComponent = nullptr;
	playerInputContext = nullptr;
	moveAction = nullptr;
	sprintAction = nullptr;
	isSprinting = false;
}

void AMainPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	StaminaUsage(DeltaTime);
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
		if (character->stamina > 0)
		{
			movementComponent->MaxWalkSpeed = 1000.0f;
			isSprinting = true;
		}
	}
}

void AMainPlayerController::StopSprinting()
{
	if (character)
	{
		movementComponent->MaxWalkSpeed = 600.0f;
		isSprinting = false;
	}
}

void AMainPlayerController::StaminaUsage(float deltaTime)
{
	if (character)
	{
		if (isSprinting && character->stamina > 0)
		{
			character->stamina -= 5 * deltaTime;

			if (character->stamina <= 0)
			{
				StopSprinting();
			}
		}

		else if (!isSprinting && character->stamina < 100)
		{
			character->stamina += 2 * deltaTime;
		}
	}
}

