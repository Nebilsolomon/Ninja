

#include "BreakableActor.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "Treasure.h"

// Sets default values






ABreakableActor::ABreakableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	GeometryCollection = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("GeometryCollection"));

	SetRootComponent(GeometryCollection);

	GeometryCollection->SetGenerateOverlapEvents(true);

	GeometryCollection->SetCollisionResponseToChannel( ECC_Pawn, ECR_Ignore);

	



}




// Called when the game starts or when spawned
void ABreakableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABreakableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABreakableActor::GetHit_Implementation(const FVector& ImpactPoint)
{

	if (bHasBeenHit) return; // ignore repeated hits
	bHasBeenHit = true;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, "Breakable actor hit");

	UWorld* World = GetWorld();
	if (World && TreasureSubclasses.Num() > 0) {
		//World->SpawnActor<AActor>(AActor::StaticClass(), ImpactPoint, FRotator::ZeroRotator);


		FVector Location = GetActorLocation();
		Location.Z += 50.f;

		const int32 RandIndex = FMath::RandRange(0, TreasureSubclasses.Num() - 1);

		World->SpawnActor<ATreasure>(TreasureSubclasses[RandIndex], Location, GetActorRotation());
		SetLifeSpan(3.0f);
	}
}











