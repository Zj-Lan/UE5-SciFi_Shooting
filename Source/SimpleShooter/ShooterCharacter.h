// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGun;

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure)
	bool IsDead() const {return Health <= 0;};

	void Shoot();

	void Aim();
	void AimDone();

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const {return Health/MaxHealth;};

	UFUNCTION(BlueprintPure)
	bool GetIsCombat() const
	{
		return IsCombat;
	}

	void SetIsCombat(const bool bIsCombat)
	{
		IsCombat = bIsCombat;
	}

private:

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);	

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;

	UPROPERTY()
	AGun* Gun;

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere)
	float Health;

	bool IsCombat;
	
};
