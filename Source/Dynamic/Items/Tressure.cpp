// Fill out your copyright notice in the Description page of Project Settings.


#include "Tressure.h"
#include "Characters/DynamicCharacter.h"

void ATressure::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	  if (ADynamicCharacter* DynamicCharacter = Cast<ADynamicCharacter>(OtherActor))
	  {
		  GEngine->AddOnScreenDebugMessage(4,5,FColor::Red,"Tressure");
	  	  Destroy();
	  }
	
}
