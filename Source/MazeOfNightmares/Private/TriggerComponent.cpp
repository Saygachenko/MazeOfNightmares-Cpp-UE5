// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

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
				}
			}
		}
	}

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