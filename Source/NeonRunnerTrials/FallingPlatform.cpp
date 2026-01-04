#include "FallingPlatform.h"

#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "RunnerCharacter.h"
#include "TimerManager.h"

AFallingPlatform::AFallingPlatform()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);

	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>("PlatformMesh");
	PlatformMesh->SetupAttachment(Root);
	PlatformMesh->SetCollisionProfileName("BlockAll");

	TriggerBox = CreateDefaultSubobject<UBoxComponent>("TriggerBox");
	TriggerBox->SetupAttachment(Root);
	TriggerBox->SetBoxExtent(FVector(100.f, 100.f, 50.f));
	TriggerBox->SetCollisionProfileName("Trigger");
}

void AFallingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
	TriggerBox->OnComponentBeginOverlap.AddDynamic(
		this, &AFallingPlatform::OnTriggerOverlap
	);
}

void AFallingPlatform::OnTriggerOverlap(
	UPrimitiveComponent*,
	AActor* OtherActor,
	UPrimitiveComponent*,
	int32,
	bool,
	const FHitResult&
)
{
	if (bHasFallen) return;

	if (Cast<ARunnerCharacter>(OtherActor))
	{
		bHasFallen = true;

		GetWorldTimerManager().SetTimer(
			FallTimerHandle,
			this,
			&AFallingPlatform::StartFalling,
			DelayBeforeFall,
			false
		);
	}
}

void AFallingPlatform::StartFalling()
{
	PlatformMesh->SetSimulatePhysics(true);

	GetWorldTimerManager().SetTimer(
		RespawnTimerHandle,
		this,
		&AFallingPlatform::Respawn,
		RespawnDelay,
		false
	);
}

void AFallingPlatform::Respawn()
{
	PlatformMesh->SetSimulatePhysics(false);
	SetActorLocation(StartLocation);

	bHasFallen = false;
}
