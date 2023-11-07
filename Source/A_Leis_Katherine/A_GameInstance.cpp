// Fill out your copyright notice in the Description page of Project Settings.


#include "A_GameInstance.h"
#include "A_BlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
//#include "ControllerDisconnectedUserWidget.h"

void UA_GameInstance::Init()
{
	Super::Init();
	FTickerDelegate TickDelegate = FTickerDelegate::CreateUObject(this, &UA_GameInstance::Tick);
	TickDelegateHandle = FTSTicker::GetCoreTicker().AddTicker(TickDelegate);

	FCoreDelegates::OnControllerConnectionChange.AddUObject(this, &UA_GameInstance::HandleControllerConnectionChange);
}

void UA_GameInstance::Shutdown()
{
	Super::Shutdown();
	FTSTicker::GetCoreTicker().RemoveTicker(TickDelegateHandle);
}

bool UA_GameInstance::Tick(float DeltaTime)
{
	if (GEngine)
	{
		FString message = FString::Printf(TEXT("Active controller ID: %d"), ActiveControllerId);
		GEngine->AddOnScreenDebugMessage(1, 0.2f, FColor::Blue, *message);
	}
	return true;
}

void UA_GameInstance::SetActiveControllerID(int32 ControllerID)
{
	ActiveControllerId = ControllerID;
}

int32 UA_GameInstance::GetActiveControllerID()
{
	return ActiveControllerId;
}

void UA_GameInstance::HandleControllerConnectionChange(bool bConnected, FPlatformUserId UserID, int32 ControllerID)
{
	FString UserID_text;
	if (UserID == PLATFORMUSERID_NONE)
	{
		UserID_text = TEXT("None");
	}
	else
	{
		UserID_text = FString::Printf(TEXT("ID "), UserID.GetInternalId());
	}

	FString message = FString::Printf(TEXT("Controller connection changed - UserIDx:%d, UserID:%s, Connected:%d"), ControllerID, *UserID_text, bConnected ? 1 : 0);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, message);

	if (GetActiveControllerID() == ControllerID)
	{
		if (APlayerController* ActivePC = UA_BlueprintFunctionLibrary::GetActivePlayerController(this))
		{
			if (bConnected)
			{
				if (bDidControllerDisconnectPauseGame)
				{
					UGameplayStatics::SetGamePaused(this, false);
					bDidControllerDisconnectPauseGame = false;
				}
				ControllerDisconnectedWidget->RemoveFromParent();
			}
			else
			{
				if (ControllerDisconnectedWidgetClass)
				{
					if (!UGameplayStatics::IsGamePaused(this))
					{
						bDidControllerDisconnectPauseGame = true;
						UGameplayStatics::SetGamePaused(this, true);
					}
					ControllerDisconnectedWidget = CreateWidget<UControllerDisconnectedUserWidget>(ActivePC, ControllerDisconnectedWidgetClass);
					ControllerDisconnectedWidget->AddToViewport();
				}
				else
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("ControllerDisconnectedWidgetClass not set."));
				}
			}
		}
	}
}

