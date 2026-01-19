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

	// ===== Health / Stamina API (pentru HUD + BP) =====
	UFUNCTION(BlueprintCallable, Category = "Runner|Health")
	float GetHealthPercent() const;

	UFUNCTION(BlueprintCallable, Category = "Runner|Health")
	float GetCurrentHealth() const { return CurrentHealth; }

	UFUNCTION(BlueprintCallable, Category = "Runner|Health")
	float GetMaxHealth() const { return MaxHealth; }

	UFUNCTION(BlueprintCallable, Category = "Runner|Stamina")
	float GetStaminaPercent() const;

	UFUNCTION(BlueprintCallable, Category = "Runner|Stamina")
	float GetStamina() const { return Stamina; }

	// --- AICI ERA PROBLEMA: Am adaugat functia care lipsea ---
	UFUNCTION(BlueprintCallable, Category = "Runner|Stamina")
	float GetMaxStamina() const { return MaxStamina; }
	// --------------------------------------------------------

	// IMPORTANT: asta trebuie chemat din capcane (BP_SpikeTrap etc.)
	UFUNCTION(BlueprintCallable, Category = "Runner|Health")
	void ApplyDamage(float DamageAmount);

protected:
	virtual void BeginPlay() override;

	// ===== Input =====
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);
	void SprintPressed();
	void SprintReleased();

	// ===== Sprint helpers =====
	bool CanSprint() const;
	void ApplyMoveSpeeds();

	// ===== Death =====
	void Die();

protected:
	// ===== Components =====
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Runner|Components")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Runner|Components")
	UCameraComponent* Camera;

	// ===== Auto-run =====
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Runner|Movement")
	bool bAutoRunEnabled = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Runner|Movement", meta = (ClampMin = "0.0"))
	float AutoRunStrength = 1.0f;

	// ===== Speeds =====
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Runner|Movement", meta = (ClampMin = "0.0"))
	float WalkSpeed = 600.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Runner|Movement", meta = (ClampMin = "0.0"))
	float SprintSpeed = 900.0f;

	// ===== Stamina =====
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Runner|Stamina", meta = (ClampMin = "0.0"))
	float MaxStamina = 100.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Runner|Stamina")
	float Stamina = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Runner|Stamina", meta = (ClampMin = "0.0"))
	float StaminaDrainPerSecond = 25.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Runner|Stamina", meta = (ClampMin = "0.0"))
	float StaminaRegenPerSecond = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Runner|Stamina", meta = (ClampMin = "0.0"))
	float StaminaRegenDelayAfterUse = 0.75f;

	float TimeSinceLastSprintUse = 0.0f;
	bool bSprintHeld = false;

	// ===== Health =====
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Runner|Health", meta = (ClampMin = "1.0"))
	float MaxHealth = 100.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Runner|Health")
	float CurrentHealth = 100.0f;
};