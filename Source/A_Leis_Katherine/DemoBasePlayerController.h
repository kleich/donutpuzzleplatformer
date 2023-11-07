// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DemoBasePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class A_LEIS_KATHERINE_API ADemoBasePlayerController : public APlayerController
{
	GENERATED_BODY()

	void ToggleSafeZoneMode();
	void ToggleSafeZoneRatio();

protected:
	virtual void SetupInputComponent() override;

};
