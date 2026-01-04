#include "RunnerGameMode.h"

#include "RunnerPlayerController.h"
#include "RunnerCharacter.h"
#include "RunnerGameState.h"

ARunnerGameMode::ARunnerGameMode()
{
	DefaultPawnClass = ARunnerCharacter::StaticClass();
	PlayerControllerClass = ARunnerPlayerController::StaticClass();
	GameStateClass = ARunnerGameState::StaticClass();
}