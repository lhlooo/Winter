// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WinterUserWidget.h"

UWidget* UWinterUserWidget::GetChildByIdx(TArray<UWidget*> ContainerPanel, int32 idx)
{
	return ContainerPanel[idx];
}
