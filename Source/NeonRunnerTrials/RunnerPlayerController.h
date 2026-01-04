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
	virtual void SetupInputComponent() override;
	void BeginPlay();

	UPROPERTY(EditAnywhere, Category = "HUD")
		TSubclassOf<UUserWidget> HUDWidgetClass;

	UUserWidget* HUDWidget;


private:
	void TogglePauseGame();
};