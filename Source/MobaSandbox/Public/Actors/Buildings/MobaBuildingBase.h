// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GenericTeamAgentInterface.h"

#include "MobaBuildingBase.generated.h"

UCLASS()
class MOBASANDBOX_API AMobaBuildingBase : public AActor, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMobaBuildingBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** GenericTeamAgentInterface **/
	virtual void SetGenericTeamId(const FGenericTeamId& TeamID) { GenericTeamID = TeamID; }
	virtual FGenericTeamId GetGenericTeamId() const { return GenericTeamID; }
	// -----------------------------

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Team")
	FGenericTeamId GenericTeamID;

};
