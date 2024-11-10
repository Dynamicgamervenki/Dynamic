// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/CharacterType.h"
#include "Dynamic/Items/Item.h"
#include "GameFramework/Character.h"  
#include "DynamicCharacter.generated.h"

struct FInputActionValue;

UCLASS()
class DYNAMIC_API ADynamicCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	ADynamicCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="CharacterState")
	ECharacterState CharacterState = ECharacterState::ECS_unequipped;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Input")
	class UInputMappingContext* DynamicInputMappingContext;

	//InputActions
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Input")
	class UInputAction* IA_Move;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Input")
	UInputAction* IA_Look;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Input")
	UInputAction* IA_Jump;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Input")
	UInputAction* IA_PickUp;

	//Function CallBacks
	UFUNCTION()
	void Move(const FInputActionValue& Value);
	UFUNCTION()
	void Look(const FInputActionValue& Value);
	void Jump();
	void PickUp();

	bool CanArm();
	bool CanDisArm();

	void PlayArmWeaponMontage(FName SectionName);

	UPROPERTY(VisibleAnywhere,Category="Weapon")
	class AWeapon* EquippedWeapon;

	UFUNCTION(BlueprintCallable)
	void DisArm();
	UFUNCTION(BlueprintCallable)
	void Arm();

	UFUNCTION(BlueprintCallable)
	void FinishEquipping();
	
	
private :
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess=true))
	EActionState ActionState = EActionState::EAS_unocuupied;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent *CameraView;
	
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* CameraBoom;
	
	public:

	UPROPERTY(VisibleAnywhere,Category = "Overlap")
	AItem* OverlappingItem;
	FORCEINLINE void SetOverlappingItem(AItem* item) { this->OverlappingItem = item;}
	FORCEINLINE ECharacterState GetCharacterState() { return CharacterState; }

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animation Montage")
	class UAnimMontage* ArmWeaponMontage;
};
