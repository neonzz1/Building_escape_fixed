//© Neonzz Games © 2020

#include "GrabberComponent.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

#define OUT
// Sets default values for this component's properties
UGrabberComponent::UGrabberComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UGrabberComponent::FindPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	//Is there a handle?
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("No Physics handle! on: %s"), *GetOwner()->GetName())
	}

}

void UGrabberComponent::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandle();
	
	SetupInputComponent();
}

void UGrabberComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PhysicsHandle) { return; }
	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(GetPlayerReach());
	}

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		GetPlayerReach(),
		FColor(0, 255, 0),
		false,
		0.f,
		0,
		5.f
	);
}

FVector UGrabberComponent::GetPlayerReach() const
{
	// Get players viewpoint
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);
 

	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

}

FVector UGrabberComponent::GetPlayerWorldPos() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	return PlayerViewPointLocation;

}

void UGrabberComponent::SetupInputComponent()
{
	//Bind input made in unreal
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabberComponent::Grab);

	InputComponent->BindAction("Drop", IE_Released, this, &UGrabberComponent::Release);

// Called when the game starts

}

FHitResult UGrabberComponent::GetFirstPhysicsBodyInReach() const
{
	FHitResult Hit;
	// Ray-cast out to a certain distance (Reach)
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		GetPlayerWorldPos(),
		GetPlayerReach(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	// See what it hits
	AActor* ActorHit = Hit.GetActor();

	if (ActorHit)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Line trace has hit: %s"), *(ActorHit->GetName()));
	}

	return Hit;

}

void UGrabberComponent::Grab()
{
	FHitResult HitResult = GetFirstPhysicsBodyInReach();

	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();

	AActor* ActorHit = HitResult.GetActor();

	if (ActorHit)
	{
		if (!PhysicsHandle) { return; }
		PhysicsHandle->GrabComponentAtLocation
		(
		ComponentToGrab,
		NAME_None,
		GetPlayerReach()
		);
	}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Help! Couldn't grab!!"));
		}
	
}
void UGrabberComponent::Release()
{
	if (!PhysicsHandle) { return; }
	PhysicsHandle->ReleaseComponent();
}


