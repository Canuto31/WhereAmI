// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorController.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class USceneComponent;

UCLASS()
class WHEREAMI_API ADoorController : public AActor
{
	GENERATED_BODY()

public:
	ADoorController();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category="Components")
	UStaticMeshComponent* DoorMesh;

	UPROPERTY(VisibleAnywhere, Category="Components")
	UBoxComponent* InteractionBox;

	UPROPERTY(VisibleAnywhere, Category="Door")
	USceneComponent* TeleportTarget;

	UPROPERTY(VisibleAnywhere, Category="Door")
	bool bIsLocked = false;

	UPROPERTY()
	AActor* OverlappingPlayer;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp,
	                  AActor* OtherActor,
	                  UPrimitiveComponent* OtherComp,
	                  int32 OtherBodyIndex);

	void HandleDoorTransition(AActor* PlayerActor);

	void TryInteract();
};
