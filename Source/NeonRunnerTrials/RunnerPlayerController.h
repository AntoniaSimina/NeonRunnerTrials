#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "RunnerPlayerController.generated.h"

UCLASS()
class NEONRUNNERTRIALS_API ARunnerPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// ===== Lifecycle =====
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	// ===== HUD =====
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> HUDWidgetClass;

	UPROPERTY()
	UUserWidget* HUDWidget = nullptr;

	// ===== END SCREEN =====
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> EndScreenClass;

	UPROPERTY()
	UUserWidget* EndScreenWidget = nullptr;

	UFUNCTION(BlueprintCallable)
	void ShowEndScreen();

private:
	// ===== PAUSE =====
	void TogglePauseGame();
};
