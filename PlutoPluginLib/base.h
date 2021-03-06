#pragma once
#include "datatypes.h"
#include <functional>
namespace base
{

	void install_g_say_callback(std::function<void(gentity_t*, team*, char*)> callback);
	void install_client_connected_callback(std::function<void(gentity_t*)> callback);
	void install_client_disconnect_callback(std::function<void(gentity_t*)> callback);
	void install_scr_player_killed_callback(std::function<void(gentity_t*, gentity_t*, gentity_t*, int*, int*, int*, bool*, vec3_t, int*)> callback);
	void install_scr_player_damaged_callback(std::function<void(gentity_t*, gentity_t*, gentity_t*, int*, int*, int*, bool*, vec3_t, int*)> callback);
	void install_client_spawn_callback(std::function<void(gentity_t*)> callback);

	void say_all(char* message);
	void sys_print(char* message);

	namespace internal
	{
		typedef char*(__cdecl* g_say_t)(gentity_t* entity, team team, char* msg);
		typedef void(__cdecl* scr_player_killed_t)(gentity_t* player_who_died, gentity_t* inflictor, gentity_t* killer, int damage, int mod, int weapon_index, bool is_alternate_weapon, vec3_t direction, int hit_location, int unkown_0, int unknow_1);
		typedef void(__cdecl* scr_player_damaged_t)(gentity_t* player_who_was_damaged, gentity_t* inflictor, gentity_t* player_who_damanged, int damage, int unknown_0, int mod, int weapon_index, bool is_alternate_weapon, vec3_t direction, int unknown_1, int hit_location, int unknown_2);
		typedef void(__cdecl* client_spawn_t)(gentity_t* entity, vec3_t spawn_position, vec3_t view_angle);

		typedef DWORD(__cdecl* sv_send_server_command_t)(int a1, int a2, char* msg, ...);
		typedef void(__cdecl* sys_print_t)(char* message);

		static g_say_t g_say_pointer_ = nullptr;
		static scr_player_killed_t scr_player_killed_pointer_ = nullptr;
		static scr_player_damaged_t scr_player_damaged_pointer_ = nullptr;
		static client_spawn_t client_spawn_pointer_ = nullptr;

		static sv_send_server_command_t sv_send_server_command_pointer_ = (sv_send_server_command_t)0x004FD8E0;
		static sys_print_t sys_print_pointer_ = (sys_print_t)0x004D8E80;

		static std::function<void(gentity_t*, team*, char*)> g_say_callback_ = nullptr;;
		static std::function<void(gentity_t*)> client_connect_callback_ = nullptr;;
		static std::function<void(gentity_t*)> client_disconnect_callback_ = nullptr;
		static std::function<void(gentity_t*, gentity_t*, gentity_t*, int*, int*, int*, bool*, vec3_t, int*)> scr_player_killed_callback_ = nullptr;
		static std::function<void(gentity_t*, gentity_t*, gentity_t*, int*, int*, int*, bool*, vec3_t, int*)> scr_player_damaged_callback_ = nullptr;
		static std::function<void(gentity_t*)> client_spawn_callback_ = nullptr;


		static bool exec_ent_thread_hook_set = false;

		void exec_ent_thread_num_helper(int function_handle, int object_ref);

		char* hk_g_say(gentity_t* entity, team team, char* msg);
		void hk_scr_player_killed(gentity_t* player_who_died, gentity_t* inflictor, gentity_t* killer, int damage, int mod, int weapon_index, bool is_alternate_weapon, vec3_t direction, int hit_location, int unkown_0, int unknow_1);
		void hk_scr_player_damaged(gentity_t* player_who_was_damaged, gentity_t* inflictor, gentity_t* player_who_damanged, int damage, int unknown_0, int mod, int weapon_index, bool is_alternate_weapon, vec3_t direction, int unknown_1, int hit_location, int unknown_2);
		void hk_client_spawn(gentity_t* entity, vec3_t spawn_position, vec3_t view_angle);

		void* detour_function(BYTE * src, const BYTE * dst, const int len);
	}
}
