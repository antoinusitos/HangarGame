// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Components/ArrowComponent.h"
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

	UPROPERTY(Category = Gameplay, VisibleAnywhere, BlueprintReadWrite)
	float launchRate;

	UPROPERTY(Category = Gameplay, VisibleAnywhere, BlueprintReadWrite)
	float steamLength;

	UPROPERTY(Category = Gameplay, VisibleAnywhere, BlueprintReadWrite)
	float damage;

	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadWrite)
	class UArrowComponent* theArrowComponent;

	UPROPERTY(Category = Camera, EditAnywhere, BlueprintReadWrite)
	bool parable;

	UFUNCTION(BlueprintImplementableEvent, Category = "Weapon")
	void ShowParticle();

	UFUNCTION(BlueprintImplementableEvent, Category = "Weapon")
	void HideParticle();

	UPROPERTY(Category = Camera, EditAnywhere, BlueprintReadWrite)
	UAudioComponent* AudioComp;

private:

	bool active;

	void LaunchSteam();

	FTimerHandle TimerHandle_LaunchSteam;

	void SteamDetect();

	FTimerHandle TimerHandle_SteamDetect;

	UParticleSystemComponent* steamParticles;
	
};
