// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterType.h"
#include "Ninja.generated.h"








UCLASS()
class PORTFOLIO2_API ANinja : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANinja();

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	

	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ActionState")
	EActionState ActionState = EActionState::EAS_Unoccupied;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SpringArmN")
	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CameraN")
	class UCameraComponent* Camera;


	void MoveForward(float Value);

	void Turn(float Value);

	void LookUp(float Value);
	void MoveRight(float Value);
	void PickupEquipItem();
	void SetEquippedWeapon(class AItem* ItemToSet);
	
	
	void Attack();
   void PlayAttackMontage();

	UFUNCTION(BlueprintCallable)
	void AttackEnd();
	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ITemWeapon")
	class AItem* Weapon;


	


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	UAnimMontage* CombatMontage;

	

	

};
