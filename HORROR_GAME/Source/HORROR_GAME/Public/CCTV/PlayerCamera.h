#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "Components/BoxComponent.h"
#include "PlayerCamera.generated.h"

UCLASS()
class HORROR_GAME_API APlayerCamera : public ACameraActor
{
	GENERATED_BODY()
	
public:
	APlayerCamera();

	virtual void BeginPlay() override;

	FViewTargetTransitionParams transParams;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		bool startingCamera;

	APlayerController* playerController;

	UBoxComponent* boxCollider;

	UFUNCTION()
	void OnBoxColliderOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
