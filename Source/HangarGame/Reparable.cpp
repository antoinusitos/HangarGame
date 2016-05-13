// Fill out your copyright notice in the Description page of Project Settings.

#include "HangarGame.h"
#include "Reparable.h"

// Sets default values
AReparable::AReparable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	maxLife = 100;
	life = 0;
	active = false;
}

// Called when the game starts or when spawned
void AReparable::BeginPlay()
{

	isBeingRepaired = false;
	Super::BeginPlay();
	
}

// Called every frame
void AReparable::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AReparable::Repare(int n) 
{
	if (active)
	{
		isBeingRepaired = true;

		life = FMath::Clamp(life + n, 0, maxLife);

		if (life >= maxLife) {
			ship->changeReparable(this);
		}
	}
}

void AReparable::Destroy(int n)
{
	life = FMath::Clamp(life - n, 0, maxLife);
}

int AReparable::GetLife()
{
	return life;
}
