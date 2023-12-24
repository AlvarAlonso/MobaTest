// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Buildings/MobaBuildingBase.h"

AMobaBuildingBase::AMobaBuildingBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMobaBuildingBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMobaBuildingBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// TODO:
	// Check distance to enemy.
	// Attack with priority.
}

