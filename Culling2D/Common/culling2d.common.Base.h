﻿#pragma once

//----------------------------------------------------------------------------------
// Include
//----------------------------------------------------------------------------------
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>

#include <vector>
#include <string>
#include <set>
#include <map>
#include <list>
#include <algorithm>
#include <functional>

#include <memory>

#include <assert.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
/**
	文字コード
	MSVC		sizeof(wchar_t)==2
	gcc(cygwin)	sizeof(wchar_t)==2
	gcc(linux)	sizeof(wchar_t)==4
*/
namespace culling2d
{
#ifdef _WIN32
typedef wchar_t achar;
typedef std::wstring astring;
#else 
typedef uint16_t achar;
typedef std::basic_string<uint16_t> astring;
#endif
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------

# if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#   define CULLING2D_STDCALL __stdcall
# else
#   define CULLING2D_STDCALL
# endif 

# if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#   define CULLING2D_DLLEXPORT __declspec(dllexport)
# else
#   define CULLING2D_DLLEXPORT
# endif 



//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace culling2d
{
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
struct Vector2DF;
struct Vector2DI;
struct Vector3DF;
struct Vector4DF;
struct Matrix43;
struct Matrix44;
struct RectF;
struct RectI;
struct Circle;

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
/**
	@brief	最大値取得
*/
template <typename T,typename U>
T Max( T t, U u )
{
	if( t > (T)u )
	{
		return t;
	}
	return u;
}

/**
	@brief	最小値取得
*/
template <typename T,typename U>
T Min( T t, U u )
{
	if( t < (T)u )
	{
		return t;
	}
	return u;
}

/**
	@brief	範囲内値取得
*/
template <typename T,typename U,typename V>
T Clamp( T t, U max_, V min_ )
{
	if( t > (T)max_ )
	{
		t = (T)max_;
	}

	if( t < (T)min_ )
	{
		t = (T)min_;
	}

	return t;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
inline float NormalizeAngle(float angle)
{
	int32_t ofs = (*(int32_t*)&angle & 0x80000000) | 0x3F000000; 
	return (angle - ((int)(angle * 0.159154943f + *(float*)&ofs) * 6.283185307f)); 
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
inline void SinCos(float x, float& s, float& c)
{
	x = NormalizeAngle(x);
	float x2 = x * x;
	float x4 = x * x * x * x;
	float x6 = x * x * x * x * x * x;
	float x8 = x * x * x * x * x * x * x * x;
	float x10 = x * x * x * x * x * x * x * x * x * x;
	s = x * (1.0f - x2 / 6.0f + x4 / 120.0f - x6 / 5040.0f + x8 / 362880.0f - x10 / 39916800.0f);
	c = 1.0f - x2 / 2.0f + x4 / 24.0f - x6 / 720.0f + x8 / 40320.0f - x10 / 3628800.0f;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------

/**
@brief	文字コードを変換する。(UTF16 -> UTF8)
@param	dst	[out]	出力配列の先頭ポインタ
@param	dst_size	[in]	出力配列の長さ
@param	src			[in]	入力配列の先頭ポインタ
@return	文字数
*/
int32_t Utf16ToUtf8(int8_t* dst, int32_t dst_size, const int16_t* src);

/**
	@brief	文字コードを変換する。(UTF8 -> UTF16)
	@param	dst			[out]	出力配列の先頭ポインタ
	@param	dst_size	[in]	出力配列の長さ
	@param	src			[in]	入力配列の先頭ポインタ
	@return	文字数
*/
int32_t Utf8ToUtf16(int16_t* dst, int32_t dst_size, const int8_t* src);

std::wstring ToWide(const char* pText);

astring ToAString(const wchar_t* src);

astring ToAString(const char* src);

std::string ToUtf8String(const achar* src);

astring ReplaceAll(const astring text, const achar* from, const achar* to);

astring CombinePath(const achar* rootPath, const achar* path);

#if !_WIN32 && !SWIG
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
static astring ReplaceAll(const astring text, const wchar_t* from, const wchar_t* to)
{
	return ReplaceAll(text, ToAString(from).c_str(), ToAString(to).c_str());
}
#endif

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#if !SWIG
void ShowMessageBox(const achar* title, const achar* text);

#if _WIN32
#define SPRINTF sprintf_s
#else
#define SPRINTF snprintf
#endif

#define CULLING2D_ASSERT(condition, message) { \
if (!(condition)) { \
	char lbuf[100]; \
	SPRINTF(lbuf, 100, "%d", __LINE__); \
	auto m = ::ace::ToAString(message); \
	auto f = ::ace::ToAString(__FILE__); \
	auto l = ::ace::ToAString(lbuf); \
	auto state = f + ::ace::ToAString("(") + l + ::ace::ToAString(")"); \
	auto m_ = state + ::ace::ToAString("\n") + m; \
	::ace::ShowMessageBox(::ace::ToAString("Assert").c_str(), m_.c_str()); \
	(*((int*)0x0) = 0x0);  } \
}

#endif

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#ifdef _WIN32
inline void Sleep( int32_t ms )
{
	::Sleep( ms );
}
#else
inline void Sleep( int32_t ms )
{
	usleep( 1000 * ms );
}
#endif

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
template <class T>
void SafeAddRef(T& t)
{
	if (t != NULL)
	{
		t->AddRef();
	}
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
template <class T>
void SafeRelease(T& t)
{
	if (t != NULL)
	{
		t->Release();
		t = NULL;
	}
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
template <class T>
void SafeSubstitute(T& target, T& value)
{
	SafeAddRef(value);
	SafeRelease(target);
	target = value;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
template <typename T>
inline void SafeDelete(T*& p)
{
	if (p != NULL)
	{
		delete (p);
		(p) = NULL;
	}
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
template <typename T>
inline void SafeDeleteArray(T*& p)
{
	if (p != NULL)
	{
		delete[] (p);
		(p) = NULL;
	}
}


const float PI = 3.14159265358979f;

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
static float DegreeToRadian(float degree)
{
	return degree / 180.0f * PI;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
static float RadianToDegree(float radian)
{
	return radian / PI * 180.0f;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
static std::vector<int8_t> GetBinaryData(astring filePath)
{
	FILE* fp = nullptr;

#if _WIN32
	_wfopen_s(&fp, filePath.c_str(), L"rb");
	if (fp == nullptr) return std::vector<int8_t>();
#else
	fp = fopen(ToUtf8String(filePath.c_str()).c_str(), "rb");
	if (fp == nullptr) return std::vector<int8_t>();
#endif

	fseek(fp, 0, SEEK_END);
	auto size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	std::vector<int8_t> data;
	data.resize(size);

	fread(&(data[0]), 1, size, fp);
	fclose(fp);

	return data;
}
}

