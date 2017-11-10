#include "offset.h"

cl_clientfunc_t* FindClient()
{
	cl_clientfunc_t* g_pReturn = nullptr;

	DWORD dwStringAddress = CSX::Memory::FindString( HW_DLL , XorStr( "ScreenFade" ) );

	if ( dwStringAddress )
	{
		DWORD dwClientOffset = *(PDWORD)( CSX::Memory::FindPushString( HW_DLL , dwStringAddress ) + 0x13 );

		if ( !CSX::Utils::IsBadReadPtr( (PVOID)dwClientOffset ) )
		{
			g_pReturn = (cl_clientfunc_t*)dwClientOffset;
		}
	}

	return g_pReturn;
}

cl_enginefunc_t* FindEngine()
{
	cl_enginefunc_t* g_pReturn = nullptr;

	DWORD dwStringAddress = CSX::Memory::FindString( CLIENT_DLL , XorStr( "sprites/voiceicon.spr" ) );

	if ( dwStringAddress )
	{
		DWORD dwEngineOffset = *(PDWORD)( CSX::Memory::FindPushString( CLIENT_DLL , dwStringAddress ) + 0x07 );

		if ( !CSX::Utils::IsBadReadPtr( (PVOID)dwEngineOffset ) )
		{
			g_pReturn = (cl_enginefunc_t*)dwEngineOffset;
		}
	}

	return g_pReturn;
}

engine_studio_api_t* FindStudio()
{
	engine_studio_api_t* g_pReturn = nullptr;

	DWORD dwStringAddress = CSX::Memory::FindString( HW_DLL , XorStr( "Couldn't get client .dll studio model rendering interface." ) );

	if ( dwStringAddress )
	{
		DWORD dwStudioOffset = *(PDWORD)( CSX::Memory::FindPushString( HW_DLL , dwStringAddress ) - 0x14 );

		if ( !CSX::Utils::IsBadReadPtr( (PVOID)dwStudioOffset ) )
		{
			g_pReturn = (engine_studio_api_t*)dwStudioOffset;
		}
	}

	return g_pReturn;
}

r_studio_interface_t* FindStudioAPI()
{
	r_studio_interface_t* g_pReturn = nullptr;

	DWORD dwPatternAddress = CSX::Memory::FindPattern( CLIENT_DLL , XorStr( "C7 00 ? ? ? ? F3 A5" ) , 2 );

	if ( dwPatternAddress )
	{
		DWORD dwRenderOffset = *(PDWORD)dwPatternAddress;

		if ( !CSX::Utils::IsBadReadPtr( (PVOID)( dwRenderOffset + 4 ) ) )
		{
			g_pReturn = (r_studio_interface_t*)dwRenderOffset;
		}
	}

	return g_pReturn;
}