// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelDoor.h"
#include "Components/BoxComponent.h"

// Sets default values
ALevelDoor::ALevelDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Parent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Parent;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	DoorMesh->SetupAttachment(RootComponent);

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	CollisionComp->SetupAttachment(DoorMesh);

	DoorFrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Frame"));
	DoorFrameMesh->SetupAttachment(RootComponent);

}

bool ALevelDoor::TurnOn()
{
	const FRotator rot(0.0f, -90.0f, 0.0f);
	DoorMesh->SetRelativeRotation(rot.Quaternion());

	return (DoorMesh->GetRelativeRotation() == rot);
}

bool ALevelDoor::TurnOff()
{
	const FRotator rot(0.0f, 0.0f, 0.0f);
	DoorMesh->SetRelativeRotation(rot.Quaternion());

	return (DoorMesh->GetRelativeRotation() == rot);
}

// Called when the game starts or when spawned
void ALevelDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevelDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

