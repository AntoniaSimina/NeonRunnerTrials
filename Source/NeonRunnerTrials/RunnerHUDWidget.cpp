#include "RunnerHUDWidget.h"

#include "RunnerCharacter.h"
#include "RunnerGameState.h"
#include "Kismet/GameplayStatics.h"

float URunnerHUDWidget::GetHealthPercent() const
{
	ARunnerCharacter* Runner =
		Cast<ARunnerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (!Runner) return 0.f;

	const float Max = Runner->GetMaxHealth();
	return (Max > 0.f) ? Runner->GetCurrentHealth() / Max : 0.f;
}

float URunnerHUDWidget::GetStaminaPercent() const
{
	ARunnerCharacter* Runner =
		Cast<ARunnerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (!Runner) return 0.f;

	const float Max = Runner->GetMaxStamina();
	return (Max > 0.f) ? Runner->GetStamina() / Max : 0.f;
}


FText URunnerHUDWidget::GetTimerText() const
{
	ARunnerGameState* GS = GetWorld()->GetGameState<ARunnerGameState>();
	if (!GS) return FText::FromString(TEXT("00:00"));

	float Time = GS->GetRunTime();

	int32 Minutes = FMath::FloorToInt(Time / 60.f);
	int32 Seconds = FMath::FloorToInt(FMath::Fmod(Time, 60.f));

	return FText::FromString(
		FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds)
	);
}
