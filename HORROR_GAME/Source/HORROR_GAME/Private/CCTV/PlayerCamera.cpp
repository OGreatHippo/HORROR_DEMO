#include "CCTV/PlayerCamera.h"
#include "Camera/CameraComponent.h"

APlayerCamera::APlayerCamera()
{
}

void APlayerCamera::BeginPlay()
{
	boxCollider = FindComponentByClass<UBoxComponent>();

	if (boxCollider)
	{
	}

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

void APlayerCamera::ChangeCamera()
{
}
