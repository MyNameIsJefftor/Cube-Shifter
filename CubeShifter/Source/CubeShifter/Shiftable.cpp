// Fill out your copyright notice in the Description page of Project Settings.


#include "Shiftable.h"

// Sets default values
AShiftable::AShiftable()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	PositiveState = true;
}

AShiftable::AShiftable(bool StartState)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	PositiveState = StartState;
}

void AShiftable::Shift()
{
	return;
}
