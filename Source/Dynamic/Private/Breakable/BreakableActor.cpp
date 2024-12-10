// Fill out your copyright notice in the Description page of Project Settings.


#include "Breakable/BreakableActor.h"
#include "Components/CapsuleComponent.h"
#include "Dynamic/Items/Tressure.h"
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
	GeometryCollection->SetCollisionResponseToChannel(ECC_Pawn,ECR_Ignore);

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	Capsule->SetupAttachment(RootComponent);
	Capsule->SetCapsuleHalfHeight(90.0f);
	Capsule->SetCapsuleRadius(65.0f);
	Capsule->SetCollisionResponseToAllChannels(ECR_Ignore);
	Capsule->SetCollisionResponseToChannel(ECC_Pawn,ECR_Block);
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
	UWorld* world = GetWorld();
	if (world && !TressureClasses.IsEmpty())
	{
		FVector SpawnLocation = GetActorLocation();
		SpawnLocation.Z += 75.0f;

		int32 Selection = FMath::RandRange(0, TressureClasses.Num() - 1);
		
		world->SpawnActor<ATressure>(TressureClasses[Selection],SpawnLocation,GetActorRotation());
		Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

