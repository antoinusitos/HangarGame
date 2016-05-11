// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Reparable.h"
#include "GameFramework/Actor.h"
#include "Ship.generated.h"

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

	int GetLife();

	int GetLifeMax();

	UFUNCTION(BlueprintImplementableEvent, Category = "CameraShake")
		void StartScreenShake();

private:

	TArray<AReparable*> reparables;

	//AReparable** reparables;

	int nbReparable;
	
};
