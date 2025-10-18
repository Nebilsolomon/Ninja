// Fill out your copyright notice in the Description page of Project Settings.


#include "Treasure.h"
#include "Ninja.h"
#include "Kismet/GameplayStatics.h"

void ATreasure::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{


	if (OtherActor)
	{
		ANinja* Ninja = Cast<ANinja>(OtherActor);
		if (Ninja)
		{
		//	Ninja->IncreaseTreasure();
			Destroy();


			if (PickupSound)
			{
			UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation());

			}
		}
	}

}
