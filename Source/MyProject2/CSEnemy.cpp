// Fill out your copyright notice in the Description page of Project Settings.


#include "CSEnemy.h"

// Sets default values
ACSEnemy::ACSEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACSEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACSEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACSEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACSEnemy::TakeDamage(int Damage)
{
	if(Hp > 0)
	{
		OnTakeDamage();
		bTookDamage = true;
		Hp -= Damage;
		if(Hp <= 0)
		{
			OnDeath();
		}
	}
	
}

