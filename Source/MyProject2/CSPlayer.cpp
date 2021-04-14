// Fill out your copyright notice in the Description page of Project Settings.


#include "CSPlayer.h"

#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "CSGun.h"
#include "Engine/Engine.h"
#include "CSThirdPersonGun.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ACSPlayer::ACSPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->SetOwnerNoSee(true);

	FPSCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FPS Camera"));
	FPSCamera->SetupAttachment(RootComponent);
	FPSCamera->SetRelativeLocation(FVector(0.f, 0.f, BaseEyeHeight));
	FPSCamera->bUsePawnControlRotation = true;

	FPSGunSocket = CreateDefaultSubobject<USceneComponent>(TEXT("FPS Gun Socket"));
	FPSGunSocket->SetupAttachment(FPSCamera);

	this->bReplicates = true;
}

// Called when the game starts or when spawned
void ACSPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	AActor* FPSGun = GetWorld()->SpawnActor(GunClass, &GetTransform(), SpawnParameters);
	ACSGun* temp = Cast<ACSGun>(FPSGun);
	if(!temp)
	{
		UE_LOG(LogTemp, Warning, TEXT("No gun equipped! Casting failed in ACSPlayer::BeginPlay()"));
		return;
		
	}

	EquippedGun = temp;
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	FPSGun->AttachToComponent(FPSGunSocket, AttachmentRules);

	AActor* TPSGun = GetWorld()->SpawnActor(EquippedGun->ThirdPersonGunClass, &GetTransform(), SpawnParameters);
	TPSGun->AttachToComponent(GetMesh(), AttachmentRules, "GunSocket");
	ACSThirdPersonGun* TPSGunTemp = Cast<ACSThirdPersonGun>(TPSGun);
	EquippedGun->TPSGun = TPSGunTemp;
	
}

// Called every frame
void ACSPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Pitch = -GetControlRotation().Pitch;
}

// Called to bind functionality to input
void ACSPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Forward", this, &ACSPlayer::HandleForwardInput);
	PlayerInputComponent->BindAxis("Right", this, &ACSPlayer::HandleRightInput);
	PlayerInputComponent->BindAxis("LookPitch", this, &ACSPlayer::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookYaw", this, &ACSPlayer::AddControllerYawInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACSPlayer::Jump);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &ACSPlayer::HandleShootInput);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &ACSPlayer::HandleReloadInput);
}

void ACSPlayer::HandleRightInput(float Value)
{
	AddMovementInput(GetActorRightVector() * Value);
}

void ACSPlayer::HandleForwardInput(float Value)
{
	AddMovementInput(GetActorForwardVector() * Value);
}

void ACSPlayer::HandleShootInput()
{
	if(EquippedGun)
	{
		EquippedGun->Fire(FPSCamera);
	}
}

void ACSPlayer::HandleReloadInput()
{
	if(EquippedGun)
	{
		EquippedGun->BeginReload();
	}
}

void ACSPlayer::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
    DOREPLIFETIME(float, Pitch);
}

