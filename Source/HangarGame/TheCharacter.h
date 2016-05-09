// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Weapon.h"
#include "TheCharacter.generated.h"

UCLASS()
class HANGARGAME_API ATheCharacter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATheCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	void SwitchToExtincteur();
	void SwitchToBouclier();
	void SwitchToCle();
	void SwitchToHealGun();

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void PlayerTakeDamage(int amount);
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void AddLife(int amount);
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	int GetLife();
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	int GetMaxLife();
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	float GetLifeRatio();

private :
	/** Handle the life of the player */
	int currentLife;
	int maxLife;
};
