// Fill out your copyright notice in the Description page of Project Settings.


#include "SlipperySlope.h"
#include "CubeShifterCharacter.h"


ASlipperySlope::ASlipperySlope()
{
	parent = CreateDefaultSubobject<USceneComponent>(TEXT("Parent"));
	RootComponent = parent;

	posCube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("posCube"));
	posCube->SetupAttachment(parent);

	posBox = CreateDefaultSubobject<UBoxComponent>(TEXT("posBox"));
	posBox->SetupAttachment(posCube);
	posBox->OnComponentBeginOverlap.AddDynamic(this, &ASlipperySlope::OnBeginOverlap);
	posBox->OnComponentEndOverlap.AddDynamic(this, &ASlipperySlope::OnEndOverlap);

	negCube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("negCube"));
	negCube->SetupAttachment(parent);

	negBox = CreateDefaultSubobject<UBoxComponent>(TEXT("negBox"));
	negBox->SetupAttachment(negCube);
	negBox->OnComponentBeginOverlap.AddDynamic(this, &ASlipperySlope::OnBeginOverlap);
	negBox->OnComponentEndOverlap.AddDynamic(this, &ASlipperySlope::OnEndOverlap);

	posSlippery = false;
}

void ASlipperySlope::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == this || !OtherActor->IsA<ACubeShifterCharacter>()) return;
	ACubeShifterCharacter* player = CastChecked<ACubeShifterCharacter, AActor>(OtherActor);
	if (posSlippery == PositiveState) {
		player->SlipperyFloor(true);
	}
}

void ASlipperySlope::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == this || !OtherActor->IsA<ACubeShifterCharacter>()) return;
	ACubeShifterCharacter* player = CastChecked<ACubeShifterCharacter, AActor>(OtherActor);
	player->SlipperyFloor(false);
}

void ASlipperySlope::Shift()
{
	Disable(posCube);
	Disable(negCube);
	Disable(posBox);
	Disable(negBox);
	PositiveState = !PositiveState;
	return;
}

void ASlipperySlope::WorldStateChange(bool worldState)
{
	if (worldState) 
	{
		if (PositiveState)
		{
			Enable(posCube);
			Enable(posBox);
		}
		else 
		{
			Disable(negCube);
			Disable(negBox);
		}
	}
	else 
	{
		if (PositiveState) 
		{
			Disable(posCube);
			Disable(posBox);
		}
		else 
		{
			Enable(negCube);
			Enable(negBox);
		}
	}
}

bool ASlipperySlope::Disable(USceneComponent* comp)
{
	if (comp->IsA<UStaticMeshComponent>())
	{
		CastChecked<UStaticMeshComponent>(comp)->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		CastChecked<UStaticMeshComponent>(comp)->SetVisibility(false);
	}
	else if (comp->IsA<UBoxComponent>())
	{
		CastChecked<UBoxComponent>(comp)->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	return true;
}

bool ASlipperySlope::Enable(USceneComponent* comp)
{
	if (comp->IsA<UStaticMeshComponent>())
	{
		CastChecked<UStaticMeshComponent>(comp)->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		CastChecked<UStaticMeshComponent>(comp)->SetVisibility(true);
	}
	else if (comp->IsA<UBoxComponent>())
	{
		CastChecked<UBoxComponent>(comp)->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
	return true;
}

void ASlipperySlope::BeginPlay()
{
	Super::BeginPlay();

	if (!PositiveState) Shift();
	else Disable(negCube);
}