#include "RunnerPlayerController.h"

void ARunnerPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	check(InputComponent);

	InputComponent->BindAction("Pause", IE_Pressed, this, &ARunnerPlayerController::TogglePauseGame);
}

void ARunnerPlayerController::TogglePauseGame()
{
	const bool bIsPausedNow = !IsPaused();
	SetPause(bIsPausedNow);

	bShowMouseCursor = bIsPausedNow;

	if (bIsPausedNow)
	{
		FInputModeUIOnly Mode;
		SetInputMode(Mode);
	}
	else
	{
		FInputModeGameOnly Mode;
		SetInputMode(Mode);
	}
}
void ARunnerPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (HUDWidgetClass)
	{
		HUDWidget = CreateWidget(this, HUDWidgetClass);
		if (HUDWidget)
		{
			HUDWidget->AddToViewport();
		}
	}
}
