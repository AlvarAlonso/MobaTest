// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HitboxComponent.h"

#include "Components/PrimitiveComponent.h"
#include "Components/ShapeComponent.h"

UHitboxComponent::UHitboxComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHitboxComponent::BeginPlay()
{
	Super::BeginPlay();

	TArray<USceneComponent*> Children;
	GetChildrenComponents(false, Children);
	for (USceneComponent* Child : Children)
	{
		UShapeComponent* ShapeComponent = Cast<UShapeComponent>(Child);
		if (ShapeComponent)
		{
			HitboxCollider = ShapeComponent;
			HitboxCollider->OnComponentBeginOverlap.AddDynamic(this, &UHitboxComponent::OnColliderBeginOverlap);
			break;
		}
	}
}

void UHitboxComponent::EndPlay(EEndPlayReason::Type Reason)
{
	Super::EndPlay(Reason);
	
	HitboxCollider->OnComponentBeginOverlap.RemoveDynamic(this, &UHitboxComponent::OnColliderBeginOverlap);
}

void UHitboxComponent::ActivateHitbox()
{
	bActivated = true;
	HitboxCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void UHitboxComponent::DeactivateHitbox()
{
	bActivated = false;
	HitboxCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UHitboxComponent::OnColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Hitbox Begin Collide"));
	BP_OnColliderBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}
