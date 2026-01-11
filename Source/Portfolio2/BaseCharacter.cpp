




// Fill out your copyright notice in the Description page of Project Settings.



#include "BaseCharacter.h"
#include "AttributeComponent.h"
#include "Components/CapsuleComponent.h"




// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttributeHealth = CreateDefaultSubobject<UAttributeComponent>(TEXT("AttributeHealth"));
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);


}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void ABaseCharacter::Attack()
{

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Base Character Attack Function Called  yessss"));
}



void ABaseCharacter::PlayAttackMontage() {



}

void ABaseCharacter::Die() {

}





void ABaseCharacter::AttackEnd() {

 }

bool ABaseCharacter::CanAttack()
{
	return false;
}





void ABaseCharacter::HitReact(const FVector& ImpactPoint)
{

	FVector forward = GetActorForwardVector();

	FVector ToHit = (ImpactPoint - GetActorLocation()).GetSafeNormal();

	double CosTheta = FVector::DotProduct(forward, ToHit);

	double Theta = FMath::Acos(CosTheta);

	Theta = FMath::RadiansToDegrees(Theta);

	FVector CrossProduct = FVector::CrossProduct(forward, ToHit);

	if (CrossProduct.Z < 0) {
		Theta = -Theta;
	}


	if (Theta >= -45 && Theta < 45) {
		PlayEnemyMontage(FName("Front"));
	}
	else if (Theta >= 45 && Theta < 135) {
		PlayEnemyMontage(FName("Right"));
	}
	else if (Theta >= -135 && Theta < -45) {
		PlayEnemyMontage(FName("Left"));
	}
	else {
		PlayEnemyMontage(FName("Back"));
	}
}



void ABaseCharacter::PlayEnemyMontage(FName name)
{

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && EnemyMontage) {
		AnimInstance->Montage_Play(EnemyMontage, 1.f);
		AnimInstance->Montage_JumpToSection(name, EnemyMontage);
	}

}