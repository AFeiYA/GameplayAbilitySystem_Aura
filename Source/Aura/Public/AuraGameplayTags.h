// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * Singleton containing native gameplay tags for the game.
 * The FAuraGameplayTags struct itself employs a common singleton pattern.
 * It has a private static member GameplayTags of its own type
 */
struct FAuraGameplayTags
{
public:
	static const FAuraGameplayTags& Get() {return GameplayTags;}
	static void InitializeNativeGameplayTags();
protected:
private:
	static FAuraGameplayTags GameplayTags;
};