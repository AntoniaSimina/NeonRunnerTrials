#include "TimedLaserTrap.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"

ATimedLaserTrap::ATimedLaserTrap()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATimedLaserTrap::BeginPlay()
{
	Super::BeginPlay();

	SetLaserActive();
}

void ATimedLaserTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Rotim DOAR când e activ
	if (bIsActive)
	{
		AddActorLocalRotation(
			FRotator(0.f, RotationSpeed * DeltaTime, 0.f)
		);
	}
}

void ATimedLaserTrap::SetLaserActive()
{
	bIsActive = true;

	// Vizibil
	LaserMesh->SetVisibility(true);

	// Damage activ
	DamageBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	// Trecem la inactiv după timp
	GetWorldTimerManager().SetTimer(
		TimerHandle,
		this,
		&ATimedLaserTrap::SetLaserInactive,
		ActiveTime,
		false
	);
}

void ATimedLaserTrap::SetLaserInactive()
{
	bIsActive = false;

	// Invizibil
	LaserMesh->SetVisibility(false);

	// Damage OFF
	DamageBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Reactivare
	GetWorldTimerManager().SetTimer(
		TimerHandle,
		this,
		&ATimedLaserTrap::SetLaserActive,
		InactiveTime,
		false
	);
}
