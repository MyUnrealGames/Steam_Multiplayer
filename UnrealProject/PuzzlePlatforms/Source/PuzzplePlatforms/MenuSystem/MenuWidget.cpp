// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuWidget.h"
#include "Engine/World.h"


bool UMenuWidget::Setup()
{
	this->AddToViewport();

	APlayerController* Controller = GetWorld()->GetFirstPlayerController();
	if (!ensure(Controller != nullptr)) return false;

	FInputModeUIOnly InputMode;
	InputMode.SetWidgetToFocus(this->TakeWidget());
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	Controller->SetInputMode(InputMode);
	Controller->bShowMouseCursor = true;
	return true;
}

void UMenuWidget::Teardown()
{
	this->RemoveFromViewport();

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	FInputModeGameOnly InputModeData;
	PlayerController->SetInputMode(InputModeData);

	PlayerController->bShowMouseCursor = false;
}


void UMenuWidget::OnLevelRemovedFromWorld(ULevel * InLevel, UWorld * InWorld)
{
	Super::OnLevelRemovedFromWorld(InLevel, InWorld);

	this->Teardown();
}

void UMenuWidget::SetMenuInterface(IMenuInterface* MenuInterface)
{
	this->MenuInterface = MenuInterface;
}