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
		UE_LOG(LogTemp, Warning, TEXT("SHOOT : %s"), *GetReadableName());
		const FVector Start = GetOwner()->GetActorLocation();
		//1000 units in facing direction of PC (1000 units in front of the camera)
		const FVector End = Start + (GetOwner()->GetActorForwardVector() * fireLength);
		FHitResult HitInfo;
		FCollisionQueryParams QParams;
		ECollisionChannel Channel = ECollisionChannel::ECC_Visibility;
		FCollisionQueryParams OParams =	FCollisionQueryParams::DefaultQueryParam;
		if (GetWorld()->LineTraceSingleByChannel(HitInfo, Start, End, ECollisionChannel::ECC_Visibility))
		{
			/*auto MyPC = Cast<ATutoPlayer>(HitInfo.GetActor());
			if (MyPC) {
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue,	TEXT("" + PlayerState->PlayerName + " hits " + MyPC->PlayerState ->PlayerName));
				MyPC->TakeHit(Damage, this);
			}*/
		}
		canShoot = false;
	}
}

