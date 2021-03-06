// dllmain.cpp : Definiert den Einstiegspunkt für die DLL-Anwendung.
#include "stdafx.h"
#include "base.h"
#include "datatypes.h"
#include <iostream>
#include <fstream>
#include "scr.h"


typedef int(__cdecl* bg_weapon_t)(int weapon, int a1, char* buffer, int buffer_size);
bg_weapon_t bg_weapon = (bg_weapon_t)0x00421B40;

typedef int(__cdecl* SV_AddServerCommand_t)(int a1, int a2, char *a3);
SV_AddServerCommand_t sv_add_server_command;

void client_say(gentity_t* entity, team* t,char* msg)
{
	if (strstr(msg, "!bold"))
		base::scr::iprint_ln_bold(entity, msg);
	else
		base::scr::iprint_ln(entity, msg);
}

void client_connect(gentity_t* ent)
{
	char buffer[256];

	sprintf_s(buffer, "%s connected! \n", ent->shared.client->session.clientstate.name);

	base::sys_print(buffer);

}

void client_disconnect(gentity_t* ent)
{
	char buffer[256];

	sprintf_s(buffer, "%s disconnected!", ent->shared.client->session.clientstate.name);

	base::sys_print(buffer);
}

void player_damaged(gentity_t* player, gentity_t* inflictor, gentity_t* damager , int* damage, int* mod, int* weapon_index, bool* is_alternate_weapon, vec3_t direction, int* hit_location)
{
	char buffer[2048];

	char weapon_buffer[1024];

	bg_weapon(*weapon_index, 0, weapon_buffer, 1024);
	sprintf_s(buffer, "%s was damaged: %d with the weapon: %s", player->shared.client->session.clientstate.name, *damage,weapon_buffer);

	base::say_all(buffer);
}


void player_killed(gentity_t* player, gentity_t* inflictor, gentity_t* killer, int* damage, int* mod, int* weapon_index, bool* is_alternate_weapon, vec3_t direction, int* hit_location)
{
	char buffer[2048];

	char weapon_buffer[1024];

	bg_weapon(*weapon_index, 0, weapon_buffer, 1024);
	sprintf_s(buffer, "%s was killed by: %s with the weapon: %s", player->shared.client->session.clientstate.name, killer->shared.client->session.clientstate.name,weapon_buffer);

	base::say_all(buffer);
}

void client_spawned(gentity_t* player)
{
	char buffer[256];

	sprintf_s(buffer, "%s spawned!", player->shared.client->session.clientstate.name);

	base::say_all(buffer);
}

std::ofstream f("dump.txt");

int hk_sv_add_server_commands(int a1,int a2,char* a3)
{
	char buffer[2048];
	sprintf_s(buffer, "SV_AddServerCommands: %d || %s \n", a2, a3);

	f << buffer;

	f.flush();

	base::sys_print(buffer);

	return sv_add_server_command(a1, a2, a3);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
	    base::sys_print("Hay motherfucker I am here \n");
		base::install_g_say_callback(client_say);
		base::install_client_connected_callback(client_connect);
		base::install_client_disconnect_callback(client_disconnect);
		base::install_scr_player_damaged_callback(player_damaged);
		base::install_scr_player_killed_callback(player_killed);
		base::install_client_spawn_callback(client_spawned);

		sv_add_server_command = (SV_AddServerCommand_t)base::internal::detour_function((BYTE*)0x004FD690, (BYTE*)hk_sv_add_server_commands, 0x5);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

