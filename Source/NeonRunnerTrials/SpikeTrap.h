#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpikeTrap.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

// ===== State machine pentru spike-uri =====
UENUM()
enum class ESpikeState : uint8
{
	Lowered,
	MovingUp,
	Raised,
	MovingDown
};

UCLASS()
class NEONRUNNERTRIALS_API ASpikeTrap : public AActor
{
	GENERATED_BODY()

public:
	ASpikeTrap();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	// ===== Components =====
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* SpikeMesh;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* DamageBox;

	// ===== Settings =====
	UPROPERTY(EditAnywhere, Category = "Spike Trap")
	float RaiseHeight = 120.f;

	UPROPERTY(EditAnywhere, Category = "Spike Trap")
	float MoveSpeed = 8.f;

	UPROPERTY(EditAnywhere, Category = "Spike Trap")
	float ActiveTime = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Spike Trap")
	float DamageAmount = 25.0f; // Variabila nouă pentru damage

	// ===== State =====
	ESpikeState SpikeState = ESpikeState::Lowered;

	FVector StartLocation;
	FVector TargetLocation;

	FTimerHandle TimerHandle;

	// ===== Logic =====
	void RaiseSpikes();
	void LowerSpikes();

	// Funcția care detectează coliziunea
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};