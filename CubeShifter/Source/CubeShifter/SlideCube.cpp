// Fill out your copyright notice in the Description page of Project Settings.


#include "SlideCube.h"

ASlideCube::ASlideCube()
{
	parent = CreateDefaultSubobject<USceneComponent>(TEXT("Parent"));
	RootComponent = parent;

	WhiteCube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WhiteCube"));
	WhiteCube->AttachTo(parent);

	BlackCube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlackCube"));
	BlackCube->AttachTo(parent);

	//MyTarget = CreateDefaultSubobject<UMoveMarker>(TEXT("Target"));
}

void ASlideCube::Shift()
{
	switch (IsWhite) {
	case true:
		disable(WhiteCube);
		enable(BlackCube);
		break;
	case false:
		disable(BlackCube);
		enable(WhiteCube);
		break;
	}
	IsWhite = !IsWhite;
	return;
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

