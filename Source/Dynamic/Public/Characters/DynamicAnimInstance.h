// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "DynamicAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class DYNAMIC_API UDynamicAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadOnly)
	class ADynamicCharacter* DynamicCharacter;
	
	UPROPERTY(BlueprintReadOnly,Category="Movement")
	class UCharacterMovementComponent* MovementComponent;
	
	//functions
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeInitializeAnimation() override;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	float GroundSpeed;
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	bool IsFalling;
};
