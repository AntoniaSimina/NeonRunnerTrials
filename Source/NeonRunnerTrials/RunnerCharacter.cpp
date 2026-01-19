#include "RunnerCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h" // Necesar pentru Restart Level

// DACA AI CREAT CLASA RunnerGameState, DECOMENTEAZA LINIA DE MAI JOS:
// #include "RunnerGameState.h"

ARunnerCharacter::ARunnerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// ===== Camera boom =====
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 400.f; // Putin mai departe ca sa vedem obstacolele
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->SocketOffset = FVector(0, 0, 100); // Ridicam camera putin

	// ===== Camera =====
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
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

	// Init health/stamina
	CurrentHealth = MaxHealth;
	Stamina = MaxStamina;

	ApplyMoveSpeeds();

	// --- LOGICA DE GAMESTATE (Timer) ---
	// Daca ai creat clasa RunnerGameState, decomenteaza liniile de mai jos:
	/*
	if (ARunnerGameState* GS = GetWorld()->GetGameState<ARunnerGameState>())
	{
		GS->StartRun();
	}
	*/
}

void ARunnerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Auto-forward (doar daca suntem vii)
	if (bAutoRunEnabled && CurrentHealth > 0)
	{
		AddMovementInput(GetActorForwardVector(), AutoRunStrength);
	}

	// Stamina logic
	TimeSinceLastSprintUse += DeltaSeconds;

	const bool bIsActuallySprinting = bSprintHeld && CanSprint();

	if (bIsActuallySprinting)
	{
		Stamina = FMath::Max(0.0f, Stamina - StaminaDrainPerSecond * DeltaSeconds);
		TimeSinceLastSprintUse = 0.0f;
	}
	else
	{
		if (TimeSinceLastSprintUse >= StaminaRegenDelayAfterUse)
		{
			Stamina = FMath::Min(MaxStamina, Stamina + StaminaRegenPerSecond * DeltaSeconds);
		}
	}

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
	if (CurrentHealth <= 0) return; // Nu ne miscam daca suntem morti

	if (FMath::Abs(Value) > 0.1f)
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
	// Daca suntem deja morti sau damage e 0, ignoram
	if (CurrentHealth <= 0.0f || DamageAmount <= 0.f) return;

	CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.0f, MaxHealth);

	// Debug message pe ecran
	if (GEngine)
	{
		FString DebugMsg = FString::Printf(TEXT("HIT! Damage: %.0f | HP: %.0f"), DamageAmount, CurrentHealth);
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, DebugMsg);
	}

	if (CurrentHealth <= 0.0f)
	{
		Die();
	}
}

void ARunnerCharacter::Die()
{
	// 1. Oprim miscarea
	bAutoRunEnabled = false;
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->StopMovementImmediately();
		GetCharacterMovement()->DisableMovement();
	}

	// 2. Mesaj Game Over
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("GAME OVER! Restarting..."));
	}

	// 3. Restart Level dupa 1 secunda (folosim un Timer simplu sau apelam direct daca vrei instant)
	// Varianta simpla pentru proiect: Restart imediat
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

float ARunnerCharacter::GetHealthPercent() const
{
	return MaxHealth > 0.f ? (CurrentHealth / MaxHealth) : 0.f;
}

float ARunnerCharacter::GetStaminaPercent() const
{
	return MaxStamina > 0.f ? (Stamina / MaxStamina) : 0.f;
}