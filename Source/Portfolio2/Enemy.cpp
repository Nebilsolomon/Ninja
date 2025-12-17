// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/PawnSensingComponent.h"

////////////////////////
#include "AIController.h"
#include "NavigationSystem.h"
#include "Navigation/PathFollowingComponent.h"
#include "Weapon.h"





#include "AttributeComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "HealthBarComponent.h"




// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);




	HealthBar = CreateDefaultSubobject<UHealthBarComponent>(TEXT("HealthBar"));
	HealthBar->SetupAttachment(GetRootComponent());

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;


	
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	

	Super::BeginPlay();

	
	HealthBar->SetVisibility(false);


	EnemyController = Cast<AAIController>(GetController());

	
	MoveToTarget(PatrolActor);
	
	//GetWorldTimerManager().SetTimer(PatrolTimer, this, &AEnemy::PatrolTimerFinished, 18);
		PawnSensingComp->OnSeePawn.AddDynamic(this, &AEnemy::OnPawnSeen);

		UWorld* World = GetWorld();
		if (World) {

			AWeapon* SpawnedWeapon = World->SpawnActor<AWeapon>(WeaponClass);
			if (SpawnedWeapon) {
				SpawnedWeapon->Equip(this, FName("RightHandSocket"));
			}

		}

	}
	
	
	



// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



	if (EnemyState > EEnemyState::EES_Patrolling)
	{



		if (CombatActor)
		{



			CheckCombatTarget();
		}
	}
		else {


	    CheckPatrolTarget();
		
	}
	
}



void AEnemy::CheckPatrolTarget()
{
	if (PatrolActor && EnemyController)
	{

		if (InTheRange(PatrolActor, PatrolRadius)) {

			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Patrol Target Reached , Moving to New Patrol Point"));

			int32 PatrolTarget = PatrolPoints.Num();

			if (PatrolTarget > 0)
			{
				int32 RandomIndex = FMath::RandRange(0, PatrolTarget - 1);

				AActor* NewPatrolPoint = PatrolPoints[RandomIndex];


				PatrolActor = NewPatrolPoint;
				FAIMoveRequest MoveRequest;
				MoveRequest.SetGoalActor(PatrolActor);
				MoveRequest.SetAcceptanceRadius(5.f);
				//GetWorldTimerManager().SetTimer(PatrolTimer, this, &AEnemy::StartPatrolTimer, 10);

				EnemyController->MoveTo(MoveRequest);



			}

		}
	}
}




// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::GetHit_Implementation(const FVector& ImpactPoint)
{

	if (HealthBar)
	{
	HealthBar->SetVisibility(true);

	}

	if (AttributeHealth->IsAlive())
	{
	HitReact(ImpactPoint);
	}
	else {

		Die();

	}

	//PlayEnemyMontage(FName("Front"));







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



float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{


	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, FString::Printf(TEXT("Enemy took damage: %f"), DamageAmount));


	if (AttributeHealth)
	{
		AttributeHealth->ReceiveDamage(DamageAmount);
	}


	if (HealthBar)
	{
		HealthBar->SetHealthPercent(AttributeHealth->GetHealthPercent());


	}


	CombatActor = EventInstigator->GetPawn();
	EnemyState = EEnemyState::EES_Chasing;
	MoveToTarget(CombatActor);

	return DamageAmount;

}







void AEnemy::Die()
{


	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

	FName name = FName();
	int randomInt = FMath::RandRange(1, 3);

	switch (randomInt)
	{
		case 1:
		name = FName("Death1");
		DeathPose = EDeathPose::EDP_Death1;

		break;
		case 2:
			name = FName("Death2");
			DeathPose = EDeathPose::EDP_Death2;

			break;


		case 3:
			name = FName("Death3");
			DeathPose = EDeathPose::EDP_Death3;
			break;

	default:
		name = FName("Death1");
		break;
	}

	if (AnimInstance && DeathMontage) {
		AnimInstance->Montage_Play(DeathMontage, 1.f);
		AnimInstance->Montage_JumpToSection(name, DeathMontage);
	
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, TEXT("Enemy Died"));

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetLifeSpan(5.f);
}

