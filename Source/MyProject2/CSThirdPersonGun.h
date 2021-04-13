// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSThirdPersonGun.generated.h"

class UStaticMeshComponent;

UCLASS()
class MYPROJECT2_API ACSThirdPersonGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACSThirdPersonGun();

protected:
	
	UPROPERTY(VisibleAnywhere)
    USceneComponent* SceneComp;
    	
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* MeshComp;

public:	

	UFUNCTION(BlueprintImplementableEvent)
	void OnFire();

};
