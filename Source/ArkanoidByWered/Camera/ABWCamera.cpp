// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWCamera.h"
#include "ArkanoidByWered/Utilities/CustomLogs/ABWCustomLogs.h"
#include "Camera/CameraComponent.h"

AABWCamera::AABWCamera()
{
	PrimaryActorTick.bCanEverTick = true;

	UCameraComponent* CameraComp = GetCameraComponent();

	if (!CameraComp)
	{
		UE_LOG(LogCamera, Warning, TEXT("AABWCamera::AABWCamera|CameraComp is nullptr"));
		return;
	}

	CameraComp->ProjectionMode = ECameraProjectionMode::Orthographic;
	CameraComp->OrthoWidth = 512.f;
}
