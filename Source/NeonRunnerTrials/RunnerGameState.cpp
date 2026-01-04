#include "RunnerGameState.h"

ARunnerGameState::ARunnerGameState()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ARunnerGameState::BeginPlay()
{
	Super::BeginPlay();
	ResetRun();
}

void ARunnerGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (RunState == ERunState::Running)
	{
		CurrentRunTime += DeltaSeconds;
	}
}

void ARunnerGameState::StartRun()
{
	CurrentRunTime = 0.0f;
	RunState = ERunState::Running;
}

void ARunnerGameState::FinishRun()
{
	RunState = ERunState::Finished;
}

void ARunnerGameState::ResetRun()
{
	CurrentRunTime = 0.0f;
	RunState = ERunState::Waiting;
}
