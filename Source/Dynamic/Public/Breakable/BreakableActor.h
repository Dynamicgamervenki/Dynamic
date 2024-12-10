// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/HitInterface.h"
#include "BreakableActor.generated.h"

UCLASS()
class DYNAMIC_API ABreakableActor : public AActor , public IHitInterface
{
	GENERATED_BODY()
	
public:	
	ABreakableActor();
	virtual void Tick(float DeltaTime) override;
	virtual void GetHit_Implementation(FVector ImpactPoint) override;
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	class UGeometryCollectionComponent* GeometryCollection;

	UPROPERTY(EditDefaultsOnly,Category = BreakableActors)
	TArray<TSubclassOf<class ATressure>> TressureClasses;

	UPROPERTY(BlueprintReadWrite,VisibleAnywhere);
	class UCapsuleComponent* Capsule;

};
