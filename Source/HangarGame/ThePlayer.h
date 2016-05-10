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

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	FVector FireStart;

	/** Start of the Fire */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadWrite)
	class UArrowComponent* theArrowComponent;

private:
	/** Handle the life of the player */
	int currentLife;
	int maxLife;
	
	static const FName MoveForwardBinding;
	static const FName MoveRightBinding;
	static const FName FireForwardBinding;
	static const FName FireRightBinding;

	

};
