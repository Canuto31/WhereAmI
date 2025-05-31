// Fill out your copyright notice in the Description page of Project Settings.


#include "StaticCameraController.h"

#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AStaticCameraController::AStaticCameraController()
{
 	PrimaryActorTick.bCanEverTick = false;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	Camera->SetupAttachment(SpringArm);
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(RootComponent);

}

void AStaticCameraController::BeginPlay()
{
	Super::BeginPlay();
	
}

void AStaticCameraController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

