// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Fire.generated.h"

UCLASS()
class HANGARGAME_API AFire : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFire();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	int nbSpawn;

	void Damage(int n);

	UPROPERTY(Category = Gameplay, VisibleAnywhere, BlueprintReadWrite)
	int maxNbSpawn;

	int life;

	UPROPERTY(Category = Gameplay, VisibleAnywhere, BlueprintReadWrite)
	int maxLife;

	UPROPERTY(Category = Gameplay, VisibleAnywhere, BlueprintReadWrite)
	float timeToCreate;

	UPROPERTY(Category = Gameplay, VisibleAnywhere, BlueprintReadWrite)
	int damage;

	void SetBaseSize(FVector size);

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	UClass* ExplosionBP;

	void DestroyObject(AActor* obj);

private:

	FVector basesize;

	void SpawnFire();

	void CreateFire(int x, int y, int z);

	FTimerHandle TimerHandle_SpawnFire;
	FTimerHandle TimerHandle_Animation;
	FTimerDelegate TimerDel;
};
