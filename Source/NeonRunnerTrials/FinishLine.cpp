#include "FinishLine.h"

#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "RunnerGameState.h"
#include "RunnerCharacter.h"
#include "RunnerPlayerController.h"
#include "RunnerSaveGame.h"

AFinishLine::AFinishLine()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;

	Trigger = CreateDefaultSubobject<UBoxComponent>("Trigger");
	Trigger->SetupAttachment(Root);
	Trigger->SetBoxExtent(FVector(100.f, 200.f, 200.f));
	Trigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Trigger->SetCollisionResponseToAllChannels(ECR_Ignore);
	Trigger->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	Trigger->SetGenerateOverlapEvents(true);
}

void AFinishLine::BeginPlay()
{
	Super::BeginPlay();

	Trigger->OnComponentBeginOverlap.AddDynamic(
		this,
		&AFinishLine::OnTriggerBeginOverlap
	);
}

void AFinishLine::OnTriggerBeginOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	// Verificăm că este player-ul
	ARunnerCharacter* Runner = Cast<ARunnerCharacter>(OtherActor);
	if (!Runner) return;

	// === GAME STATE ===
	ARunnerGameState* GS = GetWorld()->GetGameState<ARunnerGameState>();
	if (!GS) return;

	// Oprim cursa și luăm timpul final
	GS->FinishRun();
	float CurrentTime = GS->GetRunTime();

	// === SAVE GAME ===
	URunnerSaveGame* SaveGameInstance = Cast<URunnerSaveGame>(
		UGameplayStatics::LoadGameFromSlot(TEXT("RunnerSave"), 0)
	);

	if (!SaveGameInstance)
	{
		SaveGameInstance = Cast<URunnerSaveGame>(
			UGameplayStatics::CreateSaveGameObject(URunnerSaveGame::StaticClass())
		);
	}

	if (SaveGameInstance)
	{
		if (SaveGameInstance->BestTime == 0.f || CurrentTime < SaveGameInstance->BestTime)
		{
			SaveGameInstance->BestTime = CurrentTime;
			UGameplayStatics::SaveGameToSlot(
				SaveGameInstance,
				TEXT("RunnerSave"),
				0
			);
		}
	}

	// === END SCREEN ===
	ARunnerPlayerController* PC = Cast<ARunnerPlayerController>(
		UGameplayStatics::GetPlayerController(GetWorld(), 0)
	);

	if (PC)
	{
		PC->ShowEndScreen();
	}
}
