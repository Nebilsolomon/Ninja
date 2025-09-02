// Fill out your copyright notice in the Description page of Project Settings.


#include "Ninja.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"




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

}


void ANinja::MoveForward(float Value){


	if (Controller, Value != 0)
	{


		const FRotator Rotation = GetControlRotation();

		const FRotator YawRotation(0, Rotation.Yaw, 0);
		

		FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(Forward, Value);



	}

}




void ANinja::MoveRight(float Value){
	if (Controller && Value != 0)
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

