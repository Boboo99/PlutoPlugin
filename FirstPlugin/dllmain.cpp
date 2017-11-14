// dllmain.cpp : Definiert den Einstiegspunkt für die DLL-Anwendung.
#include "stdafx.h"
#include "plugin_base.h"
#include "datatypes.h"

typedef void(__cdecl* sys_print_t)(char* a1);
sys_print_t sys_print = (sys_print_t)0x004D8E80;

typedef char*(__cdecl* g_say_t)(gentity_t* entity, team t, char* msg);
g_say_t g_say = (g_say_t)0x0047E900;

typedef int(__cdecl* bg_weapon_t)(int weapon, int a1, char* buffer, int buffer_size);
bg_weapon_t bg_weapon = (bg_weapon_t)0x00421B40;

void client_say(gentity_t* entity, team* t,char* msg)
{
	*t = team::None;
	return;
}

void client_connect(gentity_t* ent)
{
	char buffer[256];

	sprintf_s(buffer, "%s connected! \n", ent->shared.client->session.clientstate.name);

	sys_print(buffer);

}

void client_disconnect(gentity_t* ent)
{
	char buffer[256];

	sprintf_s(buffer, "%s disconnected! \n", ent->shared.client->session.clientstate.name);

	sys_print(buffer);
}

void player_damaged(gentity_t* player, gentity_t* inflictor, gentity_t* damager , int* damage, int* mod, int* weapon_index, bool* is_alternate_weapon, vec3_t direction, int* hit_location)
{
	char buffer[2048];

	char weapon_buffer[1024];

	bg_weapon(*weapon_index, 0, weapon_buffer, 1024);
	sprintf_s(buffer, "%s was damaged: %d with the weapon: %s \n", player->shared.client->session.clientstate.name, *damage,weapon_buffer);

	g_say(player, player->shared.client->session.clientstate.current_team, buffer);
}


void player_killed(gentity_t* player, gentity_t* inflictor, gentity_t* killer, int* damage, int* mod, int* weapon_index, bool* is_alternate_weapon, vec3_t direction, int* hit_location)
{
	char buffer[2048];

	char weapon_buffer[1024];

	bg_weapon(*weapon_index, 0, weapon_buffer, 1024);
	sprintf_s(buffer, "%s was killed by: %s with the weapon: %s \n", player->shared.client->session.clientstate.name, killer->shared.client->session.clientstate.name,weapon_buffer);

	g_say(player, player->shared.client->session.clientstate.current_team, buffer);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		sys_print("Hay motherfucker I am here \n");
		base::install_g_say_callback(client_say);
		base::install_client_connected_callback(client_connect);
		base::install_client_disconnect_callback(client_disconnect);
		base::install_scr_player_damaged_callback(player_damaged);
		base::install_scr_player_killed_callback(player_killed);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

