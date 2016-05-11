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

	theArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("FireStart"));
	theArrowComponent->AttachTo(RootComponent);

	// Movement
	MoveSpeed = 500.0f;
	bouclierEquipe = false;
	angleBouclier = 10.0f;

	maxLife = 100.0f;
	currentLife = maxLife;

	// Animation
	hit = false;
	reload = false;
	dead = false;
	shoot = false;
	changeGun = false;
	attack = false;
	theSpeed = 0.0f;

	healTime = 1.0f;
	currentHealTime = 0.0f;
	isHealing = false;
	canHeal = true;
	healAmount = 5;

	currentWeaponType = ETypeEnum::Cle;
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

	if (currentLife >= 0)
	{
		// Find movement direction
		const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
		const float RightValue = GetInputAxisValue(MoveRightBinding);

		// Clamp max size so that (X=1, Y=1) doesn't cause faster movement in diagonal directions
		const FVector MoveDirection = FVector(ForwardValue, RightValue, 0.f).GetClampedToMaxSize(1.0f);

		// Calculate  movement
		const FVector Movement = MoveDirection * MoveSpeed * DeltaTime;

		theSpeed = Movement.SizeSquared();
		/*if (MoveDirection.X < 0.0f)
			theSpeed *= -1;*/

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

		if (isHealing)
		{
			currentHealTime += DeltaTime;
			if (FMath::Fmod(currentHealTime, 0.1f) <= 0.01f)
			{
				AddLife(healAmount);
			}
			if (currentHealTime >= healTime)
			{
				canHeal = true;
				isHealing = false;
			}
		}
	}
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
		dead = true;
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
	UE_LOG(LogTemp, Warning, TEXT("extincteur"));

	if (currentWeaponType != ETypeEnum::Extincteur)
	{
		currentWeaponType = ETypeEnum::Extincteur;
		TArray<UWeapon*> comps;
		GetComponents(comps);

		for (auto weapon : comps)
		{
			if (weapon->weaponType == ETypeEnum::Extincteur)
			{
				changeGun = true;
				StopAnimation(0);
				weapon->active = true;
			}
			else
			{
				weapon->active = false;
			}
		}
	}
}

void AThePlayer::SwitchToBouclier()
{
	UE_LOG(LogTemp, Warning, TEXT("bouclier"));

	if (currentWeaponType != ETypeEnum::Bouclier)
	{
		currentWeaponType = ETypeEnum::Bouclier;
		TArray<UWeapon*> comps;
		GetComponents(comps);

		for (auto weapon : comps)
		{
			if (weapon->weaponType == ETypeEnum::Bouclier)
			{
				changeGun = true;
				StopAnimation(0);
				weapon->active = true;
			}
			else
			{
				weapon->active = false;
			}
		}
	}
}

void AThePlayer::SwitchToCle()
{
	UE_LOG(LogTemp, Warning, TEXT("cle"));

	if (currentWeaponType != ETypeEnum::Cle)
	{
		currentWeaponType = ETypeEnum::Cle;
		TArray<UWeapon*> comps;
		GetComponents(comps);

		for (auto weapon : comps)
		{
			if (weapon->weaponType == ETypeEnum::Cle)
			{
				changeGun = true;
				StopAnimation(0);
				weapon->active = true;
			}
			else
			{
				weapon->active = false;
			}
		}
	}
}

void AThePlayer::SwitchToHealGun()
{
	UE_LOG(LogTemp, Warning, TEXT("healgun"));

	if (currentWeaponType != ETypeEnum::Healgun)
	{
		currentWeaponType = ETypeEnum::Healgun;
		TArray<UWeapon*> comps;
		GetComponents(comps);

		for (auto weapon : comps)
		{
			if (weapon->weaponType == ETypeEnum::Healgun)
			{
				changeGun = true;
				StopAnimation(0);
				weapon->active = true;
			}
			else
			{
				weapon->active = false;
			}
		}
	}
}

void AThePlayer::FireShot(FVector FireDirection)
{
	// If we are pressing fire stick in a direction
	if (FireDirection.SizeSquared() > 0.0f)
	{
		const FRotator FireRotation = FireDirection.Rotation();
		// Spawn projectile at an offset from this pawn
		//const FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);

		SetActorRotation(FireRotation);

		TArray<UWeapon*> comps;
		GetComponents(comps);

		for (auto weapon : comps)
		{
			weapon->Fire();
		}
	}
	else
	{
		bouclierEquipe = false;
		SetBool(0, false);
		SetBool(1, false);
		SetBool(2, false);
	}
}

void AThePlayer::SetBool(int theBool, bool state)
{
	if (theBool == 0)
	{
		changeGun = state;
	}
	else if (theBool == 1)
	{
		shoot = state;
	}
	else if (theBool == 2)
	{
		attack = state;
	}
}

void AThePlayer::StopAnimation(int id)
{
	TimerDel = FTimerDelegate::CreateUObject(this, &AThePlayer::SetBool, id, false);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_Animation, TimerDel, .2f, false);
}

void AThePlayer::Heal()
{
	if (canHeal)
	{
		canHeal = false;
		isHealing = true;
		currentHealTime = 0.0f;
	}
}

bool AThePlayer::checkAngle(AActor * origin)
{
	bool retour = false;
	FVector AB = GetActorLocation() - origin->GetActorLocation();
	FVector AC = GetActorForwardVector();
	float angle = FMath::Acos((AB.X*AC.X + AB.Y*AC.Y + AB.Z*AC.Z) / (sqrt((AB.X * AB.X) + (AB.Y * AB.Y) + (AB.Z * AB.Z))*sqrt((AC.X * AC.X) + (AC.Y * AC.Y) + (AC.Z * AC.Z))));
	float degAngle = FMath::RadiansToDegrees(angle);
	if (degAngle <= angleBouclier)
		retour = true;
	return retour;
}
