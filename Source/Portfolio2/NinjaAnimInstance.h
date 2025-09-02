// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "NinjaAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO2_API UNinjaAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeInitializeAnimation() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NSG")

	class ANinja* Ninja;

	UPROPERTY(BlueprintReadWrite, Category = "NinjaAnim")

	float Speed;

	UPROPERTY(BlueprintReadWrite, Category = "NinjaAnim")

	class UCharacterMovementComponent* Movement;


	UPROPERTY(BlueprintReadWrite, Category = "NinjaAnim")

	bool bIsInAir;

	
};
