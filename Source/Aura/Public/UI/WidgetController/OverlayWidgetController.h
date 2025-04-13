// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "Windows/AllowWindowsPlatformTypes.h"
#include "OverlayWidgetController.generated.h"

class UAuraUserWidget;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSingnature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSingnature, float, NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSingnature, float, NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSingnature, float, NewMaxMana);

USTRUCT(BlueprintType)
struct FUIWidgetRow:public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MessageTag = FGameplayTag();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Message = FText();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UAuraUserWidget> MessageWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Image = nullptr;
	
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnHealthChangedSingnature OnHealthChanged;
	
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnMaxHealthChangedSingnature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnManaChangedSingnature OnManaChanged;
	
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnMaxManaChangedSingnature OnMaxManaChanged;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Widget Data")
	TObjectPtr<UDataTable> MessageWidgetDataTable;
	
	void HealthChanged(const FOnAttributeChangeData& Data) const;
	void MaxHealthChanged(const FOnAttributeChangeData& Data) const;
	void ManaChanged(const FOnAttributeChangeData& Data) const;
	void MaxManaChanged(const FOnAttributeChangeData& Data) const;

};
