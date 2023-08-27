// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bIsMovingForward = false;
	bIsMovingBackward = false;
	bIsRotatingRight = false;
	bIsRotatingLeft = false;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	int numero = 3;
	UE_LOG(LogTemp, Warning, TEXT("Hola mundo %d"), numero); //Print in console

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, TEXT("Esto es un mensaje")); //Print in the screen
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC->IsInputKeyDown(EKeys::W))
	{
		bIsMovingForward = true;
	}
	else
	{
		bIsMovingForward = false;
	}
	
	if (PC->IsInputKeyDown(EKeys::S))
	{
		bIsMovingBackward = true;
	}
	else
	{
		bIsMovingBackward = false;
	}
	if (PC->IsInputKeyDown(EKeys::D))
	{
		bIsRotatingRight = true;
	}
	else
	{
		bIsRotatingRight = false;
	}
	if (PC->IsInputKeyDown(EKeys::A))
	{
		bIsRotatingLeft = true;
	}
	else
	{
		bIsRotatingLeft = false;
	}
	
	if (bIsMovingForward && !bIsMovingBackward)
	{
		FVector Location = GetActorLocation();
		Location += GetActorForwardVector() * speed * DeltaTime;
		SetActorLocation(Location);
	} else if (bIsMovingBackward && !bIsMovingForward)
	{
		FVector Location = GetActorLocation();
		Location += -GetActorForwardVector() * speed * DeltaTime;
		SetActorLocation(Location);
	}

	if (bIsRotatingRight && !bIsRotatingLeft)
	{
		FRotator NewRotation = GetActorRotation() + FRotator(0.0f, 90.0f * DeltaTime, 0.0f);
		SetActorRotation(NewRotation);
	} else if (bIsRotatingLeft && !bIsRotatingRight)
	{
		FRotator NewRotation = GetActorRotation() - FRotator(0.0f, 90.0f * DeltaTime, 0.0f);
		SetActorRotation(NewRotation);
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
