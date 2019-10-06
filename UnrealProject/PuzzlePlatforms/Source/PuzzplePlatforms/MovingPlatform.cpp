// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}

	
	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
}

void AMovingPlatform::AddActiveTrigger()
{
	++ActiveTriggers;
}

void AMovingPlatform::RemoveActiveTrigger()
{
	if (ActiveTriggers > 0) 
	{
		--ActiveTriggers;
	}
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (ActiveTriggers > 0)
	{
		if (HasAuthority())
		{
			FVector CurrentLocation = GetActorLocation();

			float JourneyLength = (GlobalTargetLocation - GlobalStartLocation).Size();
			float JourneyTravelled = (CurrentLocation - GlobalStartLocation).Size();

			if (JourneyTravelled >= JourneyLength)
			{
				Swap(GlobalStartLocation, GlobalTargetLocation);
			}
			FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
			CurrentLocation += (Direction * Speed * DeltaTime);
			SetActorLocation(CurrentLocation);

		}
	}
	

}

