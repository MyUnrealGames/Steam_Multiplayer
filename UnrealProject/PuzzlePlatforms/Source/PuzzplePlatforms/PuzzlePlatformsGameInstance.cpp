// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformsGameInstance.h"

#include "GameFramework/PlayerController.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "OnlineSubsystem.h"
#include "PlatformTrigger.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem/MainMenu.h" 
#include "MenuSystem/InGameMenu.h"
#include "MenuSystem/MenuWidget.h"



UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer & ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> MainMenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if (!ensure(MainMenuBPClass.Class != nullptr)) return;
	MenuClass = MainMenuBPClass.Class;

	ConstructorHelpers::FClassFinder<UUserWidget> InGameMenuBPClass(TEXT("/Game/MenuSystem/WBP_InGameMenu"));
	if (!ensure(InGameMenuBPClass.Class != nullptr)) return;
	InGameMenuClass = InGameMenuBPClass.Class;
}

void UPuzzlePlatformsGameInstance::Init()
{
	IOnlineSubsystem* SubSystem = IOnlineSubsystem::Get();
	if (SubSystem != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("SubSystem found: %s"), *SubSystem->GetSubsystemName().ToString());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No SubSystem found"));
	}
}

void UPuzzlePlatformsGameInstance::LoadMenuWidget()
{
	if (!ensure(MenuClass != nullptr)) return;
	MainMenu = CreateWidget<UMenuWidget>(this, MenuClass);
	if (!ensure(MainMenu != nullptr)) return;
	MainMenu->SetMenuInterface(this);
}

void UPuzzlePlatformsGameInstance::InGameLoadMenu()
{
	if (!ensure(InGameMenuClass != nullptr)) return;
	InGameMenu = CreateWidget<UMenuWidget>(this, InGameMenuClass);
	if (!ensure(InGameMenu != nullptr)) return;
	InGameMenu->SetMenuInterface(this);
}

void UPuzzlePlatformsGameInstance::Host()
{

	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting"));
	UE_LOG(LogTemp, Warning, TEXT("Hosting"));

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UPuzzlePlatformsGameInstance::Join(const FString &Address)
{
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 5, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));

	UE_LOG(LogTemp, Warning, TEXT("Joining %s"), *Address);


	APlayerController* Controller = GetFirstLocalPlayerController();
	if (!ensure(Controller != nullptr)) return;

	Controller->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
	
}


void UPuzzlePlatformsGameInstance::Quit()
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ConsoleCommand("quit");
}

void UPuzzlePlatformsGameInstance::LoadMainMenu()
{
	APlayerController* Controller = GetFirstLocalPlayerController();
	if (!ensure(Controller != nullptr)) return;

	Controller->ClientTravel("/Game/MenuSystem/MainMenu", ETravelType::TRAVEL_Absolute);
}
