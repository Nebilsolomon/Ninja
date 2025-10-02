// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"



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


	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ohh fuck i got it!"));


    DrawDebugSphere(
      GetWorld(),       // World
        ImpactPoint,      // Center of the sphere
        200,            // Radius
        12,               // Segments
        FColor::Red,      // Color
        false,            // Persistent (disappears)
        2.0f,             // LifeTime in seconds
        0,                // DepthPriority
        2.0f              // Thickness
    );

	PlayEnemyMontage();
	

}

void AEnemy::PlayEnemyMontage()
{

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && EnemyMontage) {
		AnimInstance->Montage_Play(EnemyMontage, 1.f);
	}

}







