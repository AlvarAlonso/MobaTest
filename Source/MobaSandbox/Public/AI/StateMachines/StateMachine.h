// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StateMachine.generated.h"

class UStateBase;
class UTransitionCondition;
class ACharacter;

USTRUCT(BlueprintType)
struct FStateTransition
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UTransitionCondition>> TransitionConditionClasses;
	TArray<UTransitionCondition*> TransitionConditions;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UStateBase> TargetStateClass;
	UStateBase* TargetState;
	int32 TargetStateIndex;
};

USTRUCT(BlueprintType)
struct FStateInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UStateBase> StateClass;

	UStateBase* StateInstance;

	UPROPERTY(EditAnywhere)
	TArray<FStateTransition> Transitions;
};

USTRUCT()
struct FCreatedStateRuntimeInfo
{
	GENERATED_BODY()

	FCreatedStateRuntimeInfo() :
		CreatedState(nullptr), CreatedStateIndex(0)
	{}

	FCreatedStateRuntimeInfo(UStateBase* aCreatedState, const int32 aCreatedStateIndex) :
		CreatedState(aCreatedState), CreatedStateIndex(aCreatedStateIndex) {}

public:
	UStateBase* CreatedState;
	int32 CreatedStateIndex;
};

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class MOBASANDBOX_API UStateMachine : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void InitializeStateMachine(ACharacter* Character, UObject* aWorldContext);
	
	UFUNCTION(BlueprintCallable)
	void Update(float DeltaSeconds);

private:
	void ConstructStates();
	void ConstructTransitions(const TMap<TSubclassOf<UStateBase>, FCreatedStateRuntimeInfo>& CreatedStatesInfo);
	FCreatedStateRuntimeInfo CheckTransitions();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UStateBase> StartingStateClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FStateInfo> StateInfos;

private:
	TObjectPtr<UStateBase> CurrentState = nullptr;
	int32 CurrentStateIndex = 0;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ACharacter> ControlledCharacter = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UObject> WorldContext = nullptr;
};
