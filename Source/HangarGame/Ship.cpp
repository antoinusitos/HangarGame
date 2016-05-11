// Fill out your copyright notice in the Description page of Project Settings.

#include "HangarGame.h"
#include "Ship.h"
#include "Reparable.h"

// Sets default values
AShip::AShip()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShip::BeginPlay()
{
	Super::BeginPlay();
	
	nbReparable = 0;

	for (TActorIterator<AReparable> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		AReparable* aR = *ActorItr;

		reparables.Add(aR);

		canBeRepared.Add(aR);

		nbReparable++;

		aR->ship = this;
	}

	int index = FMath::RandRange(0, reparables.Num()-1);
	reparables[index]->active = true;

}

// Called every frame
void AShip::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

int AShip::GetLife()
{
	int life = 0;

	for (int i = 0; i < nbReparable; i++) 
	{
		life = life + reparables[i]->GetLife();
	}

	return life;
}

int AShip::GetLifeMax()
{
	int life = 0;

	for (int i = 0; i < nbReparable; i++) 
	{
		life = life + reparables[i]->maxLife;
	}

	return life;
}

void AShip::changeReparable(AReparable* reparated)
{
	canBeRepared.Remove(reparated);

	if (canBeRepared.Num() > 0) {
		int index = FMath::RandRange(0, canBeRepared.Num() - 1);
		canBeRepared[index]->active = true;
	}
}