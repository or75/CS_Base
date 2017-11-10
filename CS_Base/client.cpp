#include "client.h"

PlayerMove_S g_PlayerMove;

void DrawBox( int x , int y , int w , int h , int linewidth , int r , int g , int b , int a )
{
	SDK::g_Engine.pfnTintRGBA( x , y , w , linewidth , r , g , b , a );
	SDK::g_Engine.pfnTintRGBA( x + w - linewidth , y + linewidth , linewidth , h - linewidth , r , g , b , a );
	SDK::g_Engine.pfnTintRGBA( x , y + linewidth , linewidth , h - linewidth , r , g , b , a );
	SDK::g_Engine.pfnTintRGBA( x + linewidth , y + h - linewidth , w - linewidth * 2 , linewidth , r , g , b , a );
}

static bool gs_a = false;
void gs_s() { gs_a = true; }
void gs_e() { gs_a = false; }

void HUD_Frame( double time )
{
	static bool FirstFrame = false;

	if ( !FirstFrame )
	{
		SDK::g_pEngine->Con_Printf( "\n\n\t\t\t[ CS BASE 2017 LOAD SUCCESS ]\n\n" );

		SDK::g_Engine.pfnAddCommand( "+gs" , gs_s );
		SDK::g_Engine.pfnAddCommand( "-gs" , gs_e );

		SDK::g_Engine.pfnSetMouseEnable( false );
		SDK::g_Client.IN_DeactivateMouse();

		FirstFrame = true;
	}

	SDK::g_Client.HUD_Frame( time );
}

void HUD_Redraw( float time , int intermission )
{
	SDK::g_Client.HUD_Redraw( time , intermission );

	DrawBox( 10 , 10 , 50 , 50 , 1 , 255 , 0 , 0 , 255 );
}

void HUD_PlayerMove( struct playermove_s *ppmove , int server )
{
	SDK::g_Client.HUD_PlayerMove( ppmove , server );

	g_PlayerMove.flags = ppmove->flags;
}

void CL_CreateMove( float frametime , struct usercmd_s *cmd , int active )
{
	SDK::g_Client.CL_CreateMove( frametime , cmd , active );

	if ( gs_a )
	{
		static int gs_state = 0;

		if ( gs_state == 0 && g_PlayerMove.flags & FL_ONGROUND )
		{
			cmd->buttons |= IN_DUCK;
			gs_state = 1;
		}
		else if ( gs_state == 1 )
		{
			cmd->buttons &= ~IN_DUCK;
			gs_state = 0;
		}
	}
}

int StudioDrawPlayer( int flags , struct entity_state_s *pplayer )
{
	return SDK::g_StudioAPI.StudioDrawPlayer( flags , pplayer );
}

void HookFunction()
{
	SDK::g_pClient->HUD_Frame = HUD_Frame;
	SDK::g_pClient->HUD_Redraw = HUD_Redraw;
	SDK::g_pClient->HUD_PlayerMove = HUD_PlayerMove;
	SDK::g_pClient->CL_CreateMove = CL_CreateMove;

	SDK::g_pStudioAPI->StudioDrawPlayer = StudioDrawPlayer;
}