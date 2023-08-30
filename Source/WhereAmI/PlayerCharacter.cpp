// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

// UAnimMontage* APlayerCharacter::WalkingAnimation = nullptr;

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bIsMovingForward = false;
	bIsMovingBackward = false;
	/*bIsRotatingRight = false;
	bIsRotatingLeft = false;
	bIsMoving = false;*/

	// if (WalkingAnimationAsset.Succeeded())
	// {
	// 	WalkingAnimation = WalkingAnimationAsset.Object;
	// }
	// else
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("Failed to load WalkingAnimation asset"));
	// }
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Add imput mapping context
	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
			PlayerController->GetLocalPlayer());
		if (subsystem)
		{
			subsystem->AddMappingContext(PlayerMappingContext, 0);
		}
	}
	/*int numero = 3;
	UE_LOG(LogTemp, Warning, TEXT("Hola mundo %d"), numero); //Print in console

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, TEXT("Esto es un mensaje")); //Print in the screen
	}*/
}

// UAnimMontage* WalkingAnimation = LoadObject<UAnimMontage>(nullptr, TEXT("AnimMontage'/Game/Content/Characters/Brian/Animations/walking.uasset"));

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	//Correct code to move
	const float CurrentValue = Value.Get<float>();
	if (Controller && CurrentValue != 0.f)
	{
		if (CurrentValue > 0.f)
		{
			bIsMovingForward = true;
			bIsMovingBackward = false;
		}
		else
		{
			bIsMovingBackward = true;
			bIsMovingForward = false;
		}
		FVector Forward = GetActorForwardVector();
		AddMovementInput(Forward, CurrentValue);
	}
	else
	{
		bIsMovingBackward = false;
		bIsMovingForward = false;
	}
	
	/*//Bool Example
	const bool CurrentValue = Value.Get<bool>();
	if (CurrentValue)
	{
		UE_LOG(LogTemp, Warning, TEXT("IA_Move Triggered"))
	}*/
}

void APlayerCharacter::Rotate(const FInputActionValue& Value)
{
	const float CurrentValue = Value.Get<float>();

	if (Controller && CurrentValue != 0.f)
	{
		float AdjustedRotationValue = CurrentValue * RotationSpeed;
		AddControllerYawInput(AdjustedRotationValue);
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC->IsInputKeyDown(EKeys::W))
	{
		bIsMovingForward = true;
	}
	else
	{
		bIsMoving = false;
		bIsMovingForward = false;
	}
	
	if (PC->IsInputKeyDown(EKeys::S))
	{
		bIsMovingBackward = true;
	}
	else
	{
		bIsMoving = false;
		bIsMovingBackward = false;
	}
	if (PC->IsInputKeyDown(EKeys::D))
	{
		bIsRotatingRight = true;
	}
	else
	{
		bIsMoving = false;
		bIsRotatingRight = false;
	}
	if (PC->IsInputKeyDown(EKeys::A))
	{
		bIsRotatingLeft = true;
	}
	else
	{
		bIsMoving = false;
		bIsRotatingLeft = false;
	}
	
	if (bIsMovingForward && !bIsMovingBackward)
	{
		FVector Location = GetActorLocation();
		Location += GetActorForwardVector() * speed * DeltaTime;
		SetActorLocation(Location);
		PlayAnimMontage(WalkingAnimation);
		bIsMoving = true;
	} else if (bIsMovingBackward && !bIsMovingForward)
	{
		FVector Location = GetActorLocation();
		Location += -GetActorForwardVector() * speed * DeltaTime;
		SetActorLocation(Location);
		PlayAnimMontage(WalkingAnimation);
		bIsMoving = true;
	}
	
	if (bIsRotatingRight && !bIsRotatingLeft)
	{
		FRotator NewRotation = GetActorRotation() + FRotator(0.0f, 90.0f * DeltaTime, 0.0f);
		SetActorRotation(NewRotation);
		PlayAnimMontage(WalkingAnimation);
		bIsMoving = true;
	} else if (bIsRotatingLeft && !bIsRotatingRight)
	{
		FRotator NewRotation = GetActorRotation() - FRotator(0.0f, 90.0f * DeltaTime, 0.0f);
		SetActorRotation(NewRotation);
		PlayAnimMontage(WalkingAnimation);
		bIsMoving = true;
	}*/
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Rotate);
	}
}
