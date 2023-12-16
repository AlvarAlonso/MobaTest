// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "HitboxComponent.generated.h"

class UPrimitiveComponent;
class UShapeComponent;

UCLASS(BlueprintType, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MOBASANDBOX_API UHitboxComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	UHitboxComponent();

	UFUNCTION(BlueprintCallable)
	void ActivateHitbox();

	UFUNCTION(BlueprintCallable)
	void DeactivateHitbox();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type Reason) override;

private:
	UFUNCTION()
	void OnColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	bool bActivated = false;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	TObjectPtr<UShapeComponent> HitboxCollider;
};
