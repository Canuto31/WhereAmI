// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraControllerActor.h"

#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ACameraControllerActor::ACameraControllerActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	Camera->SetupAttachment(SpringArm);
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACameraControllerActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACameraControllerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


