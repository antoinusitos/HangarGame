// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "HangarGame.h"
#include "HangarGameGameMode.h"
#include "HangarGamePawn.h"

AHangarGameGameMode::AHangarGameGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = AHangarGamePawn::StaticClass();
}

