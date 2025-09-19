// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Ninja.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"




AWeapon::AWeapon() {
	WeaponBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponBox"));
	WeaponBox->SetupAttachment(GetRootComponent());
	WeaponBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	WeaponBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	WeaponBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);


	StartTraceBox = CreateDefaultSubobject<USceneComponent>(TEXT("StartTraceBox"));
	StartTraceBox->SetupAttachment(GetRootComponent());
	EndTraceBox = CreateDefaultSubobject<USceneComponent>(TEXT("EndTraceBox"));
	EndTraceBox->SetupAttachment(GetRootComponent());





}



void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	WeaponBox->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnBoxOverlapBegin);

}


void AWeapon::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){

	Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);




}



void AWeapon::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex){

	Super::OnOverlapEnd(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);





}	



void AWeapon::OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {


	const FVector Start = StartTraceBox->GetComponentLocation();
	const FVector End = EndTraceBox->GetComponentLocation();
	 DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2.f);



	 TArray<AActor*> ActorToIgnore;
	 ActorToIgnore.Add(this);
	 FHitResult BoxHit;
	 UKismetSystemLibrary::BoxTraceSingle(
		 this,
		 Start,
		 End,
		 FVector(5, 5, 5),
		 StartTraceBox->GetComponentRotation(),
		 ETraceTypeQuery::TraceTypeQuery1,
		 false,
		 ActorToIgnore,
		 EDrawDebugTrace::ForDuration,
		 BoxHit,
		 true



	 );



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
}




