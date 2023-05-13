#include "includes.h"
using namespace hazedumper::netvars;
using namespace hazedumper::signatures;

BOOL WINAPI GlowThread(HMODULE hModule)
{
	uintptr_t gameModule = (uintptr_t)GetModuleHandle("client.dll");

	for (; !GetAsyncKeyState(VK_END); std::this_thread::sleep_for(std::chrono::microseconds(1)))
	{
		uintptr_t localplayer = *(uintptr_t*)(gameModule + dwLocalPlayer);
		uintptr_t glowObjectManager = *(uintptr_t*)(gameModule + dwGlowObjectManager);
		uintptr_t EntityList = *(uintptr_t*)(gameModule + dwEntityList);

		if (localplayer == NULL) continue;

		uint32_t localteam = *(uint32_t*)(localplayer + m_iTeamNum);

		for (int x = 0; x < 32; x++)
		{
			uintptr_t Enemy = *(uintptr_t*)(gameModule + dwEntityList + x * 0x10);
			if (Enemy == NULL) continue;

			uint32_t GlowIndex = *(uint32_t*)(Enemy + m_iGlowIndex);
			uint32_t EntityTeam = *(uint32_t*)(Enemy + m_iTeamNum);

			if (EntityTeam != localteam)
			{
				*(float*)(glowObjectManager + GlowIndex * 0x38 + 0x4) = 1.0f; // R
				*(float*)(glowObjectManager + GlowIndex * 0x38 + 0x8) = 0.0f; // G
				*(float*)(glowObjectManager + GlowIndex * 0x38 + 0xC) = 0.0f; // B
				*(float*)(glowObjectManager + GlowIndex * 0x38 + 0x10) = 1.0f; // A
			}
			*(bool*)(glowObjectManager + GlowIndex * 0x38 + 0x24) = true;
			*(bool*)(glowObjectManager + GlowIndex * 0x38 + 0x25) = false;

		}

	}
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)GlowThread, NULL, NULL, NULL);
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}


