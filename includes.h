#pragma once

#include <iostream>
#include <Windows.h>
#include <string>

#include <thread>
#include <chrono> 


#include "sdk/skCrypter.h"
#include "sdk/memory.h"
#include "sdk/csgo.hpp"

#include <numbers>
#include <cmath>


using namespace hazedumper;
using namespace netvars;
using namespace signatures;

p_module client_dll;
p_module engine_dll;
memory mem;

struct GlowObjectDefinition_t {
    DWORD pEntity;
    float r;
    float g;
    float b;
    float a;
    uint8_t _padding1[16];
    bool m_bRenderWhenOccluded;
    bool m_bRenderWhenUnoccluded;
    bool m_bFullBloomRender;
    uint8_t _padding2[5];
    int m_nFullBloomStencilTestValue;
    int m_nRenderStyle;
    uint8_t _padding3[12];
};


std::string random_string(int length)
{
	const char* charmap = Crypt("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890");
	std::string result;
	srand(time(NULL));
	for (int i = 0; i < length; ++i)
	{
		result += charmap[rand() % 52];
	}
	return result;

}