// Copyright (c) 2023 Wered. All rights reserved.


#include "JsonUtility.h"
#include "ArkanoidByWered/Systems/LevelSystem/ABWLevelData.h"

bool FJsonUtility::LoadLevelDataFromJson(UObject* OuterObject, const FString& FilePath,
                                         TArray<UABWLevelData*>& OutLevelsDataArray)
{
	const TSharedPtr<FJsonObject> JsonObject = ReadJsonFile(FilePath);

	if (!JsonObject.IsValid())
	{
		UE_LOG(LogJson, Error, TEXT("FJsonUtility::LoadLevelDataFromJson|Failed to deserialize JSON from file: %s"),
		       *FilePath);
		return false;
	}
	if (!ValidateJsonObject(JsonObject))
	{
		UE_LOG(LogJson, Error,
		       TEXT("FJsonUtility::LoadLevelDataFromJson|Malformed JSON: missing or incorrect types for fields."));
		return false;
	}

	return PopulateLevelDataArray(OuterObject, JsonObject, OutLevelsDataArray);
}

TSharedPtr<FJsonObject> FJsonUtility::ReadJsonFile(const FString& FilePath)
{
	FString JsonString;
	FFileHelper::LoadFileToString(JsonString, *FilePath);
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
	{
		return JsonObject;
	}

	return nullptr;
}

bool FJsonUtility::ValidateJsonObject(const TSharedPtr<FJsonObject>& JsonObject)
{
	TArray<TSharedPtr<FJsonValue>> JsonLevels = JsonObject->GetArrayField(TEXT("Levels"));

	for (const auto& JsonLevelPtr : JsonLevels)
	{
		const TSharedPtr<FJsonObject> JsonLevel = JsonLevelPtr->AsObject();

		if (!JsonLevel->HasTypedField<EJson::String>(FieldLevelName) ||
			!JsonLevel->HasTypedField<EJson::Boolean>(FieldIsLevelUnlocked) ||
			!JsonLevel->HasTypedField<EJson::Boolean>(FieldIsLevelCompleted))
		{
			return false;
		}
	}
	return true;
}

bool FJsonUtility::PopulateLevelDataArray(UObject* OuterObject,
                                          const TSharedPtr<FJsonObject>& JsonObject,
                                          TArray<UABWLevelData*>& OutLevelsDataArray)
{
	TArray<TSharedPtr<FJsonValue>> JsonLevels = JsonObject->GetArrayField(TEXT("Levels"));

	for (const auto& JsonLevelPtr : JsonLevels)
	{
		const TSharedPtr<FJsonObject> JsonLevel = JsonLevelPtr->AsObject();

		const FName LevelName = FName(*JsonLevel->GetStringField(FieldLevelName));
		const bool bIsLevelUnlocked = JsonLevel->GetBoolField(FieldIsLevelUnlocked);
		const bool bIsLevelCompleted = JsonLevel->GetBoolField(FieldIsLevelCompleted);

		UABWLevelData* NewLevelData = UABWLevelData::CreateUABWLevelData(
			OuterObject, LevelName, bIsLevelUnlocked, bIsLevelCompleted);

		if (!NewLevelData)
		{
			UE_LOG(LogJson, Error, TEXT("FJsonUtility::PopulateLevelDataArray|NewLevelData is nullptr"));
			return false;
		}

		OutLevelsDataArray.Add(NewLevelData);
	}
	return true;
}
