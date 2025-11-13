// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"





enum class EItemState : uint8
{
	EIS_Hover		UMETA(DisplayName = "Hover"),
	EIS_Equipped	UMETA(DisplayName = "Equipped"),
	EIS_MAX			UMETA(DisplayName = "DefaultMAX")
};




UCLASS()
class PORTFOLIO2_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	EItemState ItemState = EItemState::EIS_Hover;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Niagara")

	class UNiagaraComponent* NiagaraComponent;	






	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "gok")
	float RunningTime;





	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "gok")
	float Amplitude = 0.25f;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "gok")
	float timeConstant = 5.f;


	UFUNCTION(BlueprintCallable)
	float TransformSin(float value);






 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	UStaticMeshComponent* ItemMesh; 

	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
    class USphereComponent* Sphere;


   UFUNCTION()
   
   virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
   
   UFUNCTION()
   virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


		








};
