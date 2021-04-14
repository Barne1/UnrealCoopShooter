// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSGun.generated.h"

class USkeletalMeshComponent;
class UCameraComponent;
class UMaterialInterface;
class ACSThirdPersonGun;

UCLASS()
class MYPROJECT2_API ACSGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACSGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneComp;
	
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* MeshComp;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> ThirdPersonGunClass;

	//use this to prevent shooting or reloading during potential cutscenes, preventing friendly fire, etc.
	bool bAllowedActions = true;
	bool bReloading = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int MaxMagazineCount = 30;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int MaxAmmoCount = 210;

	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<ETraceTypeQuery> TraceChannel;

	UPROPERTY(EditDefaultsOnly)
	float TimeBetweenShots = 0.5f;

	float TimeUntilNextShot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int AmmoInMagazine = 30;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int SpareAmmo = 90;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int Damage = 40;

	void Fire(UCameraComponent* Cam);
	void BeginReload();
	void EndReload();
	
	//TODO: used for effects when firing
	UFUNCTION(BlueprintImplementableEvent)
	void OnFire();

	//TODO: used for click effect when out of ammo
	UFUNCTION(BlueprintImplementableEvent)
    void OnOutOfAmmo();

	ACSThirdPersonGun* TPSGun;

protected:
	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* BulletHoleDecalMaterial;
};