bool AEnemy::InTheRange(AActor* Target, double Radius)
{

	double Distance = (Target->GetActorLocation() - GetActorLocation()).Size();


	return Distance <= Radius;
}

void AEnemy::StartPatrolTimer()
{
	MoveToTarget(PatrolActor);
}

void AEnemy::MoveToTarget(AActor* Target)
{


	if (Target == nullptr || EnemyController == nullptr) return; 
	
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("AI Controller found and moving to Patrol Actor"));
	FAIMoveRequest MoveRequest;
	MoveRequest.SetGoalActor(Target);
	MoveRequest.SetAcceptanceRadius(70);
	EnemyController->MoveTo(MoveRequest);

}

void AEnemy::OnPawnSeen(APawn* SeenPawn)
{


	if (SeenPawn->ActorHasTag("NinjaTag"))
	{

		if (EnemyState == EEnemyState::EES_Chasing) return; 
		
	    //GetWorldTimerManager().ClearTimer(PatrolTimer);
		GetCharacterMovement()->MaxWalkSpeed = 300;

		CombatActor = SeenPawn;

		if (EnemyState != EEnemyState::EES_Attacking )
		{

	    EnemyState = EEnemyState::EES_Chasing;
		
		MoveToTarget(CombatActor);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("nebil"));

		}


	}
}







void AEnemy::CheckCombatTarget()
{
	// 1️⃣ Inside combat radius
	if (InTheRange(CombatActor, CombatRadius))
	{
		// 2️⃣ Inside attack radius
		if (InTheRange(CombatActor, AttackRadius))
		{
			if (EnemyState != EEnemyState::EES_Attacking  && EnemyState != EEnemyState::EES_Engaged)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Silver, TEXT("Attacking Target"));
				EnemyState = EEnemyState::EES_Attacking;
				StartTimerAttack();
			}
		}
		// 3️⃣ Between attack and combat radius (so chasing)
		else if (EnemyState != EEnemyState::EES_Chasing)
		{
			EnemyState = EEnemyState::EES_Chasing;
			GetCharacterMovement()->MaxWalkSpeed = 300;
			MoveToTarget(CombatActor);
			GetWorldTimerManager().ClearTimer(AttackTimer);

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, TEXT("Chasing Target"));

		}
	}
	// 4️⃣ Outside combat radius
	else
	{
		CombatActor = nullptr;
		HealthBar->SetVisibility(false);
		EnemyState = EEnemyState::EES_Patrolling;
		GetCharacterMovement()->MaxWalkSpeed = 150;
		MoveToTarget(PatrolActor);
		GetWorldTimerManager().ClearTimer(AttackTimer);

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("Lost Sight of Target, Returning to Patrol"));

	}
}

void AEnemy::Attack()
{
	EnemyState = EEnemyState::EES_Engaged;


	//EnemyState = EEnemyState::EES_Engaged;


	Super::Attack();

      PlayAttackMontage();
	  

		



		//PlayAttackMontage();
	
}

void AEnemy::PlayAttackMontage()
{

	Super::PlayAttackMontage();
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && AttackMontage) {
		AnimInstance->Montage_Play(AttackMontage, 1.f);
		FName nameSection;
		int32 SectionNumber = FMath::RandRange(1, 1);
		switch (SectionNumber) {
		case 1:
			nameSection = FName("Attack1");
			break;
		case 2:
			nameSection = FName("Attack2");
			break;
		default:
			break;
		}
		AnimInstance->Montage_JumpToSection(FName("Attack2"), AttackMontage);

	}
}



void AEnemy::StartTimerAttack()
{
	EnemyState = EEnemyState::EES_Attacking;
	const float AttackTime = FMath::RandRange(Attackmin, AttackMax);
	//GetWorldTimerManager().SetTimer(AttackTimer,this,&AEnemy::Attack,AttackTime,false);


	GetWorldTimerManager().SetTimer(AttackTimer, this, &AEnemy::Attack, AttackTime, false);



}





void AEnemy::AttackEnd()
{
	EnemyState = EEnemyState::EES_NoState;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Attack Ended"));

	///CheckCombatTarget();


}








