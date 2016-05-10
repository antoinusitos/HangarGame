// Fill out your copyright notice in the Description page of Project Settings.

#include "HangarGame.h"
#include "ThePlayer.h"

const FName AThePlayer::MoveForwardBinding("MoveForward");
const FName AThePlayer::MoveRightBinding("MoveRight");
const FName AThePlayer::FireForwardBinding("FireForward");
const FName AThePlayer::FireRightBinding("FireRight");

// Sets default values
AThePlayer::AThePlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Movement
	MoveSpeed = 1000.0f;
}

// Called when the game starts or when spawned
void AThePlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AThePlayer::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	// Find movement direction
	const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
	const float RightValue = GetInputAxisValue(MoveRightBinding);

	// Clamp max size so that (X=1, Y=1) doesn't cause faster movement in diagonal directions
	const FVector MoveDirection = FVector(ForwardValue, RightValue, 0.f).GetClampedToMaxSize(1.0f);

	// Calculate  movement
	const FVector Movement = MoveDirection * MoveSpeed * DeltaTime;

	// If non-zero size, move this actor
	if (Movement.SizeSquared() > 0.0f)
	{
		const FRotator NewRotation = Movement.Rotation();
		FHitResult Hit(1.f);
		RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);

		if (Hit.IsValidBlockingHit())
		{
			const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
			const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
			RootComponent->MoveComponent(Deflection, NewRotation, true);
		}
	}

	// Create fire direction vector
	const float FireForwardValue = GetInputAxisValue(FireForwardBinding);
	const float FireRightValue = GetInputAxisValue(FireRightBinding);
	const FVector FireDirection = FVector(FireForwardValue, FireRightValue, 0.f);

	// Try and fire a shot
	FireShot(FireDirection);
}

// Called to bind functionality to input
void AThePlayer::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis(MoveForwardBinding);
	InputComponent->BindAxis(MoveRightBinding);
	InputComponent->BindAxis(FireForwardBinding);
	InputComponent->BindAxis(FireRightBinding);

	InputComponent->BindAction("Extincteur", IE_Pressed, this, &AThePlayer::SwitchToExtincteur);
	InputComponent->BindAction("Bouclier", IE_Pressed, this, &AThePlayer::SwitchToBouclier);
	InputComponent->BindAction("Cle", IE_Pressed, this, &AThePlayer::SwitchToCle);
	InputComponent->BindAction("Healgun", IE_Pressed, this, &AThePlayer::SwitchToHealGun);
}


void AThePlayer::PlayerTakeDamage(int amount)
{
	currentLife = FMath::Max(0, currentLife - amount);
	if (currentLife == 0)
	{
		//dead
	}
}

void AThePlayer::AddLife(int amount)
{
	currentLife = FMath::Min(maxLife, currentLife + amount);
}

int AThePlayer::GetLife()
{
	return currentLife;
}

int AThePlayer::GetMaxLife()
{
	return maxLife;
}

float AThePlayer::GetLifeRatio()
{
	return (float)currentLife / (float)maxLife;
}

void AThePlayer::SwitchToExtincteur()
{
	UE_LOG(LogTemp, Warning, TEXT("lol"));
	TArray<UWeapon*> comps;
	GetComponents(comps);

	for (auto weapon : comps)
	{
		if (weapon->weaponType == ETypeEnum::Extincteur)
		{
			weapon->active = true;
		}
		else
		{
			weapon->active = false;
		}
	}
}

void AThePlayer::SwitchToBouclier()
{
	UE_LOG(LogTemp, Warning, TEXT("lol"));
	TArray<UWeapon*> comps;
	GetComponents(comps);

	for (auto weapon : comps)
	{
		if (weapon->weaponType == ETypeEnum::Bouclier)
		{
			weapon->active = true;
		}
		else
		{
			weapon->active = false;
		}
	}
}

void AThePlayer::SwitchToCle()
{
	UE_LOG(LogTemp, Warning, TEXT("lol"));
	TArray<UWeapon*> comps;
	GetComponents(comps);

	for (auto weapon : comps)
	{
		if (weapon->weaponType == ETypeEnum::Cle)
		{
			weapon->active = true;
		}
		else
		{
			weapon->active = false;
		}
	}
}

void AThePlayer::SwitchToHealGun()
{
	UE_LOG(LogTemp, Warning, TEXT("lol"));
	TArray<UWeapon*> comps;
	GetComponents(comps);

	for (auto weapon : comps)
	{
		if (weapon->weaponType == ETypeEnum::Healgun)
		{
			weapon->active = true;
		}
		else
		{
			weapon->active = false;
		}
	}
}

void AThePlayer::FireShot(FVector FireDirection)
{
	// If we are pressing fire stick in a direction
	if (FireDirection.SizeSquared() > 0.0f)
	{
		/*const FRotator FireRotation = FireDirection.Rotation();
		// Spawn projectile at an offset from this pawn
		const FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);

		UWorld* const World = GetWorld();
		if (World != NULL)
		{
		// spawn the projectile
		World->SpawnActor<AHangarGameProjectile>(SpawnLocation, FireRotation);
		}

		bCanFire = false;
		World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AHangarGamePawn::ShotTimerExpired, FireRate);

		// try and play the sound if specified
		if (FireSound != nullptr)
		{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
		}

		bCanFire = false;*/
		TArray<UWeapon*> comps;
		GetComponents(comps);

		for (auto weapon : comps)
		{
			weapon->Fire();
		}
	}
}