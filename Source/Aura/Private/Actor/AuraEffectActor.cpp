// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

// Sets default values
AAuraEffectActor::AAuraEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* OtherActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent*  TargetAsc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor);
	if (TargetAsc==nullptr) return;	
	checkf(GameplayEffectClass,TEXT("Gameplay effect class is null"));
	
	auto EffectContextHandle = TargetAsc->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	const auto EffectSpecHandle = TargetAsc->MakeOutgoingSpec(GameplayEffectClass, 1.f, EffectContextHandle );
	TargetAsc->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
}

void AAuraEffectActor::OnOverlap(AActor* OtherActor)
{
}

void AAuraEffectActor::OnEnterOverlap(AActor* OtherActor)
{
}
