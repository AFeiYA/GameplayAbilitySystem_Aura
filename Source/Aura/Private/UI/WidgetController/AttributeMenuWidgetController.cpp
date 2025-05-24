// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AbilitySystem/Data/AttributeInfo.h"

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	for (auto& Pair : AuraAttributeSet->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
			[this, Pair, AuraAttributeSet](const FOnAttributeChangeData& Data)
			{
				FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(Pair.Key);
				Info.AttributeValue = Pair.Value().GetNumericValue(AuraAttributeSet);
				AttributeInfoDelegate.Broadcast(Info);
			}
		);
	}

}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	check(AttributeInfo);
	// FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(FAuraGameplayTags::Get().Attributes_Primary_Strength);
	// Info.AttributeValue = AuraAttributeSet->GetStrength();
	// AttributeInfoDelegate.Broadcast(Info);
	for (auto& Pair : AuraAttributeSet->TagsToAttributes)
	{
		FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(Pair.Key);
		Info.AttributeValue = Pair.Value().GetNumericValue(AuraAttributeSet);
		AttributeInfoDelegate.Broadcast(Info);
	}
}