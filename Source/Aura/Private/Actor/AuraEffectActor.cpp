// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Components/SphereComponent.h"

// Sets default values
AAuraEffectActor::AAuraEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(Mesh);
	Sphere->SetupAttachment(GetRootComponent());
	
}

void AAuraEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor);
	if (ASCInterface)
	{
		//TODO: Change this to apply a Game Effect. For now using const_cast as a hack !!!
		const UAuraAttributeSet* AuraAttributeSet =  Cast<UAuraAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UAuraAttributeSet::StaticClass()));
		UAuraAttributeSet* MutableAuraAttributeSet = const_cast<UAuraAttributeSet*>(AuraAttributeSet);
		MutableAuraAttributeSet->SetHealth(AuraAttributeSet->GetHealth() + 30.f);
		Destroy();
	} 
} 

void AAuraEffectActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

// Called when the game starts or when spawned
void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
	// 	Sphere->	指向球体碰撞组件对象（USphereComponent 类型的组件实例）
	// OnComponentBeginOverlap	碰撞组件 开始重叠事件委托  （内置的 Multicast 多播委托）
	// .AddDynamic	动态绑定宏（将成员函数绑定到委托）
	// (this, ...)	指定接收事件的对象实例（当前 Actor 实例）
	// &AAuraEffectActor::OnOverlap	要绑定的成员函数指针 事件触发时实际调用的函数
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAuraEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AAuraEffectActor::OnEndOverlap);
}


