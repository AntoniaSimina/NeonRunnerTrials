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

	// Crește timpul DOAR când alergăm
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
	// Oprim timerul
	if (RunState == ERunState::Running)
	{
		RunState = ERunState::Finished;
	}
}

void ARunnerGameState::ResetRun()
{
	CurrentRunTime = 0.0f;
	RunState = ERunState::Waiting;
}

float ARunnerGameState::GetRunTime() const
{
	return CurrentRunTime;
}

ERunState ARunnerGameState::GetRunState() const
{
	return RunState;
}
