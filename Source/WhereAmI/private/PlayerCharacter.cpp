// Fill out your copyright notice in the Description page of Project Settings.


#include "WhereAmI/public/PlayerCharacter.h"
#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Inventory/Item.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	bIsMovingForward = false;
	bIsMovingBackward = false;
	bIsShiftPressing = false;
	bIsRotating = false;
	MaxSpeed = 150;
	bIsPaused = false;

	MaxInventorySlots = 8;

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));

	InteractionCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("InteractionCapsule"));
	InteractionCapsule->SetupAttachment(RootComponent);

	InteractionCapsule->SetCapsuleHalfHeight(100.0f);
	InteractionCapsule->SetCapsuleRadius(50.0f);

	InteractionCapsule->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractionCapsule->SetCollisionObjectType(ECC_Pawn);
	InteractionCapsule->SetCollisionResponseToAllChannels(ECR_Ignore);
	InteractionCapsule->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	InteractionCapsule->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
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

			InteractionCapsule->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnInteractionCapsuleOverlap);
		}
	}
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	const float CurrentValue = Value.Get<float>();
	if (Controller && CurrentValue != 0.f)
	{
		if (CurrentValue > 0.f)
		{
			bIsMovingForward = true;
			bIsMovingBackward = false;
		}
		else if (CurrentValue < 0.f)
		{
			bIsMovingBackward = true;
			bIsMovingForward = false;
		}
		FVector Forward = GetActorForwardVector();
		AddMovementInput(Forward, CurrentValue);
	}
	UpdateMovementSpeed();
}

void APlayerCharacter::Rotate(const FInputActionValue& Value)
{
	const float CurrentValue = Value.Get<float>();

	if (Controller && CurrentValue != 0.f)
	{
		float AdjustedRotationValue = CurrentValue * RotationSpeed;
		if (bIsMovingBackward)
		{
			AdjustedRotationValue *= -1.0f;
		}
		AddControllerYawInput(AdjustedRotationValue);
		bIsRotating = true;
	}
}

void APlayerCharacter::ShiftPressing(const FInputActionValue& Value)
{
	bIsShiftPressing = Value.Get<bool>();
}

void APlayerCharacter::NotShiftPressing(const FInputActionValue& Value)
{
	bIsShiftPressing = false;
}

void APlayerCharacter::FinishRotate(const FInputActionValue& Value)
{
	bIsRotating = false;
}

void APlayerCharacter::UpdateMovementSpeed()
{
	if (bIsShiftPressing && (GetCharacterMovement()->MaxWalkSpeed != MaxSpeed * 2))
	{
		GetCharacterMovement()->MaxWalkSpeed = MaxSpeed * 2;
	}
	else if (!bIsShiftPressing && (GetCharacterMovement()->MaxWalkSpeed != MaxSpeed))
	{
		GetCharacterMovement()->MaxWalkSpeed -= 1;
	}
}

void APlayerCharacter::UpdateMovingVariables()
{
	bIsMovingForward = false;
	bIsMovingBackward = false;
}

void APlayerCharacter::TogglePause()
{
	bIsPaused = !bIsPaused;
	
	UGameplayStatics::SetGamePaused(GetWorld(), bIsPaused);

	UE_LOG(LogTemp, Warning, TEXT("is paused = %s"), bIsPaused ? TEXT("true") : TEXT("false"));
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateMovementSpeed();

	FVector CapsuleLocation = InteractionCapsule->GetComponentLocation();
	float CapsuleHalfHeight = InteractionCapsule->GetScaledCapsuleHalfHeight();
	float CapsuleRadius = InteractionCapsule->GetScaledCapsuleRadius();

	DrawDebugCapsule(GetWorld(), CapsuleLocation, CapsuleHalfHeight, CapsuleRadius, FQuat::Identity, FColor::Green, false, 0.1f, 0, 2.0f);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &APlayerCharacter::UpdateMovingVariables);
		EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Rotate);
		EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Completed, this, &APlayerCharacter::FinishRotate);
		EnhancedInputComponent->BindAction(ShiftPressingAction, ETriggerEvent::Triggered, this, &APlayerCharacter::ShiftPressing);
		EnhancedInputComponent->BindAction(ShiftPressingAction, ETriggerEvent::Completed, this, &APlayerCharacter::NotShiftPressing);

		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Triggered, this, &APlayerCharacter::TogglePause);

		EnhancedInputComponent->BindAction(PickUpAction, ETriggerEvent::Triggered, this, &APlayerCharacter::TryPickupItem);
	}
}

bool APlayerCharacter::AddItemToInventory(AItem* Item)
{
	if (!Item) return false;

	for (FInventoryItem& InvItem : Inventory)
	{
		if (InvItem.ItemReference->ItemName == Item->ItemName)
		{
			if (InvItem.Quantity < InvItem.ItemReference->MaxStack)
			{
				InvItem.Quantity += Item->Quantity;
				Item->Destroy();
				return true;
			}
		}
	}

	if (Inventory.Num() < MaxInventorySlots)
	{
		Inventory.Add(FInventoryItem{ Item, Item->Quantity });
		Item->Destroy();
		return true;
	}

	return false;
}

void APlayerCharacter::PickupItem(AItem* Item)
{
	if (Item && InventoryComponent)
	{
		if (InventoryComponent->AddItem(Item))
		{
			UE_LOG(LogTemp, Warning, TEXT("Picked up: %s"), *Item->ItemName.ToString());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Inventory is full!"));
		}
	}
}

void APlayerCharacter::TryPickupItem()
{
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	FVector CapsuleLocation = InteractionCapsule->GetComponentLocation();
	float CapsuleRadius = InteractionCapsule->GetScaledCapsuleRadius();
	float CapsuleHalfHeight = InteractionCapsule->GetScaledCapsuleHalfHeight();

	bool bHasHit = GetWorld()->OverlapMultiByChannel(
		OverlapResults,
		CapsuleLocation,
		FQuat::Identity,
		ECC_WorldDynamic,
		FCollisionShape::MakeCapsule(CapsuleRadius, CapsuleHalfHeight),
		QueryParams
	);

	if (bHasHit)
	{
		for (const FOverlapResult& Result : OverlapResults)
		{
			AItem* Item = Cast<AItem>(Result.GetActor());
			if (Item)
			{
				UE_LOG(LogTemp, Warning, TEXT("Recogiendo: %s"), *Item->GetName());
				PickupItem(Item);
				return;
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No hay objetos en el área de interacción."));
	}
}

void APlayerCharacter::OnInteractionCapsuleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AItem* Item = Cast<AItem>(OtherActor);
	if (Item)
	{
		UE_LOG(LogTemp, Warning, TEXT("Detectado: %s"), *Item->GetName());

		Item->Use(this);
	}
}
