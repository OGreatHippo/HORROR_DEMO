#include "CCTV/CCTVActor.h"

// Sets default values
ACCTVActor::ACCTVActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACCTVActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACCTVActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

