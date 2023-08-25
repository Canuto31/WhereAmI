// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraControllerActor.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ACameraControllerActor::ACameraControllerActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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

	const float TimeBetweenCameraChanges = 2.0f;
	const float SmoothBlendTime = 0.75f;

	TimeToNextCameraChange -= DeltaTime;

	if (TimeToNextCameraChange <= 0.0f)
	{
		TimeToNextCameraChange += TimeBetweenCameraChanges;

		APlayerController* OurPlayer = UGameplayStatics::GetPlayerController(this, 0);

		if (OurPlayer)
		{
			if (Cameras[1] && (OurPlayer->GetViewTarget() == Cameras[0]))
			{
				OurPlayer->SetViewTargetWithBlend(Cameras[1], SmoothBlendTime);
			}
			else if (Cameras[0])
			{
				OurPlayer->SetViewTarget(Cameras[0]);
			}
		}
	}
}
