#include "SpikeTrap.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h" // Necesar pentru ApplyDamage

ASpikeTrap::ASpikeTrap()
{
	PrimaryActorTick.bCanEverTick = true;

	// 1. Root
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	// 2. Mesh (Vizual)
	SpikeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpikeMesh"));
	SpikeMesh->SetupAttachment(Root);
	SpikeMesh->SetCollisionProfileName(TEXT("NoCollision")); // Mesh-ul nu blochează fizic

	// 3. Damage Box (Logic)
	DamageBox = CreateDefaultSubobject<UBoxComponent>(TEXT("DamageBox"));
	DamageBox->SetupAttachment(SpikeMesh);
	DamageBox->SetBoxExtent(FVector(32.f, 32.f, 32.f));
	DamageBox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	// NOTĂ: Am scos AddDynamic de aici pentru că uneori Blueprints nu se actualizează corect.
	// L-am mutat în BeginPlay (mai jos).
}

void ASpikeTrap::BeginPlay()
{
	Super::BeginPlay();

	// --- FIX CRITIC ---
	// Legăm funcția de overlap aici, când începe jocul. Este mult mai sigur.
	if (DamageBox)
	{
		DamageBox->OnComponentBeginOverlap.AddDynamic(this, &ASpikeTrap::OnOverlapBegin);
	}

	// Inițializări de poziție
	StartLocation = SpikeMesh->GetRelativeLocation();
	TargetLocation = StartLocation + FVector(0.f, 0.f, RaiseHeight);

	// Pornim timer-ul
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ASpikeTrap::RaiseSpikes, 2.0f, false);
}

void ASpikeTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (SpikeState == ESpikeState::MovingUp)
	{
		FVector CurrentLoc = SpikeMesh->GetRelativeLocation();
		FVector NewLoc = FMath::VInterpConstantTo(CurrentLoc, TargetLocation, DeltaTime, MoveSpeed * 100.f);
		SpikeMesh->SetRelativeLocation(NewLoc);

		if (NewLoc.Equals(TargetLocation, 1.0f))
		{
			SpikeState = ESpikeState::Raised;
			GetWorldTimerManager().SetTimer(TimerHandle, this, &ASpikeTrap::LowerSpikes, ActiveTime, false);
		}
	}
	else if (SpikeState == ESpikeState::MovingDown)
	{
		FVector CurrentLoc = SpikeMesh->GetRelativeLocation();
		FVector NewLoc = FMath::VInterpConstantTo(CurrentLoc, StartLocation, DeltaTime, MoveSpeed * 50.f);
		SpikeMesh->SetRelativeLocation(NewLoc);

		if (NewLoc.Equals(StartLocation, 1.0f))
		{
			SpikeState = ESpikeState::Lowered;
			GetWorldTimerManager().SetTimer(TimerHandle, this, &ASpikeTrap::RaiseSpikes, 2.0f, false);
		}
	}
}

void ASpikeTrap::RaiseSpikes()
{
	SpikeState = ESpikeState::MovingUp;
}

void ASpikeTrap::LowerSpikes()
{
	SpikeState = ESpikeState::MovingDown;
}

void ASpikeTrap::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Verificăm dacă nu ne lovim singuri
	if (OtherActor && (OtherActor != this))
	{
		// DEBUG 1: Mesaj VERDE - Confirmă că Unreal a detectat coliziunea
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Coliziune detectată cu: %s"), *OtherActor->GetName()));

		// Verificăm dacă țepușele sunt periculoase (se ridică sau sunt sus)
		bool bIsDangerous = (SpikeState == ESpikeState::MovingUp || SpikeState == ESpikeState::Raised);

		if (bIsDangerous)
		{
			// DEBUG 2: Mesaj ROȘU - Confirmă că încercăm să dăm damage
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Damage Aplicat!"));

			UGameplayStatics::ApplyDamage(
				OtherActor,
				DamageAmount,
				GetInstigatorController(),
				this,
				UDamageType::StaticClass()
			);
		}
	}
}