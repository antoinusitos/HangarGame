// Fill out your copyright notice in the Description page of Project Settings.

#include "HangarGame.h"
#include "Ship.h"

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
		reparables[nbReparable] = *ActorItr;
		nbReparable++;
	}

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

