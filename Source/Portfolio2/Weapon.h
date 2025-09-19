// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Weapon.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO2_API AWeapon : public AItem
{
	GENERATED_BODY()


public:

	AWeapon();
	

	void Equip(class ANinja* Char, FName SocketName);
	virtual void BeginPlay() override;
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UFUNCTION()

	virtual void OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound")

	class USoundBase* EquipSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")

	class UBoxComponent* WeaponBox;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trace1")
	USceneComponent* StartTraceBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trace2")
	USceneComponent* EndTraceBox;

	
};
