// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/WinterGameState.h"
#include "GameFramework/PlayerController.h"
#include "WinterPlayerController.generated.h"

struct FItemRow;

enum class ItemType : uint8;

/**
 *
 */


UCLASS()
class WINTER_API AWinterPlayerController : public APlayerController {
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	FItemRow& GetItem(FName Name);

	UFUNCTION(BlueprintCallable)
	void InitializeItems();

	UFUNCTION(BlueprintCallable)
	bool EventClick(FWinterEventResource EventResource, EventType Type);

	UFUNCTION(BlueprintCallable)
	bool TimeCheck(float Time, EventType Type);

	UFUNCTION(BlueprintCallable)
	bool EnegyCheck(float Enegy, EventType Type);

	UFUNCTION(BlueprintCallable)
	void ItemsTrans(TArray<FWinterItem> Items, int32 SourceIdx, int32 AimIdx);

	UFUNCTION(BlueprintCallable)
	void AddEvent(FWinterEventResource Event, int32 AimIdx);

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	TObjectPtr<UDataTable> ItemTable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	TObjectPtr<UDataTable> InitItems;

	UPROPERTY(BlueprintReadWrite, Category = "Item")
	Place place = Place::House;
};