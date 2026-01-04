#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FallingPlatform.generated.h"

class UBoxComponent;

UCLASS()
class NEONRUNNERTRIALS_API AFallingPlatform : public AActor
{
	GENERATED_BODY()

public:
	AFallingPlatform();

protected:
	virtual void BeginPlay() override;

private:
	// Root
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;

	// Mesh
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* PlatformMesh;

	// Trigger
	UPROPERTY(VisibleAnywhere)
		UBoxComponent* TriggerBox;

	// Settings
	UPROPERTY(EditAnywhere, Category = "Falling")
		float DelayBeforeFall = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Falling")
		float RespawnDelay = 3.0f;

	FVector StartLocation;
	bool bHasFallen = false;

	FTimerHandle FallTimerHandle;
	FTimerHandle RespawnTimerHandle;

	// Functions
	UFUNCTION()
		void OnTriggerOverlap(
			UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult
		);

	void StartFalling();
	void Respawn();
};
