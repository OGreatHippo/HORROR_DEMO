#include "HUD/MyUserWidget.h"
#include "Components/ProgressBar.h"

void UMyUserWidget::SetStamina(float _stamina)
{
	if (staminaBar)
	{
		staminaBar->SetPercent(_stamina / 100);
	}
}

void UMyUserWidget::SetColour(bool _value)
{
	if (staminaBar)
	{
		if (_value)
		{
			staminaBar->SetFillColorAndOpacity(FColor::Emerald);
		}

		else
		{
			staminaBar->SetFillColorAndOpacity(FColor::Green);
		}
	}
}
