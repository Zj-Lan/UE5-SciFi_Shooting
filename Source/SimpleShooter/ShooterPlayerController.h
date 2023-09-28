// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
public:
	virtual void GameHasEnded(AActor* EndGameFocus, bool bIsWinner) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> HUDClass;

private:
	UPROPERTY()
	UUserWidget* HUD;
};
