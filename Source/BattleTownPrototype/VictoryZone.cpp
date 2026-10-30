// Fill out your copyright notice in the Description page of Project Settings.

#include "VictoryZone.h"

// Added lines
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Engine/Engine.h"

// Sets default values
AVictoryZone::AVictoryZone()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;// initially true;

	// Added lines
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(SceneRoot);

	TriggerBox->SetCollisionProfileName(TEXT("Trigger"));
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerBox->SetGenerateOverlapEvents(true);

	TriggerBox->SetBoxExtent(FVector(180.f, 180.f, 120.f));
	TriggerBox->SetRelativeLocation(FVector(0.f, 0.f, 120.f));

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AVictoryZone::OnTriggerEntered);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AVictoryZone::OnTriggerExited);

}

// We have removed these
// Called when the game starts or when spawned
/*void AVictoryZone::BeginPlay()
{
	Super::BeginPlay();

}
// Called every frame
void AVictoryZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}*/

// Added lines
bool AVictoryZone::AreBothCharactersInside() const
{
	return CharacterAInside.IsValid() && CharacterBInside.IsValid();
}
bool AVictoryZone::HasOtherCharacterInside(const AActor* RequestingCharacter) const
{
	if (!RequestingCharacter)
	{
		return false;
	}
	else
	{
		if (RequestingCharacter->ActorHasTag(FName(TEXT("CharacterA"))))
		{
			return CharacterBInside.IsValid();
		}
		else
		{
			if (RequestingCharacter->ActorHasTag(FName(TEXT("CharacterB"))))
			{
				return CharacterAInside.IsValid();
			}
			else
			{
				return false; // The build up struggle because that one last case was missing
				// which could lead a potential unassignment of a value to the function
				// which cannot and isn't allowed in the build.
			}
		}
	}
}
void AVictoryZone::OnTriggerEntered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* Character = Cast<ACharacter>(OtherActor);
	if (!Character)
	{
		return;
	}
	if (Character->ActorHasTag(FName(TEXT("CharacterA"))))
	{
		CharacterAInside = Character;
		UE_LOG(LogTemp, Warning, TEXT("Character A entered Victory Zone"));
	}
	else if (Character->ActorHasTag(FName(TEXT("CharacterB"))))
	{
		CharacterBInside = Character;
		UE_LOG(LogTemp, Warning, TEXT("Character B entered Victory Zone"));
	}
	if (AreBothCharactersInside() && !bPuzzleCompleted)
	{
		bPuzzleCompleted = true;
		UE_LOG(LogTemp, Warning, TEXT("Puzzle Completed!"));
		if(GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 8.0f, FColor::Green, TEXT("Puzzle Completed!"));
		}
	}

}
void AVictoryZone::OnTriggerExited(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (CharacterAInside.Get() == OtherActor)
	{
		CharacterAInside.Reset();
	}
	if (CharacterBInside.Get() == OtherActor)
	{
		CharacterBInside.Reset();
	}
}
