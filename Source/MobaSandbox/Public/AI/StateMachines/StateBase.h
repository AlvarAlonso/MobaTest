// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StateBase.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class MOBASANDBOX_API UStateBase : public UObject
{
	GENERATED_BODY()

	friend class UStateMachine;

	UStateBase();

private:
	void InitializeState(ACharacter* Character, UObject* aWorldContext);
	void OnEnter();
	void OnUpdate(float DeltaSeconds);
	void OnExit();

public:
	UFUNCTION(BlueprintNativeEvent)
	void BP_OnEnter();
	UFUNCTION(BlueprintNativeEvent)
	void BP_OnUpdate(float DeltaSeconds);
	UFUNCTION(BlueprintNativeEvent)
	void BP_OnExit();

public:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ACharacter> ControlledCharacter;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WorldContext;
};
