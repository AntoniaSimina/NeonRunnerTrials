#include "RotatingPlatform.h"

#include "Components/StaticMeshComponent.h"

ARotatingPlatform::ARotatingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;

	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>("PlatformMesh");
	PlatformMesh->SetupAttachment(Root);
}

void ARotatingPlatform::BeginPlay()
{
	Super::BeginPlay();
}

void ARotatingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(
		FRotator(0.f, RotationSpeed * DeltaTime, 0.f)
	);
}
