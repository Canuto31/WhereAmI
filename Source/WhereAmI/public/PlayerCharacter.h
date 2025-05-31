#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class UCameraComponent;
class USpringArmComponent;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);


UCLASS(config=Game)
class WHEREAMI_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

	/*MappingContext*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/*Actions*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* RunAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* RotateAction;

	/*Camera*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;

public:
	APlayerCharacter();

protected:
	virtual void BeginPlay() override;

	virtual void NotifyControllerChanged() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);
	void StopMove();
	void Run(const FInputActionValue& Value);
	void StopRun(const FInputActionValue& Value);
	void Rotate(const FInputActionValue& Value);

public:	
	virtual void Tick(float DeltaTime) override;

	/** Returns FollowCamera subobject **/
	//FORCEINLINE class UCameraComponent* GetCameraComponent() const { return FollowCamera; }
	/** Returns SpringArm subobject **/
	//FORCEINLINE class USpringArmComponent* GetSpringArm() const { return SpringArm; }

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bIsMovingForward;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bIsMovingBackward;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	FRotator FixedRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float RotationSpeed = 90.0f; 

};
