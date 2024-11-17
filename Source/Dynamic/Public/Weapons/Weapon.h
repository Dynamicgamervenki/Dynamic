// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dynamic/Items/Item.h"
#include "Weapon.generated.h"

UCLASS()
class DYNAMIC_API AWeapon : public AItem
{
	GENERATED_BODY()
	public:
	AWeapon();
	
	protected:

	virtual void BeginPlay() override;
	
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	UFUNCTION()
    void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	class UBoxComponent* WeaponBox;

public :
	void Equip(USceneComponent *Parent ,FName InSocketName);

	UFUNCTION(BlueprintCallable)
	void AttachMeshToSocket(USceneComponent* Parent, FName InSocketName);

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	USceneComponent* BoxTraceStart;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	USceneComponent* BoxTraceEnd;

	TArray<AActor*>IgnoreActors;

	FORCEINLINE UBoxComponent* GetWeaponBox() const {return WeaponBox;}
	
};
