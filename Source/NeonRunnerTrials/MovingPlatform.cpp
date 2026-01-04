#include "MovingPlatform.h"

#include "Components/StaticMeshComponent.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);

	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>("PlatformMesh");
	PlatformMesh->SetupAttachment(Root);

	PlatformMesh->SetCollisionProfileName("BlockAll");
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
	TargetLocation = StartLocation + MoveOffset;
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = GetActorLocation();
	FVector Destination = bMovingToTarget ? TargetLocation : StartLocation;

	FVector Direction = (Destination - CurrentLocation).GetSafeNormal();
	FVector NewLocation = CurrentLocation + Direction * MoveSpeed * DeltaTime;

	SetActorLocation(NewLocation);

	// Check if reached destination
	if (FVector::Dist(NewLocation, Destination) < 5.f)
	{
		bMovingToTarget = !bMovingToTarget;
	}
}
