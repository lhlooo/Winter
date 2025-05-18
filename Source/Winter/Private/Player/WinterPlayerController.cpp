// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/WinterPlayerController.h"
#include "Player/WinterPlayerState.h"


FItemRow& AWinterPlayerController::GetItem(FName Name)
{
	check(ItemTable);

	return *ItemTable->FindRow<FItemRow>(Name, TEXT(""));

}

void AWinterPlayerController::InitializeItems()
{
	check(PlayerState);

	AWinterPlayerState* WinterPlayerState = Cast<AWinterPlayerState>(PlayerState);

	TArray<FWinterItem*> InitializeItems;
	InitItems->GetAllRows<FWinterItem>(FString(""), InitializeItems);

	if (!InitializeItems.IsEmpty()) {
		for (FWinterItem* Item : InitializeItems) {
			WinterPlayerState->AddItem(*Item);
		}
	}
}

bool AWinterPlayerController::EventClick(FWinterEventResource EventResource, EventType Type)
{
	AWinterGameState* WinterGameState = Cast<AWinterGameState>(GetWorld()->GetGameState());
	AWinterPlayerState* WinterPlayerState = Cast<AWinterPlayerState>(PlayerState);
	check(WinterGameState);
	check(WinterPlayerState);

	TArray<FWinterItem>& ScenesItems = place == Place::House ? WinterGameState->HouseItems :
		place == Place::IceLake ? WinterGameState->LakeItems : WinterGameState->PlainItems;

	for (auto& Consume : EventResource.EventConsume) {
		int32 num = 0;
		for (auto& Item : ScenesItems) 
			if (Item.ItemName == Consume.ItemName) {
				num += Item.ItemNum;
				break;
			}
		for (auto& Item : WinterPlayerState->Items)
			if (Item.ItemName == Consume.ItemName) {
				num += Item.ItemNum;
				break;
			}
		if (num < Consume.ItemNum)
			return false;
	}
	for (auto& Consume : EventResource.EventConsume) {

		if (GetItem(Consume.ItemName).Type == ItemType::Tool)
			continue;

		int32 idx = 0, ConNum = Consume.ItemNum;
		for (auto& Item : ScenesItems){
			if (Item.ItemName == Consume.ItemName) {
				if (Item.ItemNum > Consume.ItemNum) {
					Item.ItemNum -= Consume.ItemNum;
					ConNum = 0;
				}
				else {
					ScenesItems.RemoveAt(idx);
					ConNum -= Item.ItemNum;
				}
				break;
			}
			idx++;
		}

		idx = 0;
		for (auto Item : WinterPlayerState->Items) {
			if (Item.ItemName == Consume.ItemName) {
				Item.ItemNum -= Consume.ItemNum;
				if (Item.ItemNum == 0)
					WinterPlayerState->Items.RemoveAt(idx);
				break;
			}
			idx++;
		}
	}

	for (auto Obtains : EventResource.EventGains) {
		bool HasItem = false;
		for (auto& Item : ScenesItems) {
			if (Item.ItemName == Obtains.ItemName) {
				Item.ItemNum += Obtains.ItemNum;
				HasItem = true;
				break;
			}
		}
		if(!HasItem)
			ScenesItems.Add(Obtains);
	}

	if(Type == EventType::Human){
		WinterGameState->HumanPassTime += EventResource.TimeConsume;
		WinterPlayerState->Enegy -= EventResource.EnegyConsume;
	}
	else if (Type == EventType::Dog) {
		WinterGameState->DogPassTime += EventResource.TimeConsume;
	}
	else {
		float maxTime = std::max(WinterGameState->HumanPassTime, WinterGameState->DogPassTime);
		WinterGameState->HumanPassTime = maxTime + EventResource.TimeConsume;
		WinterGameState->DogPassTime = maxTime + EventResource.TimeConsume;
		WinterPlayerState->Enegy -= EventResource.EnegyConsume;
	}

	return true;
}

bool AWinterPlayerController::TimeCheck(float Time, EventType Type)
{
	AWinterGameState* WinterGameState = Cast<AWinterGameState>(GetWorld()->GetGameState());
	check(WinterGameState);

	if (Type == EventType::Human) {
		if (10.f - WinterGameState->HumanPassTime < Time)
			return false;
	}
	else if (Type == EventType::Dog) {
		if (10.f - WinterGameState->DogPassTime < Time)
			return false;
	}
	else {
		if (10.f - std::max(WinterGameState->DogPassTime, WinterGameState->HumanPassTime) < Time)
			return false;
	}

	return true;
}

bool AWinterPlayerController::EnegyCheck(float Enegy, EventType Type)
{
	if (Type == EventType::Dog)return true;

	AWinterPlayerState* WinterPlayerState = Cast<AWinterPlayerState>(PlayerState);
	check(WinterPlayerState);

	if (WinterPlayerState->Enegy < Enegy)
		return false;

	return true;
}

void AWinterPlayerController::ItemsTrans(TArray<FWinterItem> Items,int32 SourceIdx, int32 AimIdx)
{
	AWinterGameState* WinterGameState = Cast<AWinterGameState>(GetWorld()->GetGameState());
	AWinterPlayerState* WinterPlayerState = Cast<AWinterPlayerState>(PlayerState);
	check(WinterGameState);
	check(WinterPlayerState);

	TArray<FWinterItem>& SourceItems = SourceIdx == 0 ? WinterGameState->HouseItems :
		SourceIdx == 1 ? WinterGameState->LakeItems :
		SourceIdx == 2 ? WinterGameState->PlainItems : WinterPlayerState->Items;

	TArray<FWinterItem>& AimItems = AimIdx == 0 ? WinterGameState->HouseItems :
		AimIdx == 1 ? WinterGameState->LakeItems :
		AimIdx == 2 ? WinterGameState->PlainItems : WinterPlayerState->Items;

									

	for (auto& Item : Items) {
		int idx = 0;
		for (auto& SItem : SourceItems) {
			if (Item.ItemName.IsEqual(SItem.ItemName)) {
				SItem.ItemNum -= Item.ItemNum;
				if (SItem.ItemNum == 0) {
					SourceItems.RemoveAt(idx);
				}
				break;
			}
			idx++;
		}
	}

	for (auto& Item : Items) {
		bool HasItem = false;
		for (auto& AItem : AimItems) {
			if (Item.ItemName.IsEqual(AItem.ItemName)) {
				AItem.ItemNum += Item.ItemNum;
				HasItem = true;
				break;
			}
		}
		if (!HasItem) {
			AimItems.Add(Item);
		}
	}
}

void AWinterPlayerController::AddEvent(FWinterEventResource Event, int32 AimIdx)
{
	AWinterGameState* WinterGameState = Cast<AWinterGameState>(GetWorld()->GetGameState());
	check(WinterGameState);

	TArray<FWinterEventResource>& AimEvent = AimIdx == 1 ? WinterGameState->LakeEvent : WinterGameState->PlainEvent;
	AimEvent.Add(Event);
}
