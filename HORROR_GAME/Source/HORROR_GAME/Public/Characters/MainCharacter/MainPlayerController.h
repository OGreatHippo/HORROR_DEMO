#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Characters/MainCharacter/MainCharacter.h"
#include "MainPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class HORROR_GAME_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMainPlayerController();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void SetupInputComponent() override;

	virtual void BeginPlay();

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		UInputMappingContext* playerInputContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		UInputAction* moveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		UInputAction* sprintAction;

	void Move(const FInputActionValue& value);

	void Sprint();
	void StopSprinting();

	/* HUD */

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UMyUserWidget> playerHUDClass;

	UPROPERTY()
		class UMyUserWidget* playerHUD;

private:
	AMainCharacter* character;
	UCharacterMovementComponent* movementComponent;

	bool isSprinting;
	bool isExhausted;

	void StaminaUsage(float deltaTime);
};
