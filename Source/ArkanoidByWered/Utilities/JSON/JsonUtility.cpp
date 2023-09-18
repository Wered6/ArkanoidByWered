// Copyright (c) 2023 Wered. All rights reserved.


#include "JsonUtility.h"
#include "ArkanoidByWered/Systems/LevelSystem/ABWLevelData.h"

TArray<UABWLevelData*> FJsonUtility::LoadLevelDataFromJson(UObject* OuterObject, const FString& FilePath)
{
	FString JsonString;
	FFileHelper::LoadFileToString(JsonString, *FilePath);

	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	TArray<UABWLevelData*> LevelsDataArray;

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		TArray<TSharedPtr<FJsonValue>> JsonLevels = JsonObject->GetArrayField(TEXT("Levels"));

		for (int i = 0; i < JsonLevels.Num(); i++)
		{
			const TSharedPtr<FJsonObject> JsonLevel = JsonLevels[i]->AsObject();
			const FName LevelName = FName(*JsonLevel->GetStringField(TEXT("LevelName")));
			const bool bIsLevelUnlocked = JsonLevel->GetBoolField(TEXT("bIsLevelUnlocked"));
			const bool bIsLevelCompleted = JsonLevel->GetBoolField(TEXT("bIsLevelCompleted"));

			UABWLevelData* NewLevelData = UABWLevelData::CreateUABWLevelData(
				OuterObject, LevelName, bIsLevelUnlocked, bIsLevelCompleted);

			LevelsDataArray.Add(NewLevelData);
		}
	}

	return LevelsDataArray;
}
