

#include "DoorController.h"

#include "PlayerCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

ADoorController::ADoorController()
{
 	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(RootComponent);

	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	InteractionBox->SetupAttachment(RootComponent);
	InteractionBox->SetBoxExtent(FVector(100.f, 100.f, 200.f));
	InteractionBox->SetCollisionProfileName(TEXT("Trigger"));

	TeleportTarget = CreateDefaultSubobject<USceneComponent>(TEXT("TeleportTarget"));
	TeleportTarget->SetupAttachment(RootComponent);

}

void ADoorController::BeginPlay()
{
	Super::BeginPlay();

	InteractionBox->OnComponentBeginOverlap.AddDynamic(this, &ADoorController::OnOverlapBegin);
	InteractionBox->OnComponentEndOverlap.AddDynamic(this, &ADoorController::OnOverlapEnd);
	
}

void ADoorController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoorController::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor))
	{
		OverlappingPlayer = Player;
		Player->CurrentDoor = this;
	}
}

void ADoorController::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor))
	{
		if (Player->CurrentDoor == this)
		{
			Player->CurrentDoor = nullptr;
		}
		OverlappingPlayer = nullptr;
	}
}

void ADoorController::TryInteract()
{
	if (!bIsLocked && OverlappingPlayer)
	{
		HandleDoorTransition(OverlappingPlayer);
	}
}

void ADoorController::HandleDoorTransition(AActor* PlayerActor)
{
	if (TeleportTarget && PlayerActor)
	{
		FVector NewLocation = TeleportTarget->GetComponentLocation();
		FRotator NewRotation = TeleportTarget->GetComponentRotation();
		
		PlayerActor->SetActorLocationAndRotation(NewLocation, NewRotation);
	}
}

