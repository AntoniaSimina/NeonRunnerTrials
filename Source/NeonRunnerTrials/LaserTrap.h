#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LaserTrap.generated.h"

class UBoxComponent;

UCLASS()
class NEONRUNNERTRIALS_API ALaserTrap : public AActor
{
	GENERATED_BODY()

public:
	ALaserTrap();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* LaserMesh;

	UPROPERTY(VisibleAnywhere)
		UBoxComponent* DamageBox;

	// ===== Laser Settings =====
	UPROPERTY(EditAnywhere, Category = "Laser")
		float RotationSpeed = 90.f;

	UPROPERTY(EditAnywhere, Category = "Laser")
		float DamagePerSecond = 25.f;

	UFUNCTION()
		void OnDamageOverlap(
			UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult
		);
};
