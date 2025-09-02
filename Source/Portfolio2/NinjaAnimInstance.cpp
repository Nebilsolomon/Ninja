// Fill out your copyright notice in the Description page of Project Settings.


#include "NinjaAnimInstance.h"
#include "Ninja.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"



void UNinjaAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	// Add your custom animation initialization logic here

	Ninja = Cast<ANinja>(TryGetPawnOwner());
	if (Ninja)
	{
		Movement = Ninja->GetCharacterMovement();
	}

}

void UNinjaAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	// Add your custom animation update logic here

	if (Movement)
	{
		//Speed = Movement->Velocity.Size();


		Speed = UKismetMathLibrary::VSizeXY(Movement->Velocity);

		bIsInAir = Movement->IsFalling();	



	}
}



