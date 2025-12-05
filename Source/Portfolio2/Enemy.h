// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "CharacterType.h"
#include "NiagaraSystem.h"
#include "Enemy.generated.h"






UCLASS()
class PORTFOLIO2_API AEnemy : public ABaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	EEnemyState EnemyState = EEnemyState::EES_Patrolling;

	// Called every frame
	virtual void Tick(float DeltaTime) override;




	void CheckPatrolTarget();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	virtual void GetHit_Implementation(const FVector& ImpactPoint) override;


	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;


	
	
	UPROPERTY(EditAnywhere, Category = "HealthBar")

	class UHealthBarComponent* HealthBar;

	void Die() override;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DeathPose")
	EDeathPose DeathPose = EDeathPose::EDP_Alive;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
	AActor* CombatActor;


	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Patrol")
	AActor* PatrolActor;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Patrol")

	TArray<AActor*> PatrolPoints;


	UPROPERTY()
   class AAIController* EnemyController;
	
	
   bool InTheRange(AActor* Target, double Radius);


   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol")
   double PatrolRadius = 100;




   FTimerHandle PatrolTimer;
   void PatrolTimerFinished();


   void MoveToTarget(AActor* Target);


   UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
   class UPawnSensingComponent* PawnSensingComp;
   UFUNCTION()
   void OnPawnSeen(APawn* SeenPawn);



   UPROPERTY(EditAnywhere)
   double CombatRadius = 500; 
	// double CombatRadius = 1000;

   UPROPERTY(EditAnywhere)
   double AttackRadius = 150; 

   void CheckCombatTarget();


   UPROPERTY(EditAnywhere, Category = "WeaponX")
   TSubclassOf<class AWeapon> WeaponClass;

    void Attack() override;

	void PlayAttackMontage() override;


	/*
	
	Combat
	*/

	void StartTimerAttack();
	FTimerHandle AttackTimer; 

	UPROPERTY(EditAnywhere, Category = "Combat")
	float Attackmin = 0.5; 
	
	UPROPERTY(EditAnywhere, Category = "Combat")
	float AttackMax = 1; 

};

