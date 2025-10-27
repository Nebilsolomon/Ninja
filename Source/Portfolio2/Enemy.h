// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HitInterface.h"

#include "NiagaraSystem.h"
#include "Enemy.generated.h"



UCLASS()
class PORTFOLIO2_API AEnemy : public ACharacter, public IHitInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	virtual void GetHit_Implementation(const FVector& ImpactPoint) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;


	void PlayEnemyMontage(FName name);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage")
	UAnimMontage* EnemyMontage;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* HitSound;


	UPROPERTY(EditAnywhere , Category = "Niagara")
	class UNiagaraSystem* BloodNiagara;


	UPROPERTY(EditAnywhere, Category = "HealthAttribute")


	class UAttributeComponent* AttributeHealth;
	
	UPROPERTY(EditAnywhere, Category = "HealthBar")

	class UHealthBarComponent* HealthBar;

	



};
