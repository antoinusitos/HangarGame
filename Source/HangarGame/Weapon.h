// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Reparable.h"
#include "Weapon.generated.h"

UENUM(BlueprintType)		
enum class ETypeEnum : uint8
{
	Cle 		UMETA(DisplayName = "Cle"),
	Healgun 	UMETA(DisplayName = "Healgun"),
	Bouclier	UMETA(DisplayName = "Bouclier"),
	Extincteur	UMETA(DisplayName = "Extincteur"),
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HANGARGAME_API UWeapon : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeapon();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	void Fire();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	bool active;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	ETypeEnum weaponType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	bool canShoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float fireRate;
	float lastShoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float fireLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int damage;

	void ApplyDamage(AActor* receiver);

	void PlayAnimation();
};
