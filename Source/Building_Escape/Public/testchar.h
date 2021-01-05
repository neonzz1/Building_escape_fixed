// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GrabberComponent.h"
#include "testchar.generated.h"

UCLASS()
class BUILDING_ESCAPE_API Atestchar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	Atestchar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	//Custom grabber
	UPROPERTY()
	UGrabberComponent* GrabberComponent = nullptr;

	UPROPERTY()
	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	void SetupInputComponent();

	void MoveRight();

	void MoveForward();

	FVector GetPlayerWorldPos();

};
