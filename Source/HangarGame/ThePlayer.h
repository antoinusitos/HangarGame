// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Weapon.h"
#include "Components/ArrowComponent.h"
#include "ThePlayer.generated.h"

UCLASS()
class HANGARGAME_API AThePlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AThePlayer();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

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

	/* The speed our ship moves around the level */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float MoveSpeed;

	/* Fire a shot in the specified direction */
	void FireShot(FVector FireDirection);

	bool bouclierEquipe;
	UPROPERTY(Category = Bouclier, EditAnywhere, BlueprintReadWrite)
	float angleBouclier;


	/** Start of the Fire */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadWrite)
	class UArrowComponent* theArrowComponent;

	/** Animation states */
	UPROPERTY(Category = Animation, VisibleAnywhere, BlueprintReadWrite)
	bool hit;
	UPROPERTY(Category = Animation, VisibleAnywhere, BlueprintReadWrite)
	bool reload;
	UPROPERTY(Category = Animation, VisibleAnywhere, BlueprintReadWrite)
	bool dead;
	UPROPERTY(Category = Animation, VisibleAnywhere, BlueprintReadWrite)
	bool shoot;
	UPROPERTY(Category = Animation, VisibleAnywhere, BlueprintReadWrite)
	bool changeGun;
	UPROPERTY(Category = Animation, VisibleAnywhere, BlueprintReadWrite)
	bool attack;
	UPROPERTY(Category = Animation, VisibleAnywhere, BlueprintReadWrite)
	float theSpeed;

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void StopAnimation(int id);

	/** FIN ANIMATION */

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	int maxLife;

	void Heal();

	UPROPERTY(Category = Heal, EditAnywhere, BlueprintReadWrite)
	float healTime;
	float currentHealTime;
	bool canHeal;
	bool isHealing;
	UPROPERTY(Category = Heal, EditAnywhere, BlueprintReadWrite)
	int healAmount;

	bool checkAngle(AActor* origin);

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	float GetMaxCoolDown();
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	float GetCoolDown();

	UPROPERTY(Category = Heal, EditAnywhere, BlueprintReadWrite)
	ETypeEnum currentWeaponType;

	UFUNCTION(BlueprintImplementableEvent, Category = "Weapon")
	void ChangeWeapon();

	UFUNCTION(BlueprintImplementableEvent, Category = "Weapon")
	void ShowParticle();

	UFUNCTION(BlueprintImplementableEvent, Category = "Weapon")
	void HideParticle();

private:
	/** Handle the life of the player */
	int currentLife;
	
	
	static const FName MoveForwardBinding;
	static const FName MoveRightBinding;
	static const FName FireForwardBinding;
	static const FName FireRightBinding;

	FTimerHandle TimerHandle_Animation;
	FTimerDelegate TimerDel;

	void SetBool(int theBool, bool state);

	//TArray<UWeapon*> comps;
};
