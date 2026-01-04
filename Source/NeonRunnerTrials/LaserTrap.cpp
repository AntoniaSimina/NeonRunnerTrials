#include "LaserTrap.h"

#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "RunnerCharacter.h"

ALaserTrap::ALaserTrap()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);

	LaserMesh = CreateDefaultSubobject<UStaticMeshComponent>("LaserMesh");
	LaserMesh->SetupAttachment(Root);
	LaserMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	DamageBox = CreateDefaultSubobject<UBoxComponent>("DamageBox");
	DamageBox->SetupAttachment(LaserMesh);
	DamageBox->SetCollisionProfileName("Trigger");
}

void ALaserTrap::BeginPlay()
{
	Super::BeginPlay();

	DamageBox->OnComponentBeginOverlap.AddDynamic(
		this, &ALaserTrap::OnDamageOverlap
	);
}

void ALaserTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Rotire laser
	AddActorLocalRotation(
		FRotator(0.f, RotationSpeed * DeltaTime, 0.f)
	);
}

void ALaserTrap::OnDamageOverlap(
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

	Runner->ApplyDamage(DamagePerSecond * GetWorld()->GetDeltaSeconds());
}
