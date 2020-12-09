// Fill out your copyright notice in the Description page of Project Settings.


#include "testchar.h"

// Sets default values
Atestchar::Atestchar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void Atestchar::BeginPlay()
{
	Super::BeginPlay();

	GrabberComponent = GetOwner()->FindComponentByClass<UGrabberComponent>();
	if (!GrabberComponent) {
		UE_LOG(LogTemp, Error, TEXT("No Grabber"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Grabber"));
	}

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	//Is there a handle?
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("No Physics handle! on: %s"), *GetOwner()->GetName());
	}
}

// Called every frame
void Atestchar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void Atestchar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

