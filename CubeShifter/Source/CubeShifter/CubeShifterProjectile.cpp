// Copyright Epic Games, Inc. All Rights Reserved.

#include "CubeShifterProjectile.h"
#include "Shiftable.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleEmitter.h"
#include "Kismet/GameplayStatics.h"
#include "MasterShifter.h"

ACubeShifterProjectile::ACubeShifterProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &ACubeShifterProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	MeshComp->SetupAttachment(RootComponent);
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;

	DynamicMat = nullptr;
}

void ACubeShifterProjectile::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> MasterShifters;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMasterShifter::StaticClass(), MasterShifters);

	if (MasterShifters[0] && !Cast<AMasterShifter>(MasterShifters[0])->GetPositiveState()) 
		ShiftMaterial();
}

void ACubeShifterProjectile::ShiftMaterial()
{
	// Get Material for Orb in Mesh
	if (!DynamicMat)
	{
		// Make new Dynamic Material instance for Core material
		if (UMaterialInterface* Material = MeshComp->GetMaterial(0))
		{
			DynamicMat = UMaterialInstanceDynamic::Create(Material, this);

			MeshComp->SetMaterial(0, DynamicMat);
		}
	}

	FLinearColor coreColor;
	DynamicMat->GetVectorParameterValue(TEXT("EmissiveColor"), coreColor);

	const FLinearColor White(0.875f, 0.875f, 0.875f, 1.0f);
	const FLinearColor Black(0.04f, 0.04f, 0.04f, 1.0f);

	// if face is white
	if (coreColor.R > 0.5f)
		// Change face to Black
		DynamicMat->SetVectorParameterValue(TEXT("EmissiveColor"), Black);
	else
		// Change face to White
		DynamicMat->SetVectorParameterValue(TEXT("EmissiveColor"), White);
}

void ACubeShifterProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != nullptr) && OtherActor != this && OtherActor->IsA<AShiftable>()) {
		
		AShiftable* shiftable = Cast<AShiftable>(OtherActor);
		shiftable->Shift();

		// Color Shifting Code
		if (!shiftable->IsA<AMasterShifter>()) // could replace with tag check instead in future
		{
			UParticleSystemComponent* PSC = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), WarpEffect, Hit.GetComponent()->GetComponentLocation());
			
			const FLinearColor White(0.875f, 0.875f, 0.875f, 1.0f);
			const FLinearColor Black(0.04f, 0.04f, 0.04f, 1.0f);
			
			if (!shiftable->GetPositiveState())
				PSC->SetColorParameter("Color", Black);
			else
				PSC->SetColorParameter("Color", White);
		}
	}

	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
	}

	Destroy();
}