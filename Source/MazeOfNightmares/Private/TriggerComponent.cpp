// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"


UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

AActor* UTriggerComponent::GetAcceptableActor()
{
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);

	for (AActor* Actor : Actors)
	{
		if (Actor->ActorHasTag(AcceptableActorTag))
		{
			return Actor;
		}
	}

	return nullptr;
}

void UTriggerComponent::CheckOverlapping()
{
	AActor* Actor = GetAcceptableActor();
	if (Actor)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			APlayerController* PlayerController = World->GetFirstPlayerController();
			if (PlayerController)
			{
				UUserWidget* Screamer = CreateWidget(PlayerController, ScreamerClass);
				if (Screamer)
				{
					Screamer->AddToViewport();
					if (ScreamerSound)
					{
						UGameplayStatics::SpawnSoundAtLocation(this, ScreamerSound, Actor->GetActorLocation());

						//FTimerDelegate Delegate;
						//Delegate.BindUFunction(this, "DestroyActorComponents", Screamer, ScreamerSound);
						//GetWorld()->GetTimerManager().SetTimer(DestroyComponentTimer, Delegate, 5.f, false);
					}
				}
			}
		}
	}
}

void UTriggerComponent::DestroyActorComponents(UUserWidget* ScreamerParam, USoundBase* ScreamerSoundParam)
{
	ScreamerParam->RemoveFromViewport();
	ScreamerSoundParam->RemoveFromRoot();

	//GetOwner()->Destroy();
}