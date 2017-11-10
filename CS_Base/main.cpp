#include "main.h"

DWORD WINAPI CheatEntry( LPVOID lpThreadParameter )
{
	if ( !CSX::Utils::IsModuleLoad( HW_DLL ) )
		return 0;

	if ( !CSX::Utils::IsModuleLoad( CLIENT_DLL ) )
		return 0;

	if ( !CSX::Utils::IsModuleLoad( GAMEUI_DLL ) )
		return 0;

	SDK::g_pClient = FindClient();
	SDK::g_pEngine = FindEngine();
	SDK::g_pStudio = FindStudio();
	SDK::g_pStudioAPI = FindStudioAPI();

	if ( !SDK::g_pClient )
	{
		CSX::Log::Add( "[-] Find Client Error\n" );
		return 0;
	}

	if ( !SDK::g_pEngine )
	{
		CSX::Log::Add( "[-] Find Engine Error\n" );
		return 0;
	}

	if ( !SDK::g_pStudio )
	{
		CSX::Log::Add( "[-] Find Studio Error\n" );
		return 0;
	}

	if ( !SDK::g_pStudioAPI )
	{
		CSX::Log::Add( "[-] Find StudioAPI Error\n" );
		return 0;
	}

	SDK::CopyClient();
	SDK::CopyEngine();
	SDK::CopyStudio();
	SDK::CopyStudioAPI();

	CSX::Log::Add( "g_pClient: %X\n" , SDK::g_pClient );
	CSX::Log::Add( "g_pEngine: %X\n" , SDK::g_pEngine );
	CSX::Log::Add( "g_pStudio: %X\n" , SDK::g_pStudio );
	CSX::Log::Add( "g_pStudioAPI: %X\n" , SDK::g_pStudioAPI );
	CSX::Log::Add( "g_pStudioAPI->version: %i\n" , SDK::g_pStudioAPI->version );

	HookFunction();

	return 0;
}

BOOL WINAPI DllMain( HINSTANCE hinstDLL , DWORD fdwReason , LPVOID lpReserved )
{
	if ( fdwReason == DLL_PROCESS_ATTACH )
	{
		DisableThreadLibraryCalls( hinstDLL );

		CSX::Log::LogFile = CSX::Utils::GetModuleBaseDir( hinstDLL ) + "\\debug.log";
		DeleteFileA( CSX::Log::LogFile.c_str() );
		CreateThread( 0 , 0 , CheatEntry , hinstDLL , 0 , 0 );
	}

	return TRUE;
}