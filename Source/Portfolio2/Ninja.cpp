// Fill out your copyright notice in the Description page of Project Settings.


#include "Ninja.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Weapon.h"







// Sets default values
ANinja::ANinja()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 400.f;
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	

}

// Called when the game starts or when spawned
void ANinja::BeginPlay()
{
	Super::BeginPlay();
	


	
}

// Called every frame
void ANinja::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANinja::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ANinja::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ANinja::MoveRight);


	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ANinja::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ANinja::LookUp);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);
	
	PlayerInputComponent->BindAction(TEXT("Equip"), IE_Released, this, &ANinja::PickupEquipItem);
	PlayerInputComponent->BindAction(TEXT("Attack"), IE_Released, this, &ANinja::Attack);

}


void ANinja::MoveForward(float Value){


	if (Controller, Value != 0, ActionState == EActionState::EAS_Unoccupied)
	{


		const FRotator Rotation = GetControlRotation();

		const FRotator YawRotation(0, Rotation.Yaw, 0);
		

		FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(Forward, Value);



	}

}




void ANinja::MoveRight(float Value){
	if (Controller && Value != 0 && ActionState == EActionState::EAS_Unoccupied)
	{



		const FRotator Rotation = GetControlRotation();

		const FRotator YawRotation(0, Rotation.Yaw, 0);
		

		FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(Forward, Value);
	}
}



void ANinja::Turn(float Value){
	AddControllerYawInput(Value);
}


void ANinja::LookUp(float Value){
	AddControllerPitchInput(Value);
}



void ANinja::PickupEquipItem() {


	if (Weapon) {


		AWeapon* MyWeapon = Cast<AWeapon>(Weapon);


		MyWeapon->ItemState = EItemState::EIS_Equipped;

		MyWeapon->Equip(this, FName("RightHandSocket"));

		CharacterState = ECharacterState::ECS_EquippedOneHanded;

		EquipWeapon = MyWeapon;

		Weapon = nullptr;



		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("Weapon Equipped"));


	}

	else {


		if (CanDisarm()) {



			PlayEquipMontage(FName("unequip"));
			CharacterState = ECharacterState::ECS_Unequipped;
			//EquipWeapon = nullptr;
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("Weapon Unequipped"));




		}
		else if (CanArm()) {

			PlayEquipMontage(FName("equip"));
			CharacterState = ECharacterState::ECS_EquippedOneHanded;

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Weapon Equipped"));

		}






	}

}

void ANinja::SetEquippedWeapon(AItem* ItemToSet)

{
	Weapon = ItemToSet;
}



void ANinja::Attack() {

	if (ActionState == EActionState::EAS_Unoccupied && CharacterState == ECharacterState::ECS_EquippedOneHanded) {

		PlayAttackMontage();


		ActionState = EActionState::EAS_Attacking;


	}
}




void ANinja::PlayEquipMontage(FName SectionName) {
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && equipMontage) {
		AnimInstance->Montage_Play(equipMontage, 1.f);
		AnimInstance->Montage_JumpToSection(SectionName, equipMontage);



	}
}

void ANinja::PlayAttackMontage() {



	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

	if (CombatMontage && AnimInstance) {


		AnimInstance->Montage_Play(CombatMontage, 1.f);


		FName nameSection;
		int32 SectionNumber = FMath::RandRange(1, 2);

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



		AnimInstance->Montage_JumpToSection(nameSection, CombatMontage);







	}




}

		



void ANinja::AttackEnd() {

		ActionState = EActionState::EAS_Unoccupied;

}





bool ANinja::CanArm() {
	return ActionState == EActionState::EAS_Unoccupied && CharacterState == ECharacterState::ECS_Unequipped && EquipWeapon;
}


bool ANinja::CanDisarm() {
	return ActionState == EActionState::EAS_Unoccupied && CharacterState == ECharacterState::ECS_EquippedOneHanded;
}