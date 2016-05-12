// Fill out your copyright notice in the Description page of Project Settings.

#include "HangarGame.h"
#include "Explosable.h"
#include "ThePlayer.h"

// Sets default values
AExplosable::AExplosable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	damage = 20;
}

// Called when the game starts or when spawned
void AExplosable::BeginPlay()
{
	Super::BeginPlay();

	TArray<UActorComponent*> comps;
	GetComponents(comps);

	for (int i = 0; i < comps.Num(); ++i) //Because there may be more components
	{
		/*UDecalComponent* thisComp = Cast<UDecalComponent>(comps[i]);
		if (thisComp)
		{
			myDecal = thisComp;
		}*/
		UParticleSystemComponent* thisComp2 = Cast<UParticleSystemComponent>(comps[i]);
		if (thisComp2 && thisComp2->GetName().Contains("Warning"))
		{
			UE_LOG(LogTemp, Warning, TEXT("explosion warning"));
			warning = thisComp2;
		}
		else if (thisComp2 && thisComp2->GetName().Contains("Trigger"))
		{
			UE_LOG(LogTemp, Warning, TEXT("explosion trigger"));
			trigger = thisComp2;
		}
	}
	
	//myDecal->SetVisibility(false);
	warning->SetVisibility(false);
	trigger->SetVisibility(false);

	Explose(3);
}

// Called every frame
void AExplosable::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AExplosable::Explose(float timer)
{
	//myDecal->SetVisibility(true);
	warning->SetVisibility(true);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle_DoExplosion, this, &AExplosable::DoExplosion, timer);
}

void AExplosable::DoExplosion()
{
	//myDecal->SetVisibility(false);

	warning->SetVisibility(false);
	trigger->SetVisibility(true);
	trigger->ActivateSystem(true);

	//explosion fx

	TArray<AActor*> actors;

	GetOverlappingActors(actors);

	for (auto It = actors.CreateConstIterator(); It; ++It)
	{
		auto player = Cast<AThePlayer>(*It);
		if (player) {
			player->PlayerTakeDamage(damage);

			UE_LOG(LogTemp, Warning, TEXT("Player detected"));
		}
	}
	
}

