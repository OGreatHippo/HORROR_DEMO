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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		bool startingCamera;

	UPROPERTY(VisibleAnywhere)
		UBoxComponent* boxCollider;
};
