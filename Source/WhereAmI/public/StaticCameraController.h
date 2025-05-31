// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "StaticCameraController.generated.h"

class UBoxComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class WHEREAMI_API AStaticCameraController : public AActor
{
	GENERATED_BODY()
	
public:	
	AStaticCameraController();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* BoxCollision;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure)
	FORCEINLINE USpringArmComponent* GetSpringArm() const { return SpringArm; }
	UFUNCTION(BlueprintPure)
	FORCEINLINE UCameraComponent* GetCamera() const { return Camera; }
	UFUNCTION(BlueprintPure)
	FORCEINLINE UBoxComponent* GetBoxCollision() const { return BoxCollision; }

};
