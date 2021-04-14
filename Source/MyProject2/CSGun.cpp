// Fill out your copyright notice in the Description page of Project Settings.


#include "CSGun.h"


#include "CSPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Materials/MaterialInterface.h"
#include "CSEnemy.h"
#include "CSThirdPersonGun.h"

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
	if(bAllowedActions)
	{
		if(AmmoInMagazine > 0 && TimeUntilNextShot <= 0.f && !bReloading)
		{
			OnFire();
			
			if(TPSGun)
			{
				TPSGun->OnFire();
			}
			
			AmmoInMagazine--;

			FHitResult Hit;
			FVector Start = Cam->GetComponentLocation();
			FVector End = Start + (Cam->GetComponentRotation().Vector() * 10000);
			TArray<AActor*> ActorsToIgnore;
			ActorsToIgnore.Add(this);
			ActorsToIgnore.Add(GetOwner());
			
			if(UKismetSystemLibrary::LineTraceSingle(this, Start, End, TraceChannel, true, ActorsToIgnore, EDrawDebugTrace::None, Hit, true))
			{
				ACSEnemy* Enemy = Cast<ACSEnemy>(Hit.Actor);
				if(Enemy)
				{
					Enemy->TakeDamage(Damage);
				}
				else if(Hit.Actor->GetRootComponent()->Mobility != EComponentMobility::Movable)
				{
					UE_LOG(LogTemp, Log, TEXT("SPAWNING DECAL"));
					UGameplayStatics::SpawnDecalAtLocation(this, BulletHoleDecalMaterial, FVector(20.f), Hit.ImpactPoint, UKismetMathLibrary::MakeRotFromX(-Hit.ImpactNormal));
				}
			}
		}
		else
		{
			OnOutOfAmmo();
		}
	}
}

void ACSGun::BeginReload()
{
	if(bAllowedActions)
	{
		if(!bReloading && AmmoInMagazine < MaxMagazineCount && SpareAmmo > 0)
		{
			bReloading = true;
			//TODO: Add Timer and animation
			EndReload();
		}
	}
}

void ACSGun::EndReload()
{
	int AmmoNeeded = MaxMagazineCount - AmmoInMagazine;
	int AmmoTransferred = FMath::Min(AmmoNeeded, SpareAmmo);
	SpareAmmo -= AmmoTransferred;
	AmmoInMagazine += AmmoTransferred;
	bReloading = false;
}



