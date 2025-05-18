// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WinterUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class WINTER_API UWinterUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable) 
	UWidget* GetChildByIdx(TArray<UWidget*> ContainerPanel, int32 idx);
};
