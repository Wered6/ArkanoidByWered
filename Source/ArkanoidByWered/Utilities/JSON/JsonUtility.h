// Copyright (c) 2023 Wered. All rights reserved.

#pragma once

class UABWLevelData;

class ARKANOIDBYWERED_API FJsonUtility
{
public:
	static TArray<UABWLevelData*> LoadLevelDataFromJson(UObject* OuterObject, const FString& FilePath);
};
