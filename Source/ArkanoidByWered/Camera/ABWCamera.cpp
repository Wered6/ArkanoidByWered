// Copyright (c) 2023 Wered. All rights reserved.


#include "ABWCamera.h"

#include "Camera/CameraComponent.h"

AABWCamera::AABWCamera()
{
	PrimaryActorTick.bCanEverTick = true;

	UCameraComponent* CameraComp = GetCameraComponent();
	
	if (CameraComp)
	{
		CameraComp->ProjectionMode = ECameraProjectionMode::Orthographic;
		CameraComp->OrthoWidth = 512.f;
	}
}
