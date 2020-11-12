// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenSideDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UOpenSideDoor : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UOpenSideDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);

private:

	float InitalYaw;
	float CurrentYaw;

	float DoorLastOpened = 0.f;

	UPROPERTY(EditAnywhere)
		float TargetYaw = 90.f;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate;

	UPROPERTY(EditAnywhere)
		AActor* ActorThatOpens;

	UPROPERTY(EditAnywhere)
		float DoorCloseDelay = 0.2f;

	UPROPERTY(EditAnywhere)
		float OpenSpeed = 25.f;

	UPROPERTY(EditAnywhere)
		float CloseSpeed = 45.f;
};