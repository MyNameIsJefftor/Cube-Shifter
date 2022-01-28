// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerButton.h"
#include "InteractableInterface.h"
#include "Components/SphereComponent.h"

// Sets default values
ATriggerButton::ATriggerButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Parent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Parent;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Comp"));
	CollisionComp->SetupAttachment(RootComponent);
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ATriggerButton::OnComponentBeginOverlap);
	CollisionComp->OnComponentEndOverlap.AddDynamic(this, &ATriggerButton::OnComponentEndOverlap);

	ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button"));
	ButtonMesh->SetupAttachment(CollisionComp);
}

void ATriggerButton::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		ButtonMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -10.0f));

		if (Interactable && Interactable.GetObject()->Implements<UInteractableInterface>())
			if (IInteractableInterface* i = Cast<IInteractableInterface>(Interactable.GetObject()))
				i->TurnOn();
	}
}

void ATriggerButton::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		ButtonMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

		if (Interactable && Interactable.GetObject()->Implements<UInteractableInterface>())
			if (IInteractableInterface* i = Cast<IInteractableInterface>(Interactable.GetObject()))
				i->TurnOff();
	}
}

// Called when the game starts or when spawned
void ATriggerButton::BeginPlay()
{
	Super::BeginPlay();

	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ATriggerButton::OnComponentBeginOverlap);
	CollisionComp->OnComponentEndOverlap.AddDynamic(this, &ATriggerButton::OnComponentEndOverlap);
	
}

// Called every frame
void ATriggerButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

