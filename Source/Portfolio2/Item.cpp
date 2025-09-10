// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "Components/SphereComponent.h"
#include "Ninja.h"
#include "GameFramework/CharacterMovementComponent.h" // <-- IMPORTANT include



// Sets default values
AItem::AItem()
{
    // Set this actor to call Tick() every frame
    PrimaryActorTick.bCanEverTick = true;

    // Create mesh and set as root
    ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshG"));
    RootComponent = ItemMesh;

    // Disable mesh collision
    ItemMesh->SetSimulatePhysics(false);
    ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    // Create Sphere component for overlap detection
    Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
    Sphere->SetupAttachment(RootComponent);

    // Configure sphere for overlaps
    Sphere->InitSphereRadius(100.f); // adjust size if needed
    Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    Sphere->SetCollisionObjectType(ECC_WorldDynamic);
    Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
    Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    Sphere->SetGenerateOverlapEvents(true);
}




// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();


	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnOverlapBegin);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AItem::OnOverlapEnd);
	
	
}

float AItem::TransformSin(float value)
{
    return Amplitude * FMath::Sin(value * timeConstant);
}



// Called every frame
void AItem::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);


    if (ItemState == EItemState::EIS_Hover) {
      RunningTime += DeltaTime;


    float DeltaZ =  Amplitude * FMath::Sin(RunningTime * timeConstant);

    AddActorLocalOffset(FVector(0,0,DeltaZ));
	}
    
    




}






void AItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
    UE_LOG(LogTemp, Warning, TEXT("OnOverlapBegin"));

    if (GEngine) {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Item Overlap"));
    }

    ANinja* Ninja = Cast<ANinja>(OtherActor);

    if (Ninja) {

        Ninja->SetEquippedWeapon(this);

      


 
 }
}
void AItem::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex){
	UE_LOG(LogTemp, Warning, TEXT("OnOverlapEnd"));
}