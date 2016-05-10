// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Steam.generated.h"

UCLASS()
class HANGARGAME_API ASteam : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASteam();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	float launchRate;

	float steamLength;

	float damage;

private:

	bool active;

	void LaunchSteam();

	FTimerHandle TimerHandle_LaunchSteam;

	void SteamDetect();

	FTimerHandle TimerHandle_SteamDetect;

	UParticleSystemComponent* steamParticles;
	
};
