

#include "UI/HUD/AuraHUD.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"


// 解耦设计：将业务逻辑（Controller）与表现逻辑（Widget）分离
// 可扩展性：通过继承UOverlayWidgetController实现不同功能的控制器
// 类型安全：使用TSubclassOf确保蓝图类配置的正确性
// 资源管理：利用UE4的UObject系统自动处理内存管理
UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	//单例模式管理，确保唯一实例
	if (OverlayWidgetController == nullptr)
	{
		//使用NewObject时指定Outer为当前HUD实例（this），确保生命周期绑定
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		return OverlayWidgetController;
	}
	return OverlayWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	//OverlayWidgetControllerClass必须在蓝图BP_AuraHUD中配置
	checkf(OverlayWidgetClass, TEXT("OverlayWidgetClass uninitialized , please fill out BP_AuraHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("OverlayWidgetControllerClass uninitialized , please fill out BP_AuraHUD"));

	
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UAuraUserWidget>(Widget);

	const FWidgetControllerParams WidgetControllerParams(PC,PS,ASC,AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);
	OverlayWidget -> SetWidgetController(WidgetController);
	Widget->AddToViewport();
}
