// Fill out your copyright notice in the Description page of Project Settings.


#include "A_BlueprintFunctionLibrary.h"
#include "A_GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "AchievementSubSystem.h"

int32 UA_BlueprintFunctionLibrary::GetLastMaxPlayerIndex()
{
	return UA_GameInstance::MAX_CONTROLLERS - 1;
}

void UA_BlueprintFunctionLibrary::SetActiveControllerID(const UObject* WorldContextObject, int32 ControllerID)
{
	UA_GameInstance* GameInstanceRef = Cast<UA_GameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject));
	if (GameInstanceRef)
	{
		GameInstanceRef->SetActiveControllerID(ControllerID);
	}
}

int32 UA_BlueprintFunctionLibrary::GetActiveControllerID(const UObject* WorldContextObject)
{
	UA_GameInstance* GameInstanceRef = Cast<UA_GameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject));
	if (GameInstanceRef)
	{
		return GameInstanceRef->GetActiveControllerID();
	}

	return -1;
}

void UA_BlueprintFunctionLibrary::RemoveAllPlayers(const UObject* WorldContextObject)
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(WorldContextObject, APlayerController::StaticClass(), FoundActors);

	for (AActor* Actor : FoundActors)
	{
		APlayerController* PC = Cast<APlayerController>(Actor);
		if (PC)
		{
			UGameplayStatics::RemovePlayer(PC, true);
		}
	}
}

APlayerController* UA_BlueprintFunctionLibrary::GetActivePlayerController(const UObject* WorldContextObject)
{
	return UGameplayStatics::GetPlayerControllerFromID(WorldContextObject, GetActiveControllerID(WorldContextObject));
}

ACharacter* UA_BlueprintFunctionLibrary::GetActivePlayerCharacter(const UObject* WorldContextObject)
{
	return GetActivePlayerController(WorldContextObject)->GetCharacter();
}

void UA_BlueprintFunctionLibrary::SetupActiveControllerID(const UObject* WorldContextObject, FKey Key, EStatusReturnType& Status)
{
	if(Key.IsGamepadKey())
	{
		for (int32 ControllerIndex = 0; ControllerIndex < UA_GameInstance::MAX_CONTROLLERS; ++ControllerIndex)
		{
			APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, ControllerIndex);
			if (PC->WasInputKeyJustPressed(Key))
			{
				SetActiveControllerID(WorldContextObject, ControllerIndex);
				RemoveAllPlayers(WorldContextObject);
				Status = EStatusReturnType::Success;
				return;
			}
		}
	}
	Status = EStatusReturnType::Failure;
}
UAchievementSubSystem* UA_BlueprintFunctionLibrary::GetAchievementSystem(const UObject* WorldContextObject)
{
	UGameInstance* GameInstanceRef = UGameplayStatics::GetGameInstance(WorldContextObject);
	if (GameInstanceRef)
	{
		return GameInstanceRef->GetSubsystem<UAchievementSubSystem>();
	}
	return nullptr;
}
