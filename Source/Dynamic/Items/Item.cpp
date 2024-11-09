// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "Components/SphereComponent.h"

AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	RootComponent = StaticMesh;

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetSphereRadius(45.0f);
	Sphere->SetupAttachment(GetRootComponent());
}


void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void AItem::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
		//Overlap Begin functionality
		FString OtherActorName = OtherActor->GetClass()->GetName();

		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red,OtherActorName);
		
}

void AItem::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
		//Overlap End functionality
	FString OtherActorName = OtherActor->GetClass()->GetName();
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Blue,OtherActorName);
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

	RotateInLocalSpace(DeltaTime);	
}

