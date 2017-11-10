#pragma once

#include "main.h"

#define HW_DLL		XorStr("hw.dll")
#define CLIENT_DLL	XorStr("client.dll")
#define GAMEUI_DLL	XorStr("GameUI.dll")

cl_clientfunc_t*		FindClient();
cl_enginefunc_t*		FindEngine();
engine_studio_api_t*	FindStudio();
r_studio_interface_t*	FindStudioAPI();