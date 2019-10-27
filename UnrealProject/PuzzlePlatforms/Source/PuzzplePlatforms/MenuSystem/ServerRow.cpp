// Fill out your copyright notice in the Description page of Project Settings.

#include "ServerRow.h"
#include "TextBlock.h"
#include "Button.h"
#include "MainMenu.h"


void UServerRow::Setup(UMainMenu * InParent, const uint32& InIndex)
{
	Parent = InParent;
	Index = InIndex;
	RowButton->OnClicked.AddDynamic(this, &UServerRow::OnClicked);
}

void UServerRow::SetText(const FText & Text)
{
	this->ServerName->SetText(Text);
}

void UServerRow::OnClicked()
{
	Parent->SelectIndex(Index);
}
