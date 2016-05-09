// Fill out your copyright notice in the Description page of Project Settings.

#include "HangarGame.h"
#include "Weapon.h"


// Sets default values for this component's properties
UWeapon::UWeapon()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	canShoot = true;
	fireRate = 1.0f;
	damage = 10.0f;
	active = true;
	lastShoot = 0.0f;
}


// Called when the game starts
void UWeapon::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UWeapon::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (!canShoot)
	{
		lastShoot += DeltaTime;
		if (lastShoot >= fireRate)
		{
			canShoot = true;
			lastShoot = 0.0f;
		}
	}
}

void UWeapon::Fire()
{
	if (canShoot && active)
	{
		UE_LOG(LogTemp, Warning, TEXT("SHOOT : %s"), *GetReadableName());
		canShoot = false;
	}
}

