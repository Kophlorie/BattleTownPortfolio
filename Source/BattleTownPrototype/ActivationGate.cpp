// Fill out your copyright notice in the Description page of Project Settings.


#include "ActivationGate.h" // Initialy here

// Added inclusions
#include "Components/SceneCaptureComponent.h" // oh it's funny, it's like these classes were saved in Components
#include "Components/StaticMeshComponent.h" // Same as above
#include "Components/BoxComponent.h" // Same as above
#include "GameFramework/Character.h" // That's new, not connected to the ActivationGate.h

// In a second step for the puzzle
#include "PressurePlate.h"



// Sets default values
AActivationGate::AActivationGate()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true; // Initially here

	// Stationary root
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot")); // Added lines,named in the .h
	RootComponent = SceneRoot; // Added lines

	GateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GateMesh")); // Added lines,named in the .h
	GateMesh->SetupAttachment(SceneRoot); // Added lines
	// This line is modified in the third step

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox")); // Added lines,named in the .h
	TriggerBox->SetupAttachment(SceneRoot); // Added lines

	// AddDynamic() connects Unreal's overlap event to our C++ function. The UFUNCTION() macro makes the function eligible for this kind of binding
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AActivationGate::OnTriggerEntered); // Added line

	// These were put above the OnComponentBeginOverlap.AddDynamic line, 
	// but I moved them below because Copilot suggested it first
	// which may help to avoid potential issues 
	// with the trigger box not being properly initialized before setting its properties, apparently.
	TriggerBox->SetCollisionProfileName(TEXT("Trigger")); // Added line,not named in the .h
	TriggerBox->SetRelativeLocation(FVector(250.0f, 0.0f, 100.0f)); // Added line
	TriggerBox->SetBoxExtent(FVector(150.0f, 150.0f, 100.0f)); // Added line	

}

// Called when the game starts or when spawned
void AActivationGate::BeginPlay()
{
	Super::BeginPlay();

	// Save initial door root position/location
	ClosedPosition = GateMesh->GetRelativeLocation(); // Added line

}

// Added function 
void AActivationGate::OnTriggerEntered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// This was implemented in the very first step !
	//if (OtherActor && OtherActor != this && OtherComp) // it was suggested by copilot
	//{
		// ACharacter* PlayerCharacter = Cast<ACharacter>(OtherActor); // Suggested by copilot
		// if (PlayerCharacter) // same as above
		// Instead we do this,which I assume is a way to save memory
		// Cast<ACharacter>(OtherActor) checks whether the overlapping Actor is a Character. 
		// For now, any Character can open the gate; later, we can restrict it to the appropriate playable character.
	if (Cast<ACharacter>(OtherActor)) // Check if the overlapping actor is a player character
	{
		// We commented this trigger once we added the pressure plate triggering, so it can only open when both plates are pressed simultaneously. 
		// We can add this back in later if we want to allow the gate to open when facing the gate like in InteractiveGate. 
		bShouldOpen_i = true; // THis remains the same between the two versions
		// This is where I should work more, to be able to have a box where it can go up 
		// and down when I quit the triggering area
		// and then when the next action can only be triggered once the door is back in place,
		// so you don't have weird stuff as going up and rotating hmmm
		// for now, if it is set to true, the door should go up and then turn I guess if the other triggers are activated
		// hmmm I can make the test but it is VERY NOT recommanded
		// put it to false for safety all the while keeping it for safe measures
	}
	//}


}



// The forever function always here
// Called every frame: move toward the target angle
void AActivationGate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Check whether both pressure plates are exist/activated. If either is not activated, the gate should not open.
	//if (PlateA && PlateB) // Check if both pressure plates are valid/exist
	//{
		// Suggested by copilot
		// bShouldOpen = PlateA->IsActivated() && PlateB->IsActivated(); // Update bShouldOpen based on the activation state of both pressure plates

		// Both plates must be activated simultaneously for the gate to open
		/*if (PlateA->IsActivated() && PlateB->IsActivated())
		{
			bShouldOpen = true; // Both plates are activated, the gate should open
		}*/
		// Suggested by copilot (it really wants to have the else!)
		/*else
		{
			bShouldOpen = false; // At least one plate is not activated, the gate should not open
		}*/
	//}
	// Suggested by copilot
	/*else
	{
		bShouldOpen = false; // If either pressure plate is not valid, the gate should not open
	}*/

	// In the third step
	// Gate opens only while BOTH plates are active.
	bShouldOpen =
		PlateA &&
		PlateB &&
		PlateA->IsActivated() &&
		PlateB->IsActivated();
	// The closed position is our reference. // Was already here in the 1st version
	FVector TargetPosition = ClosedPosition; // Start with the closed position

	// Below is all added
	if (bShouldOpen)// (!bShouldOpen) previous version
	{
		//return; // previous version // If the gate should not open, exit the function early
		// In the thrid step we move the target position into this if condition
		TargetPosition.Z -= OpeningHeight; // Calculate the target position for the gate when opened
	}

	// When bShouldOpen is false, the target is
	// automatically the original closed position.

	
	// Smoothly interpolate the gate's position towards the target position
	// Notice that we don't need two movement functions. VInterpConstantTo() can interpolate in either direction.
	FVector NewPosition = FMath::VInterpConstantTo(GateMesh->GetRelativeLocation(), TargetPosition, DeltaTime, OpeningSpeed);

	// FMath::VInterpConstantTo() moves toward a target position at a constant rate without overshooting. 
	// With our values, the gate travels 300 cm at 150 cm/s, taking approximately two seconds to open.
	GateMesh->SetRelativeLocation(NewPosition); // Update the gate's position


}

