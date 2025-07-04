// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAbilitySystemLibrary.h"

#include "Kismet/GameplayStatics.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"
#include "UI/WidgetController/AuraWidgetController.h"

UOverlayWidgetController* UAuraAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(WorldContextObject,0);
	if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(PlayerController->GetHUD()))
	{
		AAuraPlayerState* AuraPlayerState = PlayerController->GetPlayerState<AAuraPlayerState>();
		UAbilitySystemComponent* AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
		UAttributeSet* AttributeSet = AuraPlayerState->GetAttributeSet();
		const FWidgetControllerParams WidgetControllerParams(PlayerController,AuraPlayerState,AbilitySystemComponent,AttributeSet);
		return AuraHUD->GetOverlayWidgetController(WidgetControllerParams);
	}
	return nullptr;	
}

UAttributeMenuWidgetController* UAuraAbilitySystemLibrary::GetAttributeMenuWidgetController(
	const UObject* WorldContextObject)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(WorldContextObject,0);
	if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(PlayerController->GetHUD()))
	{
		AAuraPlayerState* AuraPlayerState = PlayerController->GetPlayerState<AAuraPlayerState>();
		UAbilitySystemComponent* AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
		UAttributeSet* AttributeSet = AuraPlayerState->GetAttributeSet();
		const FWidgetControllerParams WidgetControllerParams(PlayerController,AuraPlayerState,AbilitySystemComponent,AttributeSet);
		return AuraHUD->GetAttributeMenuWidgetController(WidgetControllerParams);
	}
	return nullptr;	
}
