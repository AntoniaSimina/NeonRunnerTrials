#include "RunnerPlayerController.h"
#include "Blueprint/UserWidget.h"

void ARunnerPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// === HUD ===
	if (HUDWidgetClass)
	{
		HUDWidget = CreateWidget(this, HUDWidgetClass);
		if (HUDWidget)
		{
			HUDWidget->AddToViewport();
		}
	}
}

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

void ARunnerPlayerController::ShowEndScreen()
{
	UE_LOG(LogTemp, Warning, TEXT("ShowEndScreen CALLED"));

	// 1️⃣ Creează widget-ul o singură dată
	if (EndScreenClass && !EndScreenWidget)
	{
		EndScreenWidget = CreateWidget(this, EndScreenClass);
	}

	// 2️⃣ Afișează widget-ul
	if (EndScreenWidget)
	{
		EndScreenWidget->AddToViewport(10);
	}

	// 3️⃣ Oprește jocul
	SetPause(true);

	// 4️⃣ UI mode + mouse
	bShowMouseCursor = true;
	SetInputMode(FInputModeUIOnly());
}
