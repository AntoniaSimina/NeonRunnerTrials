#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RunnerHUDWidget.generated.h"

UCLASS()
class NEONRUNNERTRIALS_API URunnerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// === Bindings ===
	UFUNCTION(BlueprintCallable)
		float GetHealthPercent() const;

	UFUNCTION(BlueprintCallable)
		float GetStaminaPercent() const;

	UFUNCTION(BlueprintCallable)
		FText GetTimerText() const;
};
