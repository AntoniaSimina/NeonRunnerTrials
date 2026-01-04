#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "RunnerGameState.generated.h"

UENUM(BlueprintType)
enum class ERunState : uint8
{
	Waiting,
	Running,
	Finished
};

UCLASS()
class NEONRUNNERTRIALS_API ARunnerGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ARunnerGameState();

	virtual void Tick(float DeltaSeconds) override;

	// ===== Timer control =====
	void StartRun();
	void FinishRun();
	void ResetRun();

	float GetRunTime() const { return CurrentRunTime; }
	ERunState GetRunState() const { return RunState; }

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Run")
		float CurrentRunTime = 0.0f;

	UPROPERTY(VisibleAnywhere, Category = "Run")
		ERunState RunState = ERunState::Waiting;
};
