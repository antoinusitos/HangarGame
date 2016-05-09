// Fill out your copyright notice in the Description page of Project Settings.

#include "HangarGame.h"
#include "TheCharacter.h"


// Sets default values
ATheCharacter::ATheCharacter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATheCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATheCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ATheCharacter::PlayerTakeDamage(int amount)
{
	currentLife = FMath::Max(0, currentLife - amount);
	if (currentLife == 0)
	{
		//dead
	}
}

void ATheCharacter::AddLife(int amount)
{
	currentLife = FMath::Min(maxLife, currentLife + amount);
}

int ATheCharacter::GetLife()
{
	return currentLife;
}

int ATheCharacter::GetMaxLife()
{
	return maxLife;
}

float ATheCharacter::GetLifeRatio()
{
	return (float)currentLife / (float)maxLife;
}

void ATheCharacter::SwitchToExtincteur()
{
	TArray<UWeapon*> comps;
	GetComponents(comps);

	for (auto weapon : comps)
	{
		if (weapon->weaponType == ETypeEnum::Extincteur)
		{
			weapon->active = true;
		}
		else
		{
			weapon->active = false;
		}
	}
}

void ATheCharacter::SwitchToBouclier()
{
	TArray<UWeapon*> comps;
	GetComponents(comps);

	for (auto weapon : comps)
	{
		if (weapon->weaponType == ETypeEnum::Bouclier)
		{
			weapon->active = true;
		}
		else
		{
			weapon->active = false;
		}
	}
}

void ATheCharacter::SwitchToCle()
{
	TArray<UWeapon*> comps;
	GetComponents(comps);

	for (auto weapon : comps)
	{
		if (weapon->weaponType == ETypeEnum::Cle)
		{
			weapon->active = true;
		}
		else
		{
			weapon->active = false;
		}
	}
}

void ATheCharacter::SwitchToHealGun()
{
	TArray<UWeapon*> comps;
	GetComponents(comps);

	for (auto weapon : comps)
	{
		if (weapon->weaponType == ETypeEnum::Healgun)
		{
			weapon->active = true;
		}
		else
		{
			weapon->active = false;
		}
	}
}