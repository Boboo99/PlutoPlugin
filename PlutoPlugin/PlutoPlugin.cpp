#include "stdafx.hpp"

namespace PlutoPlugin
{
	void LoadPlugins();

	void Startup()
	{
		// Install hooks
		// TODO

		// Load all plugins
		LoadPlugins();
	}
}
