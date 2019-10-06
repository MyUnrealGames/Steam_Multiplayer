// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "Engine/World.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"


bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(HostButton != nullptr)) return false;
	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

	if (!ensure(JoinButton != nullptr)) return false;
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);

	if (!ensure(QuitButton != nullptr)) return false;
	QuitButton->OnClicked.AddDynamic(this, &UMainMenu::QuitGame);

	if (ensure(CancelJoinMenuButton != nullptr)) {
		CancelJoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);
	}
	
	if (ensure(ConfirmJoinMenuButton != nullptr)) {
		ConfirmJoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);
	}


	bool SetupResult = Setup();

	return SetupResult;
}

void UMainMenu::HostServer()
{
	if (ensure(MenuInterface != nullptr))
	{
		MenuInterface->Host();
	}
}


void UMainMenu::OpenJoinMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(JoinMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(this->JoinMenu);
}

void UMainMenu::QuitGame()
{
	if (!ensure(MenuInterface != nullptr)) return;
	MenuInterface->Quit();
}

void UMainMenu::JoinServer()
{
	if (!ensure(IPAddressField != nullptr)) return;
	FString IPAddressValue = IPAddressField->GetText().ToString();
	if (!ensure(MenuInterface != nullptr)) return;
	MenuInterface->Join(IPAddressValue);
}

void UMainMenu::OpenMainMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	MenuSwitcher->SetActiveWidget(this->MainMenu);
}
