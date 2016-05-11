// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/Actor.h"
#include "Ship.generated.h"

class AReparable;

UCLASS()
class HANGARGAME_API AShip : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShip();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	int GetLife();

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	int GetLifeMax();

	UFUNCTION(BlueprintImplementableEvent, Category = "CameraShake")
	void StartScreenShake();

	void changeReparable(AReparable* reparated);

private:

	TArray<AReparable*> reparables;

	TArray<AReparable*> canBeRepared;

	//AReparable** reparables;

	int nbReparable;
	
};
