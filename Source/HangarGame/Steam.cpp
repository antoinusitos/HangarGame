// Fill out your copyright notice in the Description page of Project Settings.

#include "HangarGame.h"
#include "Steam.h"
#include "ThePlayer.h"


// Sets default values
ASteam::ASteam()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	launchRate = 2;

	steamLength = 5000;

	damage = 1;

	theArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("FireStart"));
	theArrowComponent->AttachTo(RootComponent);

	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("audio"));
	AudioComp->AttachTo(RootComponent);

	parable = true;
}

// Called when the game starts or when spawned
void ASteam::BeginPlay()
{
	Super::BeginPlay();

	TArray<UActorComponent*> comps;
	GetComponents(comps);

	for (int i = 0; i < comps.Num(); ++i) //Because there may be more components
	{
		UParticleSystemComponent* thisComp = Cast<UParticleSystemComponent>(comps[i]);
		if (thisComp)
		{
			steamParticles = thisComp;
		}
	}

	LaunchSteam();
	SteamDetect();

}

// Called every frame
void ASteam::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ASteam::LaunchSteam() 
{
	active = !active;

	steamParticles->SetVisibility(active);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle_LaunchSteam, this, &ASteam::LaunchSteam, launchRate);

	if(active)
		AudioComp->Play();
}

void ASteam::SteamDetect()
{
	if (active) 
	{
		const FVector Start = theArrowComponent->GetComponentLocation();
		const FVector End = GetActorLocation() + GetActorForwardVector()*steamLength;

		FHitResult HitInfo;
		FCollisionQueryParams QParams;
		ECollisionChannel Channel = ECollisionChannel::ECC_Visibility;
		FCollisionQueryParams OParams = FCollisionQueryParams::DefaultQueryParam;
		
		if (GetWorld()->LineTraceSingleByChannel(HitInfo, Start, End, ECollisionChannel::ECC_Visibility))
		{
			auto player = Cast<AThePlayer>(HitInfo.GetActor());
			if (player) 
			{
				if(!parable || (parable && player->checkAngle(this) == false))
					player->PlayerTakeDamage(damage);

				UE_LOG(LogTemp, Warning, TEXT("player touched"));
			}
		}
	}
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_SteamDetect, this, &ASteam::SteamDetect, 0.1f);
}
