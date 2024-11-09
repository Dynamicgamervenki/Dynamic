// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/DynamicAnimInstance.h"
#include "Characters/DynamicCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


void UDynamicAnimInstance::NativeInitializeAnimation()
{
	Super::NativeBeginPlay();

	DynamicCharacter = Cast<ADynamicCharacter>(TryGetPawnOwner());
	if(DynamicCharacter)
	{
		MovementComponent = DynamicCharacter->GetCharacterMovement();
	}
}

void UDynamicAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if(DynamicCharacter)
	{
		GroundSpeed = DynamicCharacter->GetVelocity().Size2D();
		IsFalling = MovementComponent->IsFalling();
	}
	
}
