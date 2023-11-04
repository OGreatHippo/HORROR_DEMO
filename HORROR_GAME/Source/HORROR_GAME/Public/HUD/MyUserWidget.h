#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"

UCLASS(ABSTRACT)
class HORROR_GAME_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UProgressBar* staminaBar;

	void SetStamina(float _stamina);

	void SetColour(bool _value);
};
