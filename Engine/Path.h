#pragma once

namespace Constants
{
	const char* const CUBE = "../Engine/data/Models/cube.txt";
	const char* const SPHERE = "../Engine/data/Models/sphere.txt";

	const WCHAR* const WALL01 = L"../Engine/data/Textures/wall01.dds";
	const WCHAR* const WALL02 = L"../Engine/data/Textures/wall02.dds";
	const WCHAR* const ICE = L"../Engine/data/Textures/ice.dds";
	const WCHAR* const METAL = L"../Engine/data/Textures/metal.dds";
	const WCHAR* const TERRAIN = L"../Engine/data/Textures/terrain.dds";
	const WCHAR* const MARBLE = L"../Engine/data/Textures/marble.dds";

	const int SHADOWMAP_WIDTH = 1024;
	const int SHADOWMAP_HEIGHT = 1024;
	const float SHADOWMAP_DEPTH = 50.0f;
	const float SHADOWMAP_NEAR = 1.0f;

	const int SCREEN_WIDTH = 1024;
	const int  SCREEN_HEIGHT = 768;
	const bool FULL_SCREEN = true;
	const bool VSYNC_ENABLED = true;
	const float SCREEN_DEPTH = 100.0f;
	const float SCREEN_NEAR = 1.0f;
}
