// Fill out your copyright notice in the Description page of Project Settings.

#include "HangarGame.h"
#include "Weapon.h"
#include "ThePlayer.h"
#include "Fire.h"


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
	fireLength = 1000;
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
		//UE_LOG(LogTemp, Warning, TEXT("SHOOT : %s"), *GetReadableName());

		PlayAnimation();

		const FVector Start = (Cast<AThePlayer>(GetOwner()))->theArrowComponent->GetComponentLocation();
		//1000 units in facing direction of PC (1000 units in front of the camera)
		const FVector End = Start + (GetOwner()->GetActorForwardVector() * fireLength);
		FHitResult HitInfo;
		FCollisionQueryParams QParams;
		ECollisionChannel Channel = ECollisionChannel::ECC_Visibility;
		FCollisionQueryParams OParams =	FCollisionQueryParams::DefaultQueryParam;
		if (GetWorld()->LineTraceSingleByChannel(HitInfo, Start, End, ECollisionChannel::ECC_Visibility))
		{
			ApplyDamage(HitInfo.GetActor());
		}
		if(weaponType != ETypeEnum::Bouclier)
			canShoot = false;
		else
		{
			Cast<AThePlayer>(GetOwner())->bouclierEquipe = true;
		}
	}
	else if (active)
	{
		Cast<AThePlayer>(GetOwner())->attack = false;
	}

}

void UWeapon::PlayAnimation()
{
	if (weaponType == ETypeEnum::Cle)
	{
		Cast<AThePlayer>(GetOwner())->attack = true;
		Cast<AThePlayer>(GetOwner())->bouclierEquipe = false;
	}
	else if (weaponType == ETypeEnum::Extincteur)
	{
		Cast<AThePlayer>(GetOwner())->shoot = true;
		Cast<AThePlayer>(GetOwner())->bouclierEquipe = false;
	}
	else if (weaponType == ETypeEnum::Healgun)
	{
		Cast<AThePlayer>(GetOwner())->shoot = true;
		Cast<AThePlayer>(GetOwner())->bouclierEquipe = false;
	}
}

void UWeapon::ApplyDamage(AActor* receiver)
{
	if (weaponType == ETypeEnum::Cle)
	{
		auto theReparable = Cast<AReparable>(receiver);
		if (theReparable)
		{
			
			theReparable->Repare(damage);
		}
	}
	else if (weaponType == ETypeEnum::Bouclier)
	{
		Cast<AThePlayer>(GetOwner())->bouclierEquipe = true;
	}
	else if (weaponType == ETypeEnum::Extincteur)
	{
		auto theFire = Cast<AFire>(receiver);
		if (theFire)
		{
			theFire->Damage(damage);
		}
	}
	else if (weaponType == ETypeEnum::Healgun)
	{
		auto theCharacter = Cast<AThePlayer>(receiver);
		if (theCharacter)
		{
			theCharacter->Heal();
		}
	}	
}

