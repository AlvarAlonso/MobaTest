// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/StateMachines/StateMachine.h"
#include "AI/StateMachines/StateBase.h"
#include "AI/StateMachines/TransitionCondition.h"
#include "GameFramework/Character.h"

void UStateMachine::InitializeStateMachine(ACharacter* Character, UObject* aWorldContext)
{
	ControlledCharacter = Character;
	WorldContext = aWorldContext;
	ConstructStates();
	CurrentState->OnEnter();
}


void UStateMachine::Update(float DeltaSeconds)
{
	if (!IsValid(CurrentState))
	{
		UE_LOG(LogTemp, Error, TEXT("The CurrentState is NULL!!!"));
		return;
	}

	if (!IsValid(ControlledCharacter))
	{
		UE_LOG(LogTemp, Error, TEXT("The ControlledCharacter is NULL!!!"));
		return;
	}

	FCreatedStateRuntimeInfo StateRuntimeInfo = CheckTransitions();
	if (StateRuntimeInfo.CreatedState != nullptr)
	{
		CurrentState->OnExit();
		CurrentState = StateRuntimeInfo.CreatedState;
		CurrentStateIndex = StateRuntimeInfo.CreatedStateIndex;
		CurrentState->OnEnter();
	}
	else
	{
		CurrentState->OnUpdate(DeltaSeconds);
	}
}

void UStateMachine::ConstructStates()
{
	TMap<TSubclassOf<UStateBase>, FCreatedStateRuntimeInfo> CreatedStatesInfo;
	int32 Index = 0;
	for (auto& StateInfo : StateInfos)
	{
		ensure(StateInfo.StateClass->IsValidLowLevel());
		UStateBase* NewState = NewObject<UStateBase>(StateInfo.StateClass);
		NewState->InitializeState(ControlledCharacter, WorldContext);
		StateInfo.StateInstance = NewState;
		if (StateInfo.StateClass == StartingStateClass)
		{
			CurrentState = NewState;
			CurrentStateIndex = Index;
		}

		CreatedStatesInfo.Add(StateInfo.StateClass, { NewState, Index });
		++Index;
	}

	ConstructTransitions(CreatedStatesInfo);
}

void UStateMachine::ConstructTransitions(const TMap<TSubclassOf<UStateBase>, FCreatedStateRuntimeInfo>& CreatedStatesInfo)
{
	for (auto& StateInfo : StateInfos)
	{
		for (auto& Transition : StateInfo.Transitions)
		{
			for (auto& TransitionConditionClass : Transition.TransitionConditionClasses)
			{
				UTransitionCondition* NewTransitionCondition = NewObject<UTransitionCondition>(TransitionConditionClass);
				Transition.TransitionConditions.Add(NewTransitionCondition);
			}

			const auto& CreatedStateInfo = CreatedStatesInfo.Find(Transition.TargetStateClass);
			Transition.TargetState = CreatedStateInfo->CreatedState;
			Transition.TargetStateIndex = CreatedStateInfo->CreatedStateIndex;
		}
	}
}

FCreatedStateRuntimeInfo UStateMachine::CheckTransitions()
{
	FCreatedStateRuntimeInfo ReturnValue = FCreatedStateRuntimeInfo();
	FStateInfo& CurrentStateInfo = StateInfos[CurrentStateIndex];
	for (const auto& Transition : CurrentStateInfo.Transitions)
	{
		// TODO: Create expressions using the conditions (add AND and OR logical operators).
		for (const auto& TransitionCondition : Transition.TransitionConditions)
		{
			if (TransitionCondition->BP_Evaluate())
			{
				ReturnValue.CreatedState = Transition.TargetState;
				ReturnValue.CreatedStateIndex = Transition.TargetStateIndex;
			}
		}
	}

	return ReturnValue;
}
