// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CSPlayer.generated.h"

class ACSGun;
class UCameraComponent;

UCLASS()
class MYPROJECT2_API ACSPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACSPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> GunClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCameraComponent* FPSCamera;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* FPSGunSocket;

	UPROPERTY(BlueprintReadOnly)
	ACSGun* EquippedGun;

	UPROPERTY(replicated)
	float Pitch;

protected:
	void HandleRightInput(float Value);
	void HandleForwardInput(float Value);
	void HandleShootInput();
	void HandleReloadInput();

};
