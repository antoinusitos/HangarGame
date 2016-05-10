// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Reparable.generated.h"

UCLASS()
class HANGARGAME_API AReparable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AReparable();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void Repare(int n);

	void Destroy(int n);

	int maxLife;

private:

	int life;
	
};
