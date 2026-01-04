#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RunnerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class NEONRUNNERTRIALS_API ARunnerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ARunnerCharacter();

	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void ApplyDamage(float DamageAmount);
	void Die();
	// Getters pentru HUD
	float GetMaxHealth() const { return MaxHealth; }
	float GetCurrentHealth() const { return CurrentHealth; }

	float GetMaxStamina() const { return MaxStamina; }
	float GetStamina() const { return Stamina; }


protected:
	virtual void BeginPlay() override;

private:
	// ===== Camera =====
	UPROPERTY(VisibleAnywhere, Category = "Camera")
		USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
		UCameraComponent* Camera;

	// ===== Auto-forward =====
	UPROPERTY(EditAnywhere, Category = "Runner|AutoRun")
		bool bAutoRunEnabled = true;

	UPROPERTY(EditAnywhere, Category = "Runner|AutoRun")
		float AutoRunStrength = 1.0f;

	// ===== Sprint & stamina =====
	UPROPERTY(EditAnywhere, Category = "Runner|Sprint")
		float WalkSpeed = 600.f;

	UPROPERTY(EditAnywhere, Category = "Runner|Sprint")
		float SprintSpeed = 900.f;

	UPROPERTY(EditAnywhere, Category = "Runner|Stamina")
		float MaxStamina = 100.f;

	UPROPERTY(EditAnywhere, Category = "Runner|Stamina")
		float StaminaDrainPerSecond = 25.f;

	UPROPERTY(EditAnywhere, Category = "Runner|Stamina")
		float StaminaRegenPerSecond = 18.f;

	UPROPERTY(EditAnywhere, Category = "Runner|Stamina")
		float StaminaRegenDelayAfterUse = 0.6f;

	// ===== Health =====
	UPROPERTY(EditAnywhere, Category = "Runner|Health")
		float MaxHealth = 100.f;

	UPROPERTY(VisibleAnywhere, Category = "Runner|Health")
		float CurrentHealth = 100.f;

	float Stamina = 100.f;
	float TimeSinceLastSprintUse = 0.f;
	bool bSprintHeld = false;

	// Input
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);
	void SprintPressed();
	void SprintReleased();

	// Helpers
	bool CanSprint() const;
	void ApplyMoveSpeeds();
};
