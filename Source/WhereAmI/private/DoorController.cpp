

#include "DoorController.h"

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
	
}

void ADoorController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoorController::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bIsLocked && OtherActor && OtherActor->IsA<ACharacter>())
	{
		HandleDoorTransition(OtherActor);
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

