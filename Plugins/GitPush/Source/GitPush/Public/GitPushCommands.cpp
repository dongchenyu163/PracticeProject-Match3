// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "GitPushCommands.h"

#include "GitPushPrivatePCH.h"

#define LOCTEXT_NAMESPACE "FGitPushModule"

void FGitPushCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "GitPush", "Execute GitPush action", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
