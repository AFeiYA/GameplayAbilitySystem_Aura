// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * Singleton containing native gameplay tags for the game.
 * This implementation of the singleton pattern for FAuraGameplayTags has the following characteristics and uses these C++ features:
Characteristics:
Single Instance Guarantee: The primary characteristic is that it ensures only one instance of FAuraGameplayTags exists throughout the application. This is achieved by having a static member variable GameplayTags within the struct itself.
Global Access Point: It provides a globally accessible way to get this single instance through the public static method Get(). This allows any part of the code to access the gameplay tags without needing to pass around an instance of FAuraGameplayTags.
Centralized Management: It centralizes the definition and access of native gameplay tags for the "Aura" project. The InitializeNativeGameplayTags() method, though static, is part of this centralized management, responsible for registering the tags with Unreal Engine's UGameplayTagsManager.
Initialization Control: The single instance GameplayTags is created when the program loads due to its static storage duration. The actual gameplay tag data is registered by explicitly calling InitializeNativeGameplayTags(), typically at startup.
C++ Features Used:
static Member Variable:
static FAuraGameplayTags GameplayTags; (declared in .h, defined in .cpp).
This creates a single instance of GameplayTags that belongs to the FAuraGameplayTags struct type itself, rather than to any particular object of the struct. It's instantiated once.
static Member Function (Get):
static const FAuraGameplayTags& Get() {return GameplayTags;}
This function can be called on the struct type directly (e.g., FAuraGameplayTags::Get()) without needing an instance. It returns a reference to the single GameplayTags instance. The const ensures that the instance cannot be modified through this getter, promoting read-only access to the tags container itself (though the tags manager it interacts with might change).
static Member Function (InitializeNativeGameplayTags):
static void InitializeNativeGameplayTags();
Similar to Get(), this is a class-level function. It's used to perform the one-time setup of registering the native gameplay tags.
Definition of Static Member in a Source File:
The line FAuraGameplayTags FAuraGameplayTags::GameplayTags; in AuraGameplayTags.cpp is the actual definition and instantiation of the static member. Without this, the static member would only be declared and not exist.
This pattern is a common and straightforward way to implement singletons in C++, especially for manager-type classes or global lookup tables like this gameplay tag container. While the constructor of FAuraGameplayTags is not explicitly shown as private in the provided snippet (which is a strict requirement for preventing other instantiations), the design strongly relies on the convention of using only the Get() method to access the intended single instance.
 * 
 */
struct FAuraGameplayTags
{
public:
	static const FAuraGameplayTags& Get() {return GameplayTags;}
	static void InitializeNativeGameplayTags();

	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Resilience;
	FGameplayTag Attributes_Primary_Vigor;
	
	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxMana;
	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag Attributes_Secondary_ArmorPenetration;
	FGameplayTag Attributes_Secondary_BlockChance;
	FGameplayTag Attributes_Secondary_CriticalHitChance;
	FGameplayTag Attributes_Secondary_CriticalHitDamage;
	FGameplayTag Attributes_Secondary_CriticalHitResistance;
	FGameplayTag Attributes_Secondary_HealthRegeneration;
	FGameplayTag Attributes_Secondary_ManaRegeneration;
	
protected:
private:
	static FAuraGameplayTags GameplayTags;
};