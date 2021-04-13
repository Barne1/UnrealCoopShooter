// Fill out your copyright notice in the Description page of Project Settings.


#include "CSThirdPersonGun.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ACSThirdPersonGun::ACSThirdPersonGun()
{
	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Handle"));
	RootComponent = SceneComp;
	
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComp->SetupAttachment(RootComponent);

	MeshComp->SetOwnerNoSee(true);
}

