// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class WHEREAMI_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void moveForward(float value);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	UInputMappingContext* PlayerMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	UInputAction* MoveAction;

	void Move(const FInputActionValue& value);

	// UPROPERTY(EditAnywhere, Category = "MoveActor")
	// float speed;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
// private:
// 	bool bIsMovingForward;
// 	bool bIsMovingBackward;
// 	bool bIsRotatingRight;
// 	bool bIsRotatingLeft;

// public:
// 	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="movement")
// 	bool bIsMoving;
};
