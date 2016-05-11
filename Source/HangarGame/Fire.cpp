// Fill out your copyright notice in the Description page of Project Settings.

#include "HangarGame.h"
#include "Fire.h"


// Sets default values
AFire::AFire()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	nbSpawn = 4;

	maxNbSpawn = nbSpawn;

	maxLife = 100;
	life = maxLife;

	timeToCreate = 5.0f;

	damage = 10;
}

// Called when the game starts or when spawned
void AFire::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_SpawnFire, this, &AFire::SpawnFire, timeToCreate);
}

// Called every frame
void AFire::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AFire::SpawnFire() 
{
	//UE_LOG(LogTemp, Warning, TEXT("Fire Spawn"));

	//if (nbSpawn > 0) {

		CreateFire(120, 0, 0);

		CreateFire(-120, 0, 0);

		CreateFire(0, 120, 0);

		CreateFire(0, -120, 0);

	//}

}

void AFire::CreateFire(int x, int y, int z) 
{
	FVector firePos = FVector(GetActorLocation().X + x, GetActorLocation().Y + y, GetActorLocation().Z + z);

	bool canSpawn = true;

	//location the PC is focused on
	const FVector Start = GetActorLocation();
	const FVector End = firePos;

	FHitResult HitInfo;
	FCollisionQueryParams QParams;
	ECollisionChannel Channel = ECollisionChannel::ECC_Visibility;
	FCollisionQueryParams OParams = FCollisionQueryParams::DefaultQueryParam;

	if (GetWorld()->LineTraceSingleByChannel(HitInfo, Start, End, ECollisionChannel::ECC_Visibility))
	{
		auto ob = Cast<AFire>(HitInfo.GetActor());
		if (ob) {

			canSpawn = false;

			//UE_LOG(LogTemp, Warning, TEXT("%s"), *ob->GetName());
		}
		else {
			canSpawn = false;
		}
	}
	float randomF = nbSpawn == maxNbSpawn ? 1 : FMath::FRandRange(0, 1) ;

	if (canSpawn && randomF > 0.45f) {
		AActor* SpawnedActor1 = (AActor*)GetWorld()->SpawnActor(GetClass(), &firePos);

		auto fire = Cast<AFire>(SpawnedActor1);

		if (fire) {
			fire->nbSpawn = nbSpawn - 1;
		}
	}
}

void AFire::Damage(int n) {

	life = FMath::Clamp(life - n, 0, maxLife);
}