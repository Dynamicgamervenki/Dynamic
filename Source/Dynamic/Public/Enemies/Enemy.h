// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/HitInterface.h"
#include "Enemy.generated.h"

UCLASS()
class DYNAMIC_API AEnemy : public ACharacter , public IHitInterface
{
	GENERATED_BODY()

public :
	AEnemy();
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
protected:

	virtual void BeginPlay() override;

	void PlayHitReactMontage(const FName& SectionName);
	void DirectionalHitReact(FVector ImpactPoint);

private:
	virtual void GetHit_Implementation(FVector ImpactPoint) override;

	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* HitReactMontage;
	
	UPROPERTY(EditAnywhere, Category = VisualEffects)
	UParticleSystem* HitParticles;

	

};
