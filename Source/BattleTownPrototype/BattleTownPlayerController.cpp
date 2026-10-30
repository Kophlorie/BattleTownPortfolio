// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTownPlayerController.h"

// From now on, anything below this line is completely new

#include "GameFramework/Character.h"
#include "Components/InputComponent.h"

// Added in a second step
#include "Kismet/GameplayStatics.h"

// Function to switch between CharacterA and CharacterB
// It was fully proposed by copilot and coherent with the tuto OoO
void ABattleTownPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Bind the SwitchCharacter function to the "SwitchCharacter" input action
	InputComponent->BindAction("SwitchCharacter", IE_Pressed, this, &ABattleTownPlayerController::SwitchCharacter);
}

void ABattleTownPlayerController::SwitchCharacter()
{
	// Check if CharacterA and CharacterB are valid
	//if (CharacterA && CharacterB)
	if (!CharacterA || !CharacterB)
	{
		UE_LOG(LogTemp, Warning,TEXT("Character references are missing!"));
		return;
	}


	// The distinction between APawn* and TObjectPtr<APawn>  
	// comes down to whether we're storing a reference as part of an Unreal object's state 
	// or simply using it temporarily inside a function.
	// Here: A traditional C++ pointer: APawn*
	APawn* CurrentPawn = GetPawn();
	// APawn is the type of object.
	// *indicates a pointer.
	// GetPawn() returns a pointer to the currently possessed Pawn; 
	// GetPawn() returns a raw APawn*, so using that type directly is natural.
	// CurrentPawn is a local variable, existing only while SwitchCharacter() executes.
	// We don't need Unreal's garbage collector to track this local pointer because we're using it immediately.



	// Get the currently possessed character
	if (CurrentPawn == CharacterA)
	{
		// Commented was proposed by Copilot
		// Get the currently possessed character
		//ACharacter* CurrentCharacter = Cast<ACharacter>(GetPawn());
		// Switch to the other character
		//if (CurrentCharacter == CharacterA)
		//{
			Possess(CharacterB);
	}
	else if (CurrentPawn == CharacterB)
	{
			Possess(CharacterA); // Since ACharacter inherits from APawn, comparing these references is valid.
			// Possess() already handles switching away from the currently possessed Pawn.
			// Calling UnPossess() separately is unnecessary here.
	} 
}

// Added in a second step
void ABattleTownPlayerController::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> FoundA;
	TArray<AActor*> FoundB;

	// At game start, find the Actor tagged CharacterA + Store its reference to FoundA.
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("CharacterA"), FoundA);
	// and Find the Actor tagged CharacterB + Store its reference to FoundB.
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("CharacterB"), FoundB);

	// Use those references when Tab is pressed.
	if (FoundA.Num() > 0)
	{
		CharacterA = Cast<ACharacter>(FoundA[0]);
	}

	if (FoundB.Num() > 0)
	{
		CharacterB = Cast<ACharacter>(FoundB[0]);
	}
}