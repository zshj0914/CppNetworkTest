// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "CppNetworkTestGameMode.h"
#include "CppNetworkTestPawn.h"
#include "CppNetworkTestHud.h"

ACppNetworkTestGameMode::ACppNetworkTestGameMode()
{
	DefaultPawnClass = ACppNetworkTestPawn::StaticClass();
	HUDClass = ACppNetworkTestHud::StaticClass();
}
