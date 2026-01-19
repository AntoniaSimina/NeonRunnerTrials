#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "RunnerSaveGame.generated.h"

UCLASS()
class NEONRUNNERTRIALS_API URunnerSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	URunnerSaveGame();

	// Best time in seconds (readable in Blueprint)
	UPROPERTY(BlueprintReadOnly, Category = "Save")
	float BestTime = 0.f;
};
