// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "A_BlueprintFunctionLibrary.generated.h"


UENUM(BlueprintType)
enum class EStatusReturnType : uint8
{
	Success UMETA(DisplayName = "On Success"),
	Failure UMETA(DisplayName = "On Fail")
};

UCLASS()
class A_LEIS_KATHERINE_API UA_BlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "A_BPFunctionLibrary")
		static int32 GetLastMaxPlayerIndex();

	UFUNCTION(BlueprintCallable, Category = "A_BPFunctionLibrary", meta = (WorldContext = "WorldContextObject"))
		static void SetActiveControllerID(const UObject* WorldContextObject, int32 ControllerID);

	UFUNCTION(BlueprintPure, Category = "A_BPFunctionLibrary", meta = (WorldContext = "WorldContextObject"))
		static int32 GetActiveControllerID(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "A_BPFunctionLibrary", meta = (WorldContext = "WorldContextObject"))
		static void RemoveAllPlayers(const UObject* WorldCOntextObject);

	UFUNCTION(BlueprintPure, Category = "A_BPFunctionLibrary", meta = (WorldContext = "WorldContextObject"))
		static class APlayerController* GetActivePlayerController(const UObject* WorldContextObject);
	
	UFUNCTION(BlueprintPure, Category = "A_BPFunctionLibrary", meta = (WorldContext = "WorldContextObject"))
		static class ACharacter* GetActivePlayerCharacter(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "A_BPFunctionLibrary", meta = (WorldContext = "WorldContextObject", ExpandEnumAsExecs = "Status"))
		static void SetupActiveControllerID(const UObject* WorldContextObject, FKey Key, EStatusReturnType& Status);

	UFUNCTION(BlueprintPure, Category = "A_BPFunctionLibrary - Achievements", meta = (WorldContext = "WorldContextObject"))
		static class UAchievementSubSystem* GetAchievementSystem(const UObject* WorldContextObject);
};
