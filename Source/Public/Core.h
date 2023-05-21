#pragma once

#include <string>

using namespace std;

struct Vector2
{
	float X, Y;

	Vector2()
		: X(0), Y(0)
	{}

	Vector2(const float _X, const float _Y)
		: X(_X), Y(_Y)
	{}
};
struct Vector3
{
	float X, Y, Z;

	Vector3()
		: X(0), Y(0), Z(0)
	{}

	Vector3(const float _X, const float _Y, const float _Z)
		: X(_X), Y(_Y), Z(_Z)
	{}
};


struct Scene
{
	string Filename;
	int FirstFtrame;
	int LastFtrame;
	int FrameSpeed;
	int TicksPerFrame;
	Vector3 BackgroundStatic;
	Vector3 AmbientStatic;
};

struct TextureInfo
{
	string Class;
	string Filename;
	string MapType;
	// UV
	Vector2 Offset;
	Vector2 Tiling;
};

struct MaterialInfo
{
	Vector3 Ambient;
	Vector3 Diffuse;
	Vector3 Specular;
	float Shine;
	float ShineStrength;
	float Transparency;
	string Shading;
	TextureInfo MapDiffuse;
};

struct Biped
{
	string PrivateName;
};
