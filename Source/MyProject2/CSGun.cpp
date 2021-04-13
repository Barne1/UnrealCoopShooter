// Fill out your copyright notice in the Description page of Project Settings.


#include "CSGun.h"

#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ACSGun::ACSGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Handle"));
	RootComponent = SceneComp;
	
	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	MeshComp->SetupAttachment(RootComponent);

	MeshComp->SetOnlyOwnerSee(true);
	MeshComp->CastShadow = false;
}

// Called when the game starts or when spawned
void ACSGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACSGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(TimeUntilNextShot > 0.f)
		TimeUntilNextShot -= DeltaTime;
}

void ACSGun::Fire(UCameraComponent* Cam)
{
	if(bAllowedToFire)
	{
		if(AmmoInMagazine > 0 && TimeUntilNextShot <= 0.f)
		{
			AmmoInMagazine--;

			FHitResult Hit;
			FVector Start = Cam->GetComponentLocation();
			FVector End = Start + (Cam->GetComponentRotation().Vector() * 10000);
			TArray<AActor*> ActorsToIgnore;
			ActorsToIgnore.Add(this);
			ActorsToIgnore.Add(GetOwner());
			
			UKismetSystemLibrary::LineTraceSingle(this, Start, End, TraceChannel, true, ActorsToIgnore, EDrawDebugTrace::Persistent, Hit, true);
			
			OnFire();
		}
		else
		{
			OnOutOfAmmo();
		}
	}
}



