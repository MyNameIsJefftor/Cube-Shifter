// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelDoor.h"
#include "Components/BoxComponent.h"

// Sets default values
ALevelDoor::ALevelDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	if (!Parent)
		Parent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Parent;

	if (!DoorMesh)
		DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	DoorMesh->SetupAttachment(RootComponent);
	DoorMesh->BodyInstance.SetCollisionProfileName("NoCollision");
	DoorMesh->bRenderCustomDepth = true;

	if (!CollisionComp)
		CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	CollisionComp->SetupAttachment(DoorMesh);
	CollisionComp->BodyInstance.SetCollisionProfileName("BlockAllDynamic");

	if (!DoorFrameMesh)
		DoorFrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Frame"));
	DoorFrameMesh->SetupAttachment(RootComponent);
	DoorFrameMesh->BodyInstance.SetCollisionProfileName("BlockAllDynamic");
	DoorFrameMesh->bRenderCustomDepth = true;

}

bool ALevelDoor::OpenDoor()
{
	const FRotator rot(0.0f, -90.0f, 0.0f);
	DoorMesh->SetRelativeRotation(rot.Quaternion());

	return (DoorMesh->GetRelativeRotation() == rot);
}

bool ALevelDoor::CloseDoor()
{
	const FRotator rot(0.0f, 0.0f, 0.0f);
	DoorMesh->SetRelativeRotation(rot.Quaternion());

	return (DoorMesh->GetRelativeRotation() == rot);
}

bool ALevelDoor::TurnOn()
{
	return OpenDoor();
}

bool ALevelDoor::TurnOff()
{
	return CloseDoor();
}

// Called when the game starts or when spawned
void ALevelDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

