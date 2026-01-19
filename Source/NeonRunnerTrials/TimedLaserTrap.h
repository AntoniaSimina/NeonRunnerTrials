#pragma once

#include "CoreMinimal.h"
#include "LaserTrap.h"
#include "TimedLaserTrap.generated.h"

UCLASS()
class NEONRUNNERTRIALS_API ATimedLaserTrap : public ALaserTrap
{
	GENERATED_BODY()

public:
	ATimedLaserTrap();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	// ===== Timing =====
	UPROPERTY(EditAnywhere, Category = "Timed Laser")
	float ActiveTime = 2.0f;

	UPROPERTY(EditAnywhere, Category = "Timed Laser")
	float InactiveTime = 2.0f;

	bool bIsActive = true;

	FTimerHandle TimerHandle;

	// State changes
	void SetLaserActive();
	void SetLaserInactive();
};
