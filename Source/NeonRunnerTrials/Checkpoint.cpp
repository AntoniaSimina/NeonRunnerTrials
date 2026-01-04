#include "Checkpoint.h"

#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "RunnerCharacter.h"

ACheckpoint::ACheckpoint()
{
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);

	TriggerSphere = CreateDefaultSubobject<USphereComponent>("TriggerSphere");
	TriggerSphere->SetupAttachment(Root);
	TriggerSphere->SetSphereRadius(120.f);
	TriggerSphere->SetCollisionProfileName("Trigger");
}

void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();
	TriggerSphere->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::OnOverlap);
}

void ACheckpoint::OnOverlap(
	UPrimitiveComponent*,
	AActor* OtherActor,
	UPrimitiveComponent*,
	int32,
	bool,
	const FHitResult&
)
{
	ARunnerCharacter* Runner = Cast<ARunnerCharacter>(OtherActor);
	if (!Runner) return;

	// Set respawn transform on character
	Runner->SetActorTransform(GetActorTransform());

	// Debug
	GEngine->AddOnScreenDebugMessage(
		-1, 2.f, FColor::Green,
		TEXT("Checkpoint reached")
	);
}
