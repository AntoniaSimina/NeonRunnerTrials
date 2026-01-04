#include "RunnerCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/InputComponent.h"
#include "RunnerGameState.h"



ARunnerCharacter::ARunnerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// ===== Camera boom =====
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 300.f;
	SpringArm->bUsePawnControlRotation = true;

	// ===== Camera =====
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;

	// ===== Rotation settings =====
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 720.f, 0.f);
}



void ARunnerCharacter::BeginPlay()
{
	Super::BeginPlay();

	Stamina = MaxStamina;
	ApplyMoveSpeeds();

	ARunnerGameState* GS = GetWorld()->GetGameState<ARunnerGameState>();
	if (GS)
	{
		GS->StartRun();
	}

	CurrentHealth = MaxHealth;

}

void ARunnerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Auto-forward: ruleaz? permanent înainte (în direc?ia forward a actorului)
	if (bAutoRunEnabled)
	{
		AddMovementInput(GetActorForwardVector(), AutoRunStrength);
	}

	// Stamina logic
	TimeSinceLastSprintUse += DeltaSeconds;

	const bool bWantsSprint = bSprintHeld;
	const bool bIsActuallySprinting = bWantsSprint && CanSprint();

	if (bIsActuallySprinting)
	{
		// Drain stamina
		Stamina = FMath::Max(0.0f, Stamina - StaminaDrainPerSecond * DeltaSeconds);
		TimeSinceLastSprintUse = 0.0f;
	}
	else
	{
		// Regen after delay
		if (TimeSinceLastSprintUse >= StaminaRegenDelayAfterUse)
		{
			Stamina = FMath::Min(MaxStamina, Stamina + StaminaRegenPerSecond * DeltaSeconds);
		}
	}

	// Apply speed each tick (simplu ?i robust pentru început)
	ApplyMoveSpeeds();
}

void ARunnerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveRight", this, &ARunnerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ARunnerCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &ARunnerCharacter::LookUp);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ARunnerCharacter::SprintPressed);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ARunnerCharacter::SprintReleased);
}

void ARunnerCharacter::MoveRight(float Value)
{
	// Strafe pentru control simplu în auto-run
	if (FMath::Abs(Value) > KINDA_SMALL_NUMBER)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ARunnerCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void ARunnerCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void ARunnerCharacter::SprintPressed()
{
	bSprintHeld = true;
}

void ARunnerCharacter::SprintReleased()
{
	bSprintHeld = false;
}

bool ARunnerCharacter::CanSprint() const
{
	// Po?i ajusta pragul minim ca s? nu “tremure” între sprint/walk la 0 stamina
	return Stamina > 5.0f;
}

void ARunnerCharacter::ApplyMoveSpeeds()
{
	if (!GetCharacterMovement()) return;

	const bool bIsActuallySprinting = bSprintHeld && CanSprint();
	GetCharacterMovement()->MaxWalkSpeed = bIsActuallySprinting ? SprintSpeed : WalkSpeed;
}

void ARunnerCharacter::ApplyDamage(float DamageAmount)
{
	CurrentHealth -= DamageAmount;

	if (CurrentHealth <= 0.f)
	{
		Die();
	}
}

void ARunnerCharacter::Die()
{
	// Respawn simplu: ridic?m juc?torul
	CurrentHealth = MaxHealth;

	SetActorLocation(GetActorLocation() + FVector(0, 0, 300));

	GEngine->AddOnScreenDebugMessage(
		-1, 2.f, FColor::Red, TEXT("You Died")
	);
}

