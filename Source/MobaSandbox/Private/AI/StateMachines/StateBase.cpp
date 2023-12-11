// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/StateMachines/StateBase.h"

// TODO: I think this is useless.
UStateBase::UStateBase() :
	ControlledCharacter(nullptr)
{}

void UStateBase::InitializeState(ACharacter* Character, UObject* aWorldContext)
{
	ControlledCharacter = Character;
	WorldContext = aWorldContext;
}

void UStateBase::OnEnter()
{
	UE_LOG(LogTemp, Display, TEXT("OnEnter: %s"), *GetPathName());
	BP_OnEnter();
}

void UStateBase::OnUpdate(float DeltaSeconds)
{
	UE_LOG(LogTemp, Display, TEXT("OnUpdate: %s"), *GetPathName());
	BP_OnUpdate(DeltaSeconds);
}

void UStateBase::OnExit()
{
	UE_LOG(LogTemp, Display, TEXT("OnExit: %s"), *GetPathName());
	BP_OnExit();
}

void UStateBase::BP_OnEnter_Implementation()
{
	UE_LOG(LogTemp, Display, TEXT("BP_OnEnter_Implementation"));
}

void UStateBase::BP_OnUpdate_Implementation(float DeltaSeconds)
{
	UE_LOG(LogTemp, Display, TEXT("BP_OnUpdate_Implementation"));
}

void UStateBase::BP_OnExit_Implementation()
{
	UE_LOG(LogTemp, Display, TEXT("BP_OnExit_Implementation"));
}
