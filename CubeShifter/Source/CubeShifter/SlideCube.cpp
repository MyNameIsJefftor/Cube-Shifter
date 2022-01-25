// Fill out your copyright notice in the Description page of Project Settings.


#include "SlideCube.h"

ASlideCube::ASlideCube()
{
	parent = CreateDefaultSubobject<USceneComponent>(TEXT("Parent"));
	RootComponent = parent;

	posCube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("posCube"));
	posCube->AttachTo(parent);

	negCube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("negCube"));
	negCube->AttachTo(parent);

	//MyTarget = CreateDefaultSubobject<UMoveMarker>(TEXT("Target"));
}

void ASlideCube::Shift()
{
	disable(posCube);
	disable(negCube);
	isPositve = !isPositve;
	return;
}

void ASlideCube::WorldStateChange(bool worldState)
{
	if (worldState)
		if (isPositve)
			enable(posCube);
		else
			disable(negCube);
	else
		if (isPositve)
			disable(posCube);
		else
			enable(negCube);
}

void ASlideCube::disable(UStaticMeshComponent* mesh)
{
	mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	mesh->SetVisibility(false);
}

void ASlideCube::enable(UStaticMeshComponent* mesh)
{
	mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	mesh->SetVisibility(true);
}

