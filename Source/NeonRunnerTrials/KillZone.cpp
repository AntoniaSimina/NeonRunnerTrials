#include "KillZone.h"

#include "Components/BoxComponent.h"
#include "RunnerCharacter.h"

AKillZone::AKillZone()
{
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);

	Box = CreateDefaultSubobject<UBoxComponent>("Box");
	Box->SetupAttachment(Root);
	Box->SetCollisionProfileName("Trigger");
}

void AKillZone::BeginPlay()
{
	Super::BeginPlay();
	Box->OnComponentBeginOverlap.AddDynamic(this, &AKillZone::OnOverlap);
}

void AKillZone::OnOverlap(
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

	// Respawn simplu: reset pozi?ia la ultimul checkpoint
	Runner->SetActorLocation(Runner->GetActorLocation() + FVector(0, 0, 300));

	GEngine->AddOnScreenDebugMessage(
		-1, 2.f, FColor::Red,
		TEXT("Respawn!")
	);
}
