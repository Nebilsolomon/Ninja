// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Ninja.h"
#include "Components/SphereComponent.h"






void AWeapon::BeginPlay()
{
	Super::BeginPlay();



}


void AWeapon::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){

	Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);




}



void AWeapon::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex){

	Super::OnOverlapEnd(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);





}	




void AWeapon::Equip(class ANinja* Char, FName SocketName) {
	if (Char) {
		// Attach the weapon to the character's hand
	
		FAttachmentTransformRules AttachRules(EAttachmentRule::SnapToTarget, true);
		ItemMesh->AttachToComponent(Char->GetMesh(), AttachRules, SocketName);

		



	}
}