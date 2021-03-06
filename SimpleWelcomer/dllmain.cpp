// dllmain.cpp : Definiert den Einstiegspunkt für die DLL-Anwendung.
#include "stdafx.h"
#include "base.h"
#include "datatypes.h"


void client_connected(gentity_t* player)
{
	char buffer[256];
	sprintf_s(buffer, "%s joined the game!", player->shared.client->session.clientstate.name);
	base::say_all(buffer);
}

void client_disconnected(gentity_t* player)
{
	char buffer[256];
	sprintf_s(buffer, "%s left the game!", player->shared.client->session.clientstate.name);
	base::say_all(buffer);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
	    base::sys_print("Loaded SimpleWelcomer \n");
		base::install_client_connected_callback(client_connected);
		base::install_client_disconnect_callback(client_disconnected);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

