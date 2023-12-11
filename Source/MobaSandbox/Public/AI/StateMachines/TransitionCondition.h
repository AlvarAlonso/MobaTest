// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TransitionCondition.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class MOBASANDBOX_API UTransitionCondition : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	bool BP_Evaluate();
};
