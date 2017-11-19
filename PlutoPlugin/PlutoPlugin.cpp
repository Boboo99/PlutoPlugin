#include "stdafx.hpp"

namespace PlutoPlugin
{
	void LoadPlugins();
	void InstallHooks();

	void Startup()
	{
		// Install hooks
		InstallHooks();

		// Load all plugins
		LoadPlugins();
	}
}
