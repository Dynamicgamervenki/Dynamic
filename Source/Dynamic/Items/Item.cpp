// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "Characters/DynamicCharacter.h"
#include "Components/SphereComponent.h"

AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	RootComponent = ItemMesh;

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetSphereRadius(45.0f);
	Sphere->SetupAttachment(GetRootComponent());
}


void AItem::BeginPlay()
{
	Super::BeginPlay();
	Sphere->OnComponentBeginOverlap.AddDynamic(this,&AItem::OnSphereOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this,&AItem::OnSphereEndOverlap);
	
}

void AItem::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
		if(ADynamicCharacter* DynamicCharacter = Cast<ADynamicCharacter>(OtherActor))
		{
			DynamicCharacter->SetOverlappingItem(this);
		}
}

void AItem::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(ADynamicCharacter* DynamicCharacter = Cast<ADynamicCharacter>(OtherActor))
	{
		DynamicCharacter->SetOverlappingItem(nullptr);
	}
}

void AItem::RotateInLocalSpace(float DeltaTime)
{
	RunningTime += DeltaTime;

	float DeltaZ = Amplitude * FMath::Sin(RunningTime * TimeConstant);

	AddActorWorldOffset(FVector(0.f, 0.f, DeltaZ));
}


void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//RotateInLocalSpace(DeltaTime);	
}

