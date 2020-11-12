// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	void FindPressurePlate();
	void FindAudioComponent();

	float TotalMassOfActors() const;

	bool OpenDoorSound = false;
	bool CloseDoorSound = true;


private:

	float InitalYaw;
	float CurrentYaw;
	float DoorLastOpened = 0.f;
	
	UPROPERTY(EditAnywhere)
	float MassThatOpens = 50.f;

	UPROPERTY(EditAnywhere)
	float TargetYaw = 90.f;	

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 0.2f;

	UPROPERTY(EditAnywhere)
	float OpenSpeed = 25.f;

	UPROPERTY(EditAnywhere)
	float CloseSpeed = 45.f;

	UPROPERTY()
	UAudioComponent* AudioComponent = nullptr;
};
