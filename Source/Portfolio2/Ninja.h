// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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
};
