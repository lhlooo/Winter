// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Player/WinterPlayerState.h"
#include "WinterGameState.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class Weather : uint8 {
	SunnyDay UMETA(DisplayName = "SunnyDay"),
	LightSnow UMETA(DisplayName = "LightSnow"),
	HeavySnow UMETA(DisplayName = "HeavySnow")
};

UENUM(BlueprintType)
enum class EventType : uint8 {
	Human UMETA(DisplayName = "Human"),
	Dog UMETA(DisplayName = "Dog"),
	HumanAndDog UMETA(DisplayName = "HumanAndDog")
};

UENUM(BlueprintType)
enum class Place : uint8 {
	House UMETA(DisplayName = "House"),
	IceLake UMETA(DisplayName = "IceLake"),
	IcePlain UMETA(DisplayName = "IcePlain")
};

USTRUCT(BlueprintType)
struct FWinterEventResource : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EventType eventType = EventType::Human;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FWinterItem> EventConsume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FWinterItem> EventGains;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EnegyConsume = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeConsume = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UTexture2D* ActionLogo;
};

UCLASS()
class WINTER_API AWinterGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Date")
	int32 TotalDate = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Date")
	int32 PassedDate = 1;

	UPROPERTY(BlueprintReadWrite, Category = "Date")
	float HumanPassTime = 0.f;

	UPROPERTY(BlueprintReadWrite, Category = "Date")
	float DogPassTime = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weather")
	Weather DayWeather;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Event")
	TObjectPtr<UDataTable> HouseEvents;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Event")
	TObjectPtr<UDataTable> LakeEvents;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Event")
	TObjectPtr<UDataTable> PlainEvents;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Event")
	TObjectPtr<UDataTable> CreateEvents;

	UPROPERTY(BlueprintReadWrite, Category = "Event")
	TArray<FWinterEventResource> HouseEvent;

	UPROPERTY(BlueprintReadWrite, Category = "Event")
	TArray<FWinterEventResource> LakeEvent;

	UPROPERTY(BlueprintReadWrite, Category = "Event")
	TArray<FWinterEventResource> PlainEvent;

	UPROPERTY(BlueprintReadWrite, Category = "Item")
	TArray<FWinterItem> HouseItems;

	UPROPERTY(BlueprintReadWrite, Category = "Item")
	TArray<FWinterItem> LakeItems;

	UPROPERTY(BlueprintReadWrite, Category = "Item")
	TArray<FWinterItem> PlainItems;
};
