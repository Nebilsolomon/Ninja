// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HitInterface.h"
#include "BaseCharacter.generated.h"

UCLASS()
class PORTFOLIO2_API ABaseCharacter : public ACharacter, public IHitInterface
{
	GENERATED_BODY()

private:



public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipped")
	class AWeapon* EquipWeapon;

	virtual void Attack();
	virtual void PlayAttackMontage();
	virtual bool CanAttack();
	virtual void HitReact(const FVector& ImpactPoint);
	virtual void PlayEnemyMontage(FName name);


	virtual void Die();

	UFUNCTION(BlueprintCallable)
	virtual void AttackEnd();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage")
	UAnimMontage* EnemyMontage;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage")
	UAnimMontage* DeathMontage;

	class UAttributeComponent* AttributeHealth;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* HitSound;


	UPROPERTY(EditAnywhere, Category = "Niagara")
	class UNiagaraSystem* BloodNiagara;





public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	

};
