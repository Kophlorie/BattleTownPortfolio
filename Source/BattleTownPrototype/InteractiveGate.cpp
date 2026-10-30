// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveGate.h" // Initialy here

// Added inclusions
#include "Components/SceneCaptureComponent.h" // oh it's funny, it's like these classes were saved in Components
#include "Components/StaticMeshComponent.h" // Same as above
#include "Components/BoxComponent.h" // Same as above
#include "GameFramework/Character.h" // That's new not connected to the InteractiveGate.h

// In the third step for its conditional activation
#include "VictoryZone.h"

// Sets default values
AInteractiveGate::AInteractiveGate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true; // Initially here

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot")); // Added lines named in the .h
	RootComponent = SceneRoot; // Added lines

	GateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GateMesh")); // Added lines named in the .h
	GateMesh->SetupAttachment(SceneRoot); // Added lines

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox")); // Added lines named in the .h
	TriggerBox->SetupAttachment(SceneRoot); // Added lines

	// AddDynamic() connects Unreal's overlap event to our C++ function. The UFUNCTION() macro makes the function eligible for this kind of binding
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AInteractiveGate::OnTriggerEntered); // Added line

	// These were put above the OnComponentBeginOverlap.AddDynamic line, 
	// but I moved them below because Copilot suggested it first
	// which may help to avoid potential issues 
	// with the trigger box not being properly initialized before setting its properties apparently.
	TriggerBox->SetCollisionProfileName(TEXT("Trigger")); // Added line not named in the .h
	TriggerBox->SetRelativeLocation(FVector(250.0f, 0.0f, 100.0f)); // Added line
	TriggerBox->SetBoxExtent(FVector(150.0f, 150.0f, 100.0f)); // Added line
}

// Called when the game starts or when spawned
void AInteractiveGate::BeginPlay()
{
	Super::BeginPlay();

	ClosedPosition = GateMesh->GetRelativeLocation(); // Added line
	
}

// Added function
void AInteractiveGate::OnTriggerEntered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//if (OtherActor && OtherActor != this && OtherComp) // it was suggested by copilot
	//{
		// ACharacter* PlayerCharacter = Cast<ACharacter>(OtherActor); // Suggested by copilot
		// if (PlayerCharacter) // same as above
		// Instead we do this, which I assume is a way to save memory
		// Cast<ACharacter>(OtherActor) checks whether the overlapping Actor is a Character. 
		// For now, any Character can open the gate; later, we can restrict it to the appropriate playable character.
		if ((!ActivatePuzzle && Cast<ACharacter>(OtherActor)) //(Cast<ACharacter>(OtherActor)) Check if the overlapping actor is a player character
			|| (ActivatePuzzle && (VictoryZone->HasOtherCharacterInside(OtherActor))) // VictoryZone &&
			)
		{
			bShouldOpen = true; // THis remains the same between the two versions

			// Added in the third step
			UE_LOG(LogTemp, Warning, TEXT("Interactive Gate unlocked by %s"), *OtherActor->GetActorNameOrLabel());

		}
	//}
}

// Called every frame
void AInteractiveGate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Below is all added
	if (!bShouldOpen)
	{
		return; // If the gate should not open, exit the function early
	}

	FVector TargetPosition = ClosedPosition; // Start with the closed position
	TargetPosition.Z += OpeningHeight; // Calculate the target position for the gate when opened

	// Smoothly interpolate the gate's position towards the target position
	FVector NewPosition = FMath::VInterpConstantTo(GateMesh->GetRelativeLocation(), TargetPosition, DeltaTime, OpeningSpeed);
	// FMath::VInterpConstantTo() moves toward a target position at a constant rate without overshooting. 
	// With our values, the gate travels 300 cm at 150 cm/s, taking approximately two seconds to open.
	GateMesh->SetRelativeLocation(NewPosition); // Update the gate's position
}

