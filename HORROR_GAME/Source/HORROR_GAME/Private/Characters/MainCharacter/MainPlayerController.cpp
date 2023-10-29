#include "Characters/MainCharacter/MainPlayerController.h"
#include "EnhancedInputSubsystems.h"
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
		enhancedInputComponent->BindAction(moveAction, ETriggerEvent::Triggered, this, &ATestPlayerController::MoveTriggered);
		enhancedInputComponent->BindAction(moveAction, ETriggerEvent::Completed, this, &ATestPlayerController::MoveReleased);
	}
}

void AMainPlayerController::BeginPlay()
{

}

void AMainPlayerController::Move(const FInputActionValue& value)
{

}
