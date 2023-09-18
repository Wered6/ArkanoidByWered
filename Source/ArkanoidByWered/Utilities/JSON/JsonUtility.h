// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

class UABWLevelData;

class ARKANOIDBYWERED_API FJsonUtility
{
public:
	static bool LoadLevelDataFromJson(UObject* OuterObject,
	                                  const FString& FilePath,
	                                  TArray<UABWLevelData*>& OutLevelsDataArray);

private:
	static TSharedPtr<FJsonObject> ReadJsonFile(const FString& FilePath);
	static bool ValidateJsonObject(const TSharedPtr<FJsonObject>& JsonObject);
	static bool PopulateLevelDataArray(UObject* OuterObject,
	                                   const TSharedPtr<FJsonObject>& JsonObject,
	                                   TArray<UABWLevelData*>& OutLevelsDataArray);

	inline static FString FieldLevelName{TEXT("LevelName")};
	inline static FString FieldIsLevelUnlocked{TEXT("bIsLevelUnlocked")};
	inline static FString FieldIsLevelCompleted{TEXT("bIsLevelCompleted")};
};
