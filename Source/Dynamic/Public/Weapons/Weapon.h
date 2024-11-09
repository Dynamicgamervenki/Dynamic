// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dynamic/Items/Item.h"
#include "Weapon.generated.h"

UCLASS()
class DYNAMIC_API AWeapon : public AItem
{
	GENERATED_BODY()
	protected:

	virtual void BeginPlay() override;
	
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

public :
	void Equip(USceneComponent *Parent ,FName InSocketName);
	
};
