#include "WhereAmI/public/PlayerCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "DoorController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

APlayerCharacter::APlayerCharacter()
{
 	PrimaryActorTick.bCanEverTick = true;
	
	bIsMovingForward = false;
	bIsMovingBackward = false;
	

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Values definition
	GetCharacterMovement()->MaxAcceleration = 500.0f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f;
	GetCharacterMovement()->BrakingDecelerationWalking =  2000.0f;

	// Create a SpringArm (Pulls in towards the player if there is a collision)
	//SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	//SpringArm->SetupAttachment(RootComponent);
	//SpringArm->TargetArmLength = 400.0f;

	// Create a FollowCamera
	//FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	//FollowCamera->SetupAttachment(SpringArm);

	//SpringArm->bUsePawnControlRotation = false;
	//FollowCamera->bUsePawnControlRotation = false;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = false;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerStart* PlayerStart = Cast<APlayerStart>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerStart::StaticClass())))
	{
		FixedRotation = PlayerStart->GetActorRotation();
		SetActorRotation(FixedRotation);
	}
	
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorRotation(FixedRotation);
}

void APlayerCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	if (APlayerController* PlayerCharacter = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerCharacter->GetLocalPlayer()))
		{
			subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Move
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &APlayerCharacter::StopMove);

		// Run
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Run);
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Completed, this, &APlayerCharacter::StopRun);

		// Rotate
		EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Rotate);

		// Interact
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Interact);

	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component!"), *GetNameSafe(this))
	}
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	UE_LOG(LogTemp, Warning, TEXT("MovementVector: %f"), MovementVector.Y);

	if (Controller != nullptr && MovementVector.Y != 0.0f)
	{
		if (MovementVector.Y > 0.0f)
		{
			bIsMovingForward = true;
			bIsMovingBackward = false;
		}
		else if (MovementVector.Y < 0.0f)
		{
			bIsMovingForward = false;
			bIsMovingBackward = true;
		}
		// Usa el vector adelante del actor (no del controlador) para evitar que rote al moverse
		const FVector ForwardDirection = GetActorForwardVector();

		// Movimiento solo hacia adelante o hacia atrás
		AddMovementInput(ForwardDirection, MovementVector.Y);
	}
}

void APlayerCharacter::StopMove()
{
	bIsMovingForward = false;
	bIsMovingBackward = false;
}

void APlayerCharacter::Run(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Shift is being held down."));
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
}

void APlayerCharacter::StopRun(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Shift has been released."));
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
}

void APlayerCharacter::Rotate(const FInputActionValue& Value)
{
	float RotationInput = Value.Get<float>();

	if (FMath::Abs(RotationInput) > KINDA_SMALL_NUMBER)
	{
		if (bIsMovingBackward)
		{
			RotationInput *= -1.0f;
		}
		
		FRotator CurrentRotation = GetActorRotation();

		float yawChangue = RotationInput * RotationSpeed *GetWorld()->GetDeltaSeconds();
		FRotator NewRotation = FRotator(0.0f, CurrentRotation.Yaw + yawChangue, 0.0f);

		SetActorRotation(NewRotation);
		FixedRotation = NewRotation;
	}
}

void APlayerCharacter::Interact(const FInputActionValue& Value)
{
	if (CurrentDoor)
	{
		CurrentDoor->TryInteract();
	}
}
