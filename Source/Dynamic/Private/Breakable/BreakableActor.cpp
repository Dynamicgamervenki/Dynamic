// Fill out your copyright notice in the Description page of Project Settings.


#include "Breakable/BreakableActor.h"
#include "GeometryCollection/GeometryCollectionComponent.h"

// Sets default values
ABreakableActor::ABreakableActor()
{
	PrimaryActorTick.bCanEverTick = false;
	GeometryCollection = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("GemotryCollection"));
	RootComponent = GeometryCollection;
	GeometryCollection->SetGenerateOverlapEvents(true);
	GeometryCollection->SetCollisionObjectType(ECC_Destructible);
	GeometryCollection->SetCollisionResponseToChannel(ECC_Camera,ECR_Ignore);
}

void ABreakableActor::BeginPlay()
{
	Super::BeginPlay();

}

void ABreakableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABreakableActor::GetHit_Implementation(FVector ImpactPoint)
{
	
}

