// Fill out your copyright notice in the Description page of Project Settings.


#include "PressurePlate.h"

// Added lines
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

// Added for the second step
#include "GameFramework/Character.h"

// Sets default values
APressurePlate::APressurePlate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; // previously true;
	// Unlike our MovingPlatform, the pressure plate doesn't need to update its position every frame.
	// Eventually, its activation will depend on collision events.
	// This is an example of choosing event driven logic rather than continuous polling.

	PlateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlateMesh"));
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));

	RootComponent = PlateMesh;

	TriggerBox->SetupAttachment(RootComponent);

	TriggerBox->SetCollisionProfileName(TEXT("Trigger"));

	TriggerBox->SetBoxExtent(FVector(100.0f, 100.0f, 50.0f)); // Position the TriggerBox above the mesh
	TriggerBox->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f)); 
	// The trigger extends 50 Unreal units above and below its centre, 
	// so its initial volume spans approximately 0–100 units above the plate's local origin.
	// That allows it to detect the lower part of a standing character.


	// Adding now as a second step the three elements that will allow the TriggerBox to detect overlaps with other Actors.
	TriggerBox->SetGenerateOverlapEvents(true);

	// AddDynamic registers one of our C++ member functions as a callback for an Unreal event.
	// We don't need to check every frame whether a character is standing on the plate.
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &APressurePlate::OnTriggerEntered);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &APressurePlate::OnTriggerExited);
}

// Called when the game starts or when spawned
/*void APressurePlate::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APressurePlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}*/

// Added functions
bool APressurePlate::IsActivated() const
{
	return bIsActivated;
}

// Now adding as a second step the OnTriggerEntered and OnTriggerExited functions. 
// These will be called when an Actor enters or exits the TriggerBox's volume.
// Copilot could determine the function signatures from the UFUNCTION() declarations in the header file
void APressurePlate::OnTriggerEntered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check if the overlapping actor is a player character
	if (Cast<ACharacter>(OtherActor))
	{
		bIsActivated = true;

		// Version 1 UE_LOG(LogTemp, Warning, TEXT("Pressure plate ACTIVATED"));
		// Version 2: without the first *GetName() to have two variations of the log message
		UE_LOG(LogTemp, Warning, TEXT("Pressure plate ACTIVATED by %s"), *OtherActor->GetName()); // is suggested by copilot
	}
}

// Copilot could determine the function signatures from the UFUNCTION() declarations in the header file
void APressurePlate::OnTriggerExited(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Check if the overlapping actor is a player character
	if (Cast<ACharacter>(OtherActor))
	{
		bIsActivated = false;
		// Version 1: UE_LOG(LogTemp, Warning, TEXT("Pressure plate DEACTIVATED));
		// Version 2: UE_LOG(LogTemp, Warning, TEXT("%s Pressure plate DEACTIVATED by %s"),*GetName(), *OtherActor->GetName()); 
		UE_LOG(LogTemp, Warning, TEXT("%s Pressure plate DEACTIVATED  by %s"), *GetActorNameOrLabel(), *OtherActor->GetActorNameOrLabel());
	}
}