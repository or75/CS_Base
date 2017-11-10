#pragma once

#include "main.h"

struct PlayerMove_S
{
	int flags;
};

extern PlayerMove_S g_PlayerMove;

void HookFunction();