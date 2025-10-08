// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"







// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);





	
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::GetHit(const FVector& ImpactPoint)
{

	

	//PlayEnemyMontage(FName("Front"));



	FVector forward = GetActorForwardVector(); 

	FVector ToHit = (ImpactPoint - GetActorLocation()).GetSafeNormal();

	double CosTheta =	FVector::DotProduct(forward, ToHit);

	double Theta = FMath::Acos(CosTheta);

	Theta = FMath::RadiansToDegrees(Theta);

	FVector CrossProduct = FVector::CrossProduct(forward, ToHit);

	if(CrossProduct.Z < 0) {
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




	if (HitSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,            // World context object
			HitSound,        // USoundBase* (your sound asset)
			ImpactPoint      // Location of the hit
		);


	}
		if (BloodNiagara)
		{


			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, "neden buraya girmiyor ki yaw ");

		
                if (BloodNiagara)
                {
                    FRotator NoRotation(0, 0, 0);
                    // Correct the class name to match the actual class in the Niagara library
                    UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), BloodNiagara, ImpactPoint, NoRotation);
                }
            



		}



		}








void AEnemy::PlayEnemyMontage(FName name)
{

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && EnemyMontage) {
		AnimInstance->Montage_Play(EnemyMontage, 1.f);
		AnimInstance->Montage_JumpToSection(name, EnemyMontage);
	}

}







