#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class NEONRUNNERTRIALS_API AMovingPlatform : public AActor
{
	GENERATED_BODY()

public:
	AMovingPlatform();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	// Root
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;

	// Platform mesh
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* PlatformMesh;

	// === Movement settings ===
	UPROPERTY(EditAnywhere, Category = "Movement")
		FVector MoveOffset = FVector(300.f, 0.f, 0.f);

	UPROPERTY(EditAnywhere, Category = "Movement")
		float MoveSpeed = 150.f;

	FVector StartLocation;
	FVector TargetLocation;

	bool bMovingToTarget = true;
};
