// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ControllerDisconnectedUserWidget.h"
#include "A_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class A_LEIS_KATHERINE_API UA_GameInstance : public UGameInstance
{
	GENERATED_BODY()

	int32 ActiveControllerId = -1;

	FTSTicker::FDelegateHandle TickDelegateHandle;

	void HandleControllerConnectionChange(bool bConnected, FPlatformUserId UserID, int32 ControllerID);

	bool bDidControllerDisconnectPauseGame = false;

	UPROPERTY()
	UControllerDisconnectedUserWidget* ControllerDisconnectedWidget;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UControllerDisconnectedUserWidget> ControllerDisconnectedWidgetClass;

public: 
	static const int32 MAX_CONTROLLERS = 4;

	virtual void Init() override;
	virtual void Shutdown() override;

	UFUNCTION()
		bool Tick(float DeltaSeconds);

	void SetActiveControllerID(int32 ControllerID);
	int32 GetActiveControllerID();
};
