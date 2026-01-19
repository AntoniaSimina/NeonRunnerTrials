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
	UFUNCTION(BlueprintCallable, Category = "Run")
	void StartRun();

	UFUNCTION(BlueprintCallable, Category = "Run")
	void FinishRun();

	UFUNCTION(BlueprintCallable, Category = "Run")
	void ResetRun();

	// ===== Getters (IMPORTANT pentru Best Time & UI) =====
	UFUNCTION(BlueprintCallable, Category = "Run")
	float GetRunTime() const;

	UFUNCTION(BlueprintCallable, Category = "Run")
	ERunState GetRunState() const;

protected:
	virtual void BeginPlay() override;

private:
	// ===== Runtime data =====
	UPROPERTY(VisibleAnywhere, Category = "Run")
	float CurrentRunTime = 0.0f;

	UPROPERTY(VisibleAnywhere, Category = "Run")
	ERunState RunState = ERunState::Waiting;
};
