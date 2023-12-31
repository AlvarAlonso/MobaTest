// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GenericTeamAgentInterface.h"

#include "MobaCharacterBase.generated.h"

UCLASS()
class MOBASANDBOX_API AMobaCharacterBase : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMobaCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** GenericTeamAgentInterface **/
	UFUNCTION(BlueprintCallable)
	virtual void SetGenericTeamId(const FGenericTeamId& TeamID) { GenericTeamID = TeamID; }
	virtual FGenericTeamId GetGenericTeamId() const { return GenericTeamID; }
	// -----------------------------

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Team")
	FGenericTeamId GenericTeamID;

};
