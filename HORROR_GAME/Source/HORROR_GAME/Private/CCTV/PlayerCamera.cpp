#include "CCTV/PlayerCamera.h"
#include "Camera/CameraComponent.h"

APlayerCamera::APlayerCamera()
{
}

void APlayerCamera::BeginPlay()
{
	if (startingCamera)
	{
		APlayerController* playerController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());

		if (playerController)
		{
			FViewTargetTransitionParams transParams;
			playerController->SetViewTarget(this, transParams);
		}
	}
}
