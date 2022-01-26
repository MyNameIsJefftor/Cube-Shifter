// Fill out your copyright notice in the Description page of Project Settings.


#include "SlideCube.h"

ASlideCube::ASlideCube()
{
	parent = CreateDefaultSubobject<USceneComponent>(TEXT("Parent"));
	RootComponent = parent;

	posCube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("posCube"));
	posCube->SetupAttachment(parent);

	negCube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("negCube"));
	negCube->SetupAttachment(parent);

	//MyTarget = CreateDefaultSubobject<UMoveMarker>(TEXT("Target"));
}

void ASlideCube::Shift()
{
	Disable(posCube);
	Disable(negCube);
	isPositve = !isPositve;
	return;
}

void ASlideCube::WorldStateChange(bool worldState)
{
	if (worldState)
		if (isPositve)
			Enable(posCube);
		else
			Disable(negCube);
	else
		if (isPositve)
			Disable(posCube);
		else
			Enable(negCube);
}

void ASlideCube::BeginPlay()
{
	Super::BeginPlay();

	if (!PositiveState) Shift(); 
	else Disable(negCube);
}

bool ASlideCube::Disable(USceneComponent* mesh)
{
	CastChecked<UStaticMeshComponent>(mesh)->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CastChecked<UStaticMeshComponent>(mesh)->SetVisibility(false);
	return true;
}

bool ASlideCube::Enable(USceneComponent* mesh)
{
	CastChecked<UStaticMeshComponent>(mesh)->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CastChecked<UStaticMeshComponent>(mesh)->SetVisibility(true);
	return true;
}

