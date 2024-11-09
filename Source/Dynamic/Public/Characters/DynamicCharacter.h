// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DynamicCharacter.generated.h"

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
	UInputAction* IA_Equip;

	//Function CallBacks
	UFUNCTION()
	void Move(const FInputActionValue& Value);
	UFUNCTION()
	void Look(const FInputActionValue& Value);
	void Jump();
	
private :

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent *CameraView;
	
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* CameraBoom;


};
