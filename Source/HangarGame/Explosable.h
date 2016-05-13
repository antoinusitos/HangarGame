// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/DecalComponent.h"
#include "GameFramework/Actor.h"
#include "Explosable.generated.h"

UCLASS()
class HANGARGAME_API AExplosable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExplosable();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void Explose(float timer);
	
	bool blockable;

	int damage;

	UPROPERTY(Category = active, EditAnywhere, BlueprintReadWrite)
	float forceExplosion;

private:

	void DoExplosion();

	FTimerHandle TimerHandle_DoExplosion;

	UDecalComponent* myDecal;

	UParticleSystemComponent* warning;

	UParticleSystemComponent* trigger;

};
