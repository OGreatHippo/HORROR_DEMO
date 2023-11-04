#include "Characters/MainCharacter/MainPlayerController.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Blueprint/UserWidget.h"
#include "HUD/MyUserWidget.h"

AMainPlayerController::AMainPlayerController()
{
	character = nullptr;
	movementComponent = nullptr;
	playerInputContext = nullptr;
	moveAction = nullptr;
	sprintAction = nullptr;
	isSprinting = false;

	/* HUD */

	playerHUDClass = nullptr;
	playerHUD = nullptr;
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

	if (IsLocalPlayerController() && playerHUDClass)
	{
		playerHUD = CreateWidget<UMyUserWidget>(this, playerHUDClass);
		check(playerHUD);
		playerHUD->AddToPlayerScreen();
		playerHUD->SetStamina(character->stamina);
		playerHUD->SetColour(isExhausted);
	}
}

void AMainPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (playerHUD)
	{
		playerHUD->RemoveFromParent();
		playerHUD = nullptr;
	}

	Super::EndPlay(EndPlayReason);
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
		if (character->stamina > 0 && !isExhausted)
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
		if (isSprinting && character->stamina > 0 && !isExhausted)
		{
			character->stamina -= 15 * deltaTime;
			playerHUD->SetStamina(character->stamina);

			if (character->stamina <= 0)
			{
				StopSprinting();
				isExhausted = true;
				playerHUD->SetColour(isExhausted);
			}
		}

		else if (!isSprinting && character->stamina < 100)
		{
			character->stamina += 5 * deltaTime;
			playerHUD->SetStamina(character->stamina);

			if (character->stamina >= 30)
			{
				isExhausted = false;
				playerHUD->SetColour(isExhausted);
			}
		}
	}
}

