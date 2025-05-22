﻿#include "D1CheatEntryWidget.h"

#include "CommonTextBlock.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Item/D1ItemTemplate.h"
#include "Player/LyraCheatManager.h"
#include "Player/LyraPlayerController.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(D1CheatEntryWidget)

UD1CheatEntryWidget::UD1CheatEntryWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    
}

void UD1CheatEntryWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Button_Entry->OnClicked.AddUniqueDynamic(this, &ThisClass::OnButtonClicked);
}

void UD1CheatEntryWidget::InitializeUI(ED1CheatEntryType InCheatEntryType, TSubclassOf<UD1ItemTemplate> InItemTemplateClass, TSoftObjectPtr<UAnimMontage> InAnimMontage)
{
	CheatEntryType = InCheatEntryType;
	
	switch (CheatEntryType)
	{
	case ED1CheatEntryType::PrimaryWeapon:
	case ED1CheatEntryType::SecondaryWeapon:
	case ED1CheatEntryType::Armor:
	case ED1CheatEntryType::Utility:
		ItemTemplateClass = InItemTemplateClass;
		if (ItemTemplateClass)
		{
			if (UD1ItemTemplate* ItemTemplate = Cast<UD1ItemTemplate>(ItemTemplateClass->GetDefaultObject()))
			{
				Text_Entry->SetText(ItemTemplate->DisplayName);
				Image_Entry->SetBrushFromTexture(ItemTemplate->IconTexture, true);
			}
		}
		break;
	case ED1CheatEntryType::Animation:
		AnimMontage = InAnimMontage;
		if (AnimMontage.IsNull() == false)
		{
			Text_Entry->SetText(FText::FromString(AnimMontage.GetAssetName()));
			SizeBox_Entry->SetVisibility(ESlateVisibility::Collapsed);
		}
		break;
	}
}

void UD1CheatEntryWidget::OnButtonClicked()
{
	ALyraPlayerController* LyraPlayerController = GetOwningPlayer<ALyraPlayerController>();
	if (LyraPlayerController == nullptr)
		return;

	switch (CheatEntryType)
	{
	case ED1CheatEntryType::PrimaryWeapon:
		// TEMP Rookiss
		//LyraPlayerController->Server_EquipWeapon(EWeaponSlotType::Primary, ItemTemplateClass);
		break;
	case ED1CheatEntryType::SecondaryWeapon:
		// TEMP Rookiss
		//LyraPlayerController->Server_EquipWeapon(EWeaponSlotType::Secondary, ItemTemplateClass);
		break;
	case ED1CheatEntryType::Armor:
		// TEMP Rookiss
		//LyraPlayerController->Server_EquipArmor(ItemTemplateClass);
		break;
	case ED1CheatEntryType::Utility:
		// TEMP Rookiss
		//LyraPlayerController->Server_EquipUtility(EUtilitySlotType::Primary, ItemTemplateClass);
		break;
	case ED1CheatEntryType::Animation:
		if (ULyraCheatManager* LyraCheatManager = Cast<ULyraCheatManager>(LyraPlayerController->CheatManager))
		{
			LyraCheatManager->SelectedMontage = AnimMontage;
		}
		break;
	}
}
