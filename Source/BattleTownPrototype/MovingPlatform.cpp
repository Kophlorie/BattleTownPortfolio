// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"
// Adding another element from existing libraries
#include "Components/StaticMeshComponent.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Adding a new element here
	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
	// PlatformMesh is the only new element not in the basic libraries

	// Adding the new root element that is the PlatformMesh
	RootComponent = PlatformMesh;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	// Ading a new element here too: only elements already in the libraries
	InitialLocation = GetActorLocation();
	
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); // Tick() updates the elapsed time and computes a new position.

	// Adding new elements - typically the equation for the movement
	
	// The 1st movement was only an up and down movement
	//ElapsedTime += DeltaTime; // Only elements from the library so far
							 // Although ElpsedTime has been newly declared in the .h
	
	// The 2nd movement is a up-left-right-down movement + for some
	PhaseTime += DeltaTime * Speed;

	// Each phase lasts PI/2 units of scaled time
	// I cannot comment it as it is the whole base of unlocking the vertical movement.
	// Without it, it goes just up and down.
	// if (PhaseTime >= PI / 2.0f)
	// Your current if only advances one phase per frame.If the game freezes momentarily or Speed is very high, 
	// the phase clock might advance by more than one phase duration. So you put instead:
	while (PhaseTime >= PI / 2.0f)
	{
		PhaseTime -= PI / 2.0f;
		Phase = (Phase + 1) % 8;
	}
	// The distinction between if and while is how many times the condition is checked and the operation repeated.

	// Smooth movement from 0 to 1
	float Alpha = FMath::Sin(PhaseTime);
	Alpha *= Alpha; // This gives zero velocity at both ends of each phase. For a smoother motion:
	// without this Alpha *= Alpha line, The code above uses sin(PhaseTime) over each quarter-cycle, 
	// but during the horizontal return and downward movement, this produces an abrupt velocity change 
	// at the phase boundaries, although the position remains continuous.

	// These two lines are aslo the same as writting directly: Alpha = FMath::Square(FMath::Sin(t * PI / 2));
	// Other options are: Alpha = t; (constant speed) 
	// or Alpha = t*t*t*(t*(t*6 - 15) + 10); Zero velocity and zero acceleration at the endpoints. Useful when you want gentler transitions.
	// Basically, you always need to compute the derivatives and their values at the endpoints to see if they are zero or not, and so
	// if you need to smoothen the movement or not. 1st derivative is  the velocity and 2nd derivative is the acceleration, respectively.


	FVector NewLocation = InitialLocation; // NewLocation is a new element

	// The 1st movement We are loading the sin equation from the FMath library gg 
	// I am not sure where/why Amplitude comes from though
	//NewLocation.Z += Amplitude * FMath::Sin(Speed * ElapsedTime); // Sin ou Cos comes back to the same movement


	// The 2nd movement
	switch (Phase)
	{
	case 0: // Move up
		NewLocation.Z += ZAmplitude * Alpha;
		break;

	case 1: // Move left
		NewLocation.Z += ZAmplitude;
		NewLocation.X -= XAmplitude * Alpha;
		break;

	case 2: // Return horizontally
		NewLocation.Z += ZAmplitude;
		NewLocation.X -= XAmplitude * (1.0f - Alpha);
		break;

	case 3: // Move up
		NewLocation.Z += ZAmplitude * (1.0f + Alpha);
		break;

	case 4: // Move down
		NewLocation.Z += ZAmplitude * (2.0f - Alpha);
		break;

	case 5: // Move left
		NewLocation.Z += ZAmplitude;
		NewLocation.X -= XAmplitude * Alpha;
		break;

	case 6: // Return horizontally
		NewLocation.Z += ZAmplitude;
		NewLocation.X -= XAmplitude * (1.0f - Alpha);
		break;

	case 7: // Move down
		NewLocation.Z += ZAmplitude * (1.0f - Alpha);
		break;
	}

	// Same no matter the selected movement
	SetActorLocation(NewLocation); // Fair enough, we move our element after computing the new position


}

