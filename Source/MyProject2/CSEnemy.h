// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CSEnemy.generated.h"

UCLASS()
class MYPROJECT2_API ACSEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACSEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnTakeDamage();

	UFUNCTION(BlueprintImplementableEvent)
    void OnDeath();

	int Hp = 100;

public:
	void TakeDamage(int Damage);

	UFUNCTION(BlueprintCallable)
	bool IsDead() {return Hp <= 0;}

	UPROPERTY(BlueprintReadWrite)
	bool bTookDamage;
};
