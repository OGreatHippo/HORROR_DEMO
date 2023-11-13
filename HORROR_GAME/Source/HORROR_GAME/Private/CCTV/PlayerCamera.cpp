#include "CCTV/PlayerCamera.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"

APlayerCamera::APlayerCamera()
{
}

void APlayerCamera::BeginPlay()
{
	playerController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());

	boxCollider = FindComponentByClass<UBoxComponent>();

	if (boxCollider)
	{
		boxCollider->OnComponentBeginOverlap.AddDynamic(this, &APlayerCamera::OnBoxColliderOverlap);
	}

	if (startingCamera)
	{
		if (playerController)
		{
			FViewTargetTransitionParams transParams;
			playerController->SetViewTarget(this, transParams);
		}
	}
}

void APlayerCamera::OnBoxColliderOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("sup"));
}
