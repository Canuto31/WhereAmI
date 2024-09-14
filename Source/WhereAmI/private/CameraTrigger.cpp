// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraTrigger.h"
#include "CameraControllerActor.h"
#include "PlayerCharacter.h"

// Sets default values
ACameraTrigger::ACameraTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TriggerVolumen = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume"));
	RootComponent = TriggerVolumen;
	TriggerVolumen->OnComponentBeginOverlap.AddDynamic(this, &ACameraTrigger::OnOverlapBegin);

}

// Called when the game starts or when spawned
void ACameraTrigger::BeginPlay()
{
	Super::BeginPlay();

	// Ensure collision setup for TriggerVolumen, if necessary
	TriggerVolumen->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerVolumen->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	TriggerVolumen->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	TriggerVolumen->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	
}

void ACameraTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Ensure it's the player character
	if (OtherActor && OtherActor->IsA<APlayerCharacter>())
	{
		// Check if CameraController is valid before using it
		if (CameraController)
		{
			CameraController->TriggerCameraChange(CameraIndex);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("CameraController is not set!"));
		}
	}
}

