// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class DYNAMIC_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AItem();
	virtual void Tick(float DeltaTime) override;
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	class USphereComponent* Sphere;

	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
private :	

	void RotateInLocalSpace(float DeltaTime);
	
	float RunningTime;
	UPROPERTY(EditInstanceOnly,Category="Rotation")
	float Amplitude = 1.0f;
	UPROPERTY(EditInstanceOnly,Category="Rotation")
	float TimeConstant = 5.f;

};
