// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "WinterPlayerState.generated.h"

/**
 *
 */


UENUM(BlueprintType)
enum class ItemType : uint8 {
	Tool UMETA(DisplayName = "Tool"),
	Food UMETA(DisplayName = "Food"),
	Material UMETA(DisplayName = "Material"),
	Partner UMETA(DisplayName = "Partner")
};

USTRUCT()
struct FItemRow : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ItemType Type;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName ItemName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText ItemDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTexture2D* ItemLogo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 ItemVolume;
};

USTRUCT(BlueprintType)
struct FWinterItem : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemNum;
};


UCLASS()
class WINTER_API AWinterPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	UFUNCTION()
	void AddItem(FWinterItem& Item);

	UPROPERTY(BlueprintReadWrite)
	TArray<FWinterItem> Items;

	UPROPERTY(BlueprintReadWrite)
	float Enegy = 100.f;

	UPROPERTY(BlueprintReadWrite)
	float MaxEnegy = 100.f;

private:


};
