// Fill out your copyright notice in the Description page of Project Settings.



#include "Weapon.h"
#include "Ninja.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Enemy.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"

#include "HitInterface.h"


#include "GeometryCollection/GeometryCollectionComponent.h"

#include "NiagaraComponent.h"


AWeapon::AWeapon() {












WeaponBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponBox"));
	//WeaponBox->SetupAttachment(ItemMesh);

	WeaponBox->SetupAttachment(ItemMesh, TEXT("SwordSocket"));

	
	
/*
WeaponBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	WeaponBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	

	*/
	
	WeaponBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	WeaponBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	WeaponBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);






	

	//WeaponBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//WeaponBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	//WeaponBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);


	StartTraceBox = CreateDefaultSubobject<USceneComponent>(TEXT("StartTraceBox"));
	StartTraceBox->SetupAttachment(GetRootComponent());
	EndTraceBox = CreateDefaultSubobject<USceneComponent>(TEXT("EndTraceBox"));
	EndTraceBox->SetupAttachment(GetRootComponent());





}



void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	WeaponBox->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnWeaponBoxOverlap);

}


void AWeapon::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){

	Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);




}



void AWeapon::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex){

	Super::OnOverlapEnd(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);





}	







void AWeapon::OnWeaponBoxOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {





	// Perform box trace for precise hit detection
	const FVector Start = StartTraceBox->GetComponentLocation();
	const FVector End = EndTraceBox->GetComponentLocation();

	// Debug visualizations
	//DrawDebugLine(GetWorld(), Start, End, FColor::Blue, false, 2.f, 0, 2.f);
	FVector TraceBoxSize(10, 10, 10); // Increased size
	/*DrawDebugBox(GetWorld(), Start, TraceBoxSize, FColor::Red, false, 2.f);
	DrawDebugBox(GetWorld(), End, TraceBoxSize, FColor::Green, false, 2.f);*/
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("Start: %s, End: %s"), *Start.ToString(), *End.ToString()));

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	FHitResult BoxHit;

	UKismetSystemLibrary::BoxTraceSingle(
		this,
		Start,
		End,
		TraceBoxSize,
		StartTraceBox->GetComponentRotation(),
		UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_WorldDynamic),
		false,
		ActorsToIgnore,
		EDrawDebugTrace::None,
		BoxHit,
		true
	);

	if (BoxHit.GetActor())
	{

		IHitInterface* HitInterface = Cast<IHitInterface>(BoxHit.GetActor());

		if (HitInterface)
		{
		//	HitInterface->GetHit(BoxHit.ImpactPoint);

			HitInterface->Execute_GetHit(BoxHit.GetActor(), BoxHit.ImpactPoint);

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Hit an actor via trace"));

		}

		CreateField(BoxHit.ImpactPoint);

	}


	

	/*
	
	AActor* HitActor = BoxHit.GetActor();
	if (HitActor != nullptr) {


		CreateField(BoxHit.ImpactPoint);

		AEnemy* Enemy = Cast<AEnemy>(HitActor);


		if (Enemy) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Hit an enemy via trace  nebil"));
			Enemy->GetHit(BoxHit.ImpactPoint);



		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Hit actor is not an enemy"));
		}
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No actor hit by trace"));
	}
	CreateField(BoxHit.ImpactPoint);
	
	
	*/
}


















void AWeapon::Equip(class ANinja* Char, FName SocketName) {
	if (Char) {
		// Attach the weapon to the character's hand
	
		FAttachmentTransformRules AttachRules(EAttachmentRule::SnapToTarget, true);
		ItemMesh->AttachToComponent(Char->GetMesh(), AttachRules, SocketName);



		if (EquipSound)
		{
		UGameplayStatics::PlaySoundAtLocation(this, EquipSound, GetActorLocation());

		}


		if (Sphere)
		{

			Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}



	}

	NiagaraComponent->Deactivate();

}




