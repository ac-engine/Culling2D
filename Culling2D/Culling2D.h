#pragma once


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
#include <array>
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

namespace culling2d
{
	//----------------------------------------------------------------------------------
	//
	//----------------------------------------------------------------------------------
	/**
	@brief	最大値取得
	*/
	template <typename T, typename U>
	T Max(T t, U u)
	{
		if (t > (T)u)
		{
			return t;
		}
		return u;
	}

	/**
	@brief	最小値取得
	*/
	template <typename T, typename U>
	T Min(T t, U u)
	{
		if (t < (T)u)
		{
			return t;
		}
		return u;
	}

	/**
	@brief	範囲内値取得
	*/
	template <typename T, typename U, typename V>
	T Clamp(T t, U max_, V min_)
	{
		if (t > (T)max_)
		{
			t = (T)max_;
		}

		if (t < (T)min_)
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

	//----------------------------------------------------------------------------------
	//
	//----------------------------------------------------------------------------------
#ifdef _WIN32
	inline void Sleep(int32_t ms)
	{
		::Sleep(ms);
	}
#else
	inline void Sleep(int32_t ms)
	{
		usleep(1000 * ms);
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
			delete[](p);
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

#include <memory>
#include <atomic>

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace culling2d {
	//----------------------------------------------------------------------------------
	//
	//----------------------------------------------------------------------------------
	/**
	@brief	参照カウンタオブジェクト
	*/
	class ReferenceObject
	{
	private:
		mutable std::atomic<int32_t> m_reference;

	public:
		ReferenceObject();

		virtual ~ReferenceObject();

		virtual int AddRef();

		virtual int GetRef();

		virtual int Release();
	};
};


//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace culling2d
{
	//----------------------------------------------------------------------------------
	//
	//----------------------------------------------------------------------------------

	/**
	@brief	2次元ベクトル
	*/
	struct Vector2DF
	{
	public:
		/**
		@brief	X
		*/
		float	X;

		/**
		@brief	Y
		*/
		float	Y;

		/**
		@brief	コンストラクタ
		*/
		Vector2DF();

		/**
		@brief	コンストラクタ
		@param	x	X
		@param	y	Y
		*/
		Vector2DF(float x, float y);

		/**
		@brief	このベクトルの長さを取得する。
		*/
		float GetLength() const
		{
			return sqrt(GetSquaredLength());
		}

		/**
		@brief	このベクトルの長さの二乗を取得する。
		*/
		float GetSquaredLength() const
		{
			return X * X + Y * Y;
		}

		/**
		@brief	このベクトルの長さを設定する。
		*/
		void SetLength(float value)
		{
			float length = GetLength();
			(*this) *= (value / length);
		}

		/**
		@brief	このベクトルの単位ベクトルを取得する。
		*/
		Vector2DF GetNormal()
		{
			float length = GetLength();
			return Vector2DF(X / length, Y / length);
		}

		/**
		@brief	このベクトルの単位ベクトル化する。
		*/
		void Normalize()
		{
			float length = GetLength();
			(*this) /= length;
		}

		/**
		@brief	このベクトルの向きを弧度法で取得する。
		*/
		float GetRadian() const
		{
			return atan2(Y, X);
		}

		/**
		@brief	このベクトルの向きを弧度法で設定する。
		*/
		void SetRadian(float value)
		{
			float length = GetLength();
			SinCos(value, Y, X);
			X *= length;
			Y *= length;
		}

		/**
		@brief	このベクトルの向きを度数法で取得する。
		*/
		float GetDegree() const
		{
			return RadianToDegree(atan2(Y, X));
		}

		/**
		@brief	このベクトルの向きを度数法で設定する。
		*/
		void SetDegree(float value)
		{
			float length = GetLength();
			SinCos(DegreeToRadian(value), Y, X);
			X *= length;
			Y *= length;
		}

		bool operator==(const Vector2DF& right);

		bool operator!=(const Vector2DF& right);

		Vector2DF operator-();

		Vector2DF operator+(const Vector2DF& right);

		Vector2DF operator-(const Vector2DF& right);

		Vector2DF operator*(const Vector2DF& right);

		Vector2DF operator/(const Vector2DF& right);

		Vector2DF operator*(float right);

		Vector2DF operator/(float right);

		Vector2DF& operator+=(const Vector2DF& right);

		Vector2DF& operator-=(const Vector2DF& right);

		Vector2DF& operator*=(const Vector2DF& right);

		Vector2DF& operator/=(const Vector2DF& right);

		Vector2DF& operator*=(float right);

		Vector2DF& operator/=(float right);

		/**
		@brief	内積を取得する。
		@param	v1	値1
		@param	v2	値2
		*/
		static float Dot(const Vector2DF& v1, const Vector2DF& v2)
		{
			return v1.X * v2.X + v1.Y * v2.Y;
		}

		/**
		@brief	2点間の距離を取得する。
		@param	v1	値1
		@param	v2	値2
		*/
		static float Distance(const Vector2DF& v1, const Vector2DF& v2)
		{
			float dx = v1.X - v2.X;
			float dy = v1.Y - v2.Y;
			return sqrt(dx * dx + dy * dy);
		}
	};

	//----------------------------------------------------------------------------------
	//
	//----------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------


//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace culling2d
{
	//----------------------------------------------------------------------------------
	//
	//----------------------------------------------------------------------------------

	/**
	@brief	2次元ベクトル(整数)
	*/
	struct Vector2DI
	{
	public:
		/**
		@brief	X
		*/
		int32_t	X;

		/**
		@brief	Y
		*/
		int32_t	Y;

		/**
		@brief	コンストラクタ
		*/
		Vector2DI();

		/**
		@brief	コンストラクタ
		*/
		Vector2DI(int32_t x, int32_t y);

		bool operator == (const Vector2DI& o);
		bool operator != (const Vector2DI& o);

		Vector2DI operator-();

		Vector2DI operator+(const Vector2DI& right);

		Vector2DI operator-(const Vector2DI& right);

		Vector2DI operator*(const Vector2DI& right);

		Vector2DI operator/(const Vector2DI& right);

		Vector2DI operator*(int32_t right);

		Vector2DI operator/(int32_t right);

		Vector2DI& operator+=(const Vector2DI& right);

		Vector2DI& operator-=(const Vector2DI& right);

		Vector2DI& operator*=(const Vector2DI& right);

		Vector2DI& operator/=(const Vector2DI& right);

		Vector2DI& operator*=(int32_t right);

		Vector2DI& operator/=(int32_t right);
	};

	//----------------------------------------------------------------------------------
	//
	//----------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace culling2d {
	//----------------------------------------------------------------------------------
	//
	//----------------------------------------------------------------------------------
	/**
	@brief	3次元ベクトル
	*/
	struct Vector3DF
	{
	public:
		/**
		@brief	X
		*/
		float	X;

		/**
		@brief	Y
		*/
		float	Y;

		/**
		@brief	Z
		*/
		float	Z;

		/**
		@brief	コンストラクタ
		*/
		Vector3DF();

		/**
		@brief	コンストラクタ
		@param	x	X
		@param	y	Y
		@param	z	Z
		*/
		Vector3DF(float x, float y, float z);

		bool operator == (const Vector3DF& o);
		bool operator != (const Vector3DF& o);

		Vector3DF operator-();

		Vector3DF operator + (const Vector3DF& o) const;

		Vector3DF operator - (const Vector3DF& o) const;

		Vector3DF operator * (const Vector3DF& o) const;

		Vector3DF operator / (const Vector3DF& o) const;

		Vector3DF operator * (const float& o) const;

		Vector3DF operator / (const float& o) const;

		Vector3DF& operator += (const Vector3DF& o);

		Vector3DF& operator -= (const Vector3DF& o);

		Vector3DF& operator *= (const Vector3DF& o);

		Vector3DF& operator /= (const Vector3DF& o);

		Vector3DF& operator *= (const float& o);

		Vector3DF& operator /= (const float& o);


		/**
		@brief	このベクトルの長さを取得する。
		*/
		float GetLength() const
		{
			return sqrt(GetSquaredLength());
		}

		/**
		@brief	このベクトルの長さの二乗を取得する。
		*/
		float GetSquaredLength() const
		{
			return X * X + Y * Y + Z * Z;
		}

		/**
		@brief	このベクトルの長さを設定する。
		*/
		void SetLength(float value)
		{
			float length = GetLength();
			(*this) *= (value / length);
		}

		/**
		@brief	このベクトルの単位ベクトルを取得する。
		*/
		Vector3DF GetNormal()
		{
			float length = GetLength();
			return Vector3DF(X / length, Y / length, Z / length);
		}

		/**
		@brief	このベクトルの単位ベクトル化する。
		*/
		void Normalize()
		{
			float length = GetLength();
			(*this) /= length;
		}

		/**
		@brief	内積を取得する。
		*/
		static float Dot(const Vector3DF& v1, const Vector3DF& v2);

		/**
		@brief	外積を取得する。
		@note
		右手系の場合、右手の親指がv1、人差し指がv2としたとき、中指の方向を返す。<BR>
		左手系の場合、左手の親指がv1、人差し指がv2としたとき、中指の方向を返す。<BR>
		*/
		static Vector3DF Cross(const Vector3DF& v1, const Vector3DF& v2);

		/**
		@brief	2点間の距離を取得する。
		*/
		static float Distance(const Vector3DF& v1, const Vector3DF& v2);
	};

	//----------------------------------------------------------------------------------
	//
	//----------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------


//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace culling2d {
	//----------------------------------------------------------------------------------
	//
	//----------------------------------------------------------------------------------
	/**
	@brief	4次元ベクトル
	*/
	struct Vector4DF
	{
	public:
		/**
		@brief	X
		*/
		float	X;

		/**
		@brief	Y
		*/
		float	Y;

		/**
		@brief	Z
		*/
		float	Z;

		/**
		@brief	W
		*/
		float	W;

		/**
		@brief	コンストラクタ
		*/
		Vector4DF();

		/**
		@brief	コンストラクタ
		@param	x	X
		@param	y	Y
		@param	z	Z
		@param	w	W
		*/
		Vector4DF(float x, float y, float z, float w);


		/**
		@brief	このベクトルの長さを取得する。
		*/
		float GetLength() const
		{
			return sqrt(GetSquaredLength());
		}

		/**
		@brief	このベクトルの長さの二乗を取得する。
		*/
		float GetSquaredLength() const
		{
			return X * X + Y * Y + Z * Z + W * W;
		}

		/**
		@brief	このベクトルの長さを設定する。
		*/
		void SetLength(float value)
		{
			float length = GetLength();
			(*this) *= (value / length);
		}

		/**
		@brief	このベクトルの単位ベクトルを取得する。
		*/
		Vector4DF GetNormal()
		{
			float length = GetLength();
			return Vector4DF(X / length, Y / length, Z / length, W / length);
		}

		/**
		@brief	このベクトルの単位ベクトル化する。
		*/
		void Normalize()
		{
			float length = GetLength();
			(*this) /= length;
		}

		bool operator == (const Vector4DF& o);
		bool operator != (const Vector4DF& o);

		Vector4DF operator-();

		Vector4DF operator + (const Vector4DF& o) const;

		Vector4DF operator - (const Vector4DF& o) const;

		Vector4DF operator * (const Vector4DF& o) const;

		Vector4DF operator / (const Vector4DF& o) const;

		Vector4DF operator * (const float& o) const;

		Vector4DF operator / (const float& o) const;

		Vector4DF& operator += (const Vector4DF& o);

		Vector4DF& operator -= (const Vector4DF& o);

		Vector4DF& operator *= (const Vector4DF& o);

		Vector4DF& operator /= (const Vector4DF& o);

		Vector4DF& operator *= (const float& o);

		Vector4DF& operator /= (const float& o);

		/**
		@brief	内積を取得する。
		*/
		static float Dot(const Vector4DF& v1, const Vector4DF& v2);

		/**
		@brief	2点間の距離を取得する。
		*/
		static float Distance(const Vector4DF& v1, const Vector4DF& v2);
	};

	//----------------------------------------------------------------------------------
	//
	//----------------------------------------------------------------------------------
}



namespace culling2d
{
	/**
	@brief	3×3行列を表す構造体。
	@note
	[0,0][0,1]
	[1,0][1,1]
	*/
	struct Matrix33
	{
	public:
		/**
		@brief	オブジェクトを生成し、単位行列で初期化する。
		*/
		Matrix33();

		/**
		@brief	行列の値
		*/
		float Values[3][3];

		/**
		@brief	単位行列を設定する。
		*/
		Matrix33& SetIdentity();

		/**
		@brief	転置行列を設定する。
		@return	このインスタンスへの参照
		*/
		Matrix33& SetTransposed();

		/**
		@brief	逆行列を設定する。
		@return	このインスタンスへの参照
		*/
		Matrix33& SetInverted();

		/**
		@brief	逆行列を取得する。
		@return	逆行列
		*/
		Matrix33 GetInverted();

		/**
		@brief	平行移動の行列を設定する。
		*/
		Matrix33& SetTranslation(float x, float y);

		/**
		@brief	回転行列を設定する。
		*/
		Matrix33& SetRotation(float angle);

		/**
		@brief	拡大・縮小行列を設定する。
		*/
		Matrix33& SetScale(float x, float y);

		/**
		@brief	行列でベクトルを変形させる。
		@param	in	変形前ベクトル
		@return	変形後ベクトル
		*/
		Vector2DF Transform2D(const Vector2DF& in) const;

		/**
		@brief	行列でベクトルを変形させる。
		@param	in	変形前ベクトル
		@return	変形後ベクトル
		*/
		Vector3DF Transform3D(const Vector3DF& in) const;

		/**
		@brief	3×3行列の掛け算を計算する。
		*/
		Matrix33 operator*(const Matrix33& right);

		Vector3DF operator*(const Vector3DF& right);
	};
}


//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace culling2d {
	//----------------------------------------------------------------------------------
	//
	//----------------------------------------------------------------------------------

	/**
	@brief	4×4行列を表す構造体
	@note
	M * V[x,y,z,1] の形<BR>
	[0,0][0,1][0,2][0,3]
	[1,0][1,1][1,2][1,3]
	[2,0][2,1][2,2][2,3]
	[3,0][3,1][3,2][3,3]
	*/
	struct Matrix44
	{
	private:

	public:

		/**
		@brief	オブジェクトを生成し、単位行列で初期化する。
		*/
		Matrix44();

		/**
		@brief	行列の値
		*/
		float	Values[4][4];

		/**
		@brief	単位行列を設定する。
		@return	このインスタンスへの参照
		*/
		Matrix44& SetIndentity();

		/**
		@brief	転置行列を設定する。
		@return	このインスタンスへの参照
		*/
		Matrix44& SetTransposed();

		/**
		@brief	逆行列を設定する。
		@return	このインスタンスへの参照
		*/
		Matrix44& SetInverted();

		/**
		@brief	逆行列を取得する。
		@return	逆行列
		*/
		Matrix44 GetInverted();


		/**
		@brief	カメラ行列(右手系)を設定する。
		@param	eye	カメラの位置
		@param	at	カメラの注視点
		@param	up	カメラの上方向
		@return	このインスタンスへの参照
		*/
		Matrix44& SetLookAtRH(const Vector3DF& eye, const Vector3DF& at, const Vector3DF& up);

		/**
		@brief	カメラ行列(左手系)を設定する。
		@param	eye	カメラの位置
		@param	at	カメラの注視点
		@param	up	カメラの上方向
		@return	このインスタンスへの参照
		*/
		Matrix44& SetLookAtLH(const Vector3DF& eye, const Vector3DF& at, const Vector3DF& up);

		/**
		@brief	射影行列(右手系)を設定する。
		@param	ovY	Y方向への視野角(ラジアン)
		@param	aspect	画面のアスペクト比
		@param	zn	最近距離
		@param	zf	最遠距離
		@return	このインスタンスへの参照
		*/
		Matrix44& SetPerspectiveFovRH(float ovY, float aspect, float zn, float zf);

		/**
		@brief	OpenGL用射影行列(右手系)を設定する。
		@param	ovY	Y方向への視野角(ラジアン)
		@param	aspect	画面のアスペクト比
		@param	zn	最近距離
		@param	zf	最遠距離
		@return	このインスタンスへの参照
		*/
		Matrix44& SetPerspectiveFovRH_OpenGL(float ovY, float aspect, float zn, float zf);

		/**
		@brief	射影行列(左手系)を設定する。
		@param	ovY	Y方向への視野角(ラジアン)
		@param	aspect	画面のアスペクト比
		@param	zn	最近距離
		@param	zf	最遠距離
		@return	このインスタンスへの参照
		*/
		Matrix44& SetPerspectiveFovLH(float ovY, float aspect, float zn, float zf);

		/**
		@brief	正射影行列(右手系)を設定する。
		@param	width	横幅
		@param	height	縦幅
		@param	zn	最近距離
		@param	zf	最遠距離
		@return	このインスタンスへの参照
		*/
		Matrix44& SetOrthographicRH(float width, float height, float zn, float zf);

		/**
		@brief	正射影行列(左手系)を設定する。
		@param	width	横幅
		@param	height	縦幅
		@param	zn	最近距離
		@param	zf	最遠距離
		@return	このインスタンスへの参照
		*/
		Matrix44& SetOrthographicLH(float width, float height, float zn, float zf);

		/**
		@brief	並行移動行列を設定する。
		@param	x	X方向移動量
		@param	y	Y方向移動量
		@param	z	Z方向移動量
		@return	このインスタンスへの参照
		*/
		Matrix44& SetTranslation(float x, float y, float z);

		/**
		@brief	X軸回転行列(右手)を設定する。
		@param	angle	X軸回転量(ラジアン)
		@return	このインスタンスへの参照
		*/
		Matrix44& SetRotationX(float angle);

		/**
		@brief	Y軸回転行列(右手)を設定する。
		@param	angle	Y軸回転量(ラジアン)
		@return	このインスタンスへの参照
		*/
		Matrix44& SetRotationY(float angle);

		/**
		@brief	Z軸回転行列(右手)を設定する。
		@param	angle	Z軸回転量(ラジアン)
		@return	このインスタンスへの参照
		*/
		Matrix44& SetRotationZ(float angle);

		/**
		@brief	任意軸の反時計回転行列(右手)を設定する。
		@param	axis	軸
		@param	angle	回転量(ラジアン)
		@return	このインスタンスへの参照
		*/
		Matrix44& SetRotationAxis(const Vector3DF& axis, float angle);

		/**
		@brief	クオータニオンを元に回転行列(右手)を設定する。
		@param	x	クオータニオン
		@param	y	クオータニオン
		@param	z	クオータニオン
		@param	w	クオータニオン
		@return	このインスタンスへの参照
		*/
		Matrix44& SetQuaternion(float x, float y, float z, float w);

		/**
		@brief	拡大行列を設定する。
		@param	x	X方向拡大率
		@param	y	Y方向拡大率
		@param	z	Z方向拡大率
		@return	このインスタンスへの参照
		*/
		Matrix44& SetScale(float x, float y, float z);

		/**
		@brief	行列でベクトルを変形させる。
		@param	in	変形前ベクトル
		@return	変形後ベクトル
		*/
		Vector3DF Transform3D(const Vector3DF& in) const;

		/**
		@brief	行列でベクトルを変形させる。
		@param	in	変形前ベクトル
		@return	変形後ベクトル
		*/
		Vector4DF Transform4D(const Vector4DF& in) const;

		Matrix44 operator * (const Matrix44& right) const;

		Vector3DF operator*(const Vector3DF& right) const;

		Vector4DF operator*(const Vector4DF& right) const;

		/**
		@brief	乗算を行う。
		@param	o	出力先
		@param	in1	行列1
		@param	in2	行列2
		@return	出力先の参照
		*/
		static Matrix44& Mul(Matrix44& o, const Matrix44& in1, const Matrix44& in2);

	};

	//----------------------------------------------------------------------------------
	//
	//----------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------

namespace culling2d
{
	struct Circle
	{
		Vector2DF Position;
		float Radius;

		Circle()
		{
			Position = culling2d::Vector2DF(0, 0);
			Radius = 0;
		}

		Circle(Vector2DF position, float radius)
		{
			Position = position;
			Radius = radius;
		}

		bool operator==(Circle circle) {
			return Position == circle.Position&&Radius == circle.Radius;
		}

		bool operator!=(Circle circle)
		{
			return Position != circle.Position || Radius != circle.Radius;
		}
	};
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace culling2d {
	//----------------------------------------------------------------------------------
	//
	//----------------------------------------------------------------------------------
	/**
	@brief	長方形(浮動小数点)の構造体
	*/
	struct RectF
	{
	public:
		/**
		@brief	左上X座標
		*/
		float X;

		/**
		@brief	左上Y座標
		*/
		float Y;

		/**
		@brief	横幅
		*/
		float Width;

		/**
		@brief	縦幅
		*/
		float Height;

		/**
		@brief	コンストラクタ
		*/
		RectF();

		/**
		@brief	コンストラクタ
		@param	x	左上X座標
		@param	y	左上Y座標
		@param	width	横幅
		@param	height	縦幅
		*/
		RectF(float x, float y, float width, float height);

		/**
		@brief	左上座標を取得する。
		@return	左上座標
		*/
		Vector2DF GetPosition() const;

		/**
		@brief	大きさを取得する。
		@return	大きさ
		*/
		Vector2DF GetSize() const;

		/**
		@brief	四隅の座標を(X,Y)、(X+Width,Y)、(X+Width,Y+Height)、(X,Y+Height)の順に配列として取得する。
		@return	座標
		*/
		std::array<Vector2DF, 4> GetVertexes() const;

		/**
		@brief	円と衝突しているか否かを調べる。
		@param circle 円
		@return	衝突しているか否か
		*/
		bool GetCollision(Circle circle);
	};

	//----------------------------------------------------------------------------------
	//
	//----------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace culling2d
{
	/**
	@brief	長方形(整数)の構造体
	*/
	struct RectI
	{
	public:
		/**
		@brief	左上X座標
		*/
		int X;

		/**
		@brief	左上Y座標
		*/
		int Y;

		/**
		@brief	横幅
		*/
		int Width;

		/**
		@brief	縦幅
		*/
		int Height;

		/**
		@brief	コンストラクタ
		*/
		RectI();

		/**
		@brief	コンストラクタ
		@param	x	左上X座標
		@param	y	左上Y座標
		@param	width	横幅
		@param	height	縦幅
		*/
		RectI(int x, int y, int width, int height);

		/**
		@brief	左上座標を取得する。
		@return	左上座標
		*/
		Vector2DI GetPosition() const;

		/**
		@brief	大きさを取得する。
		@return	大きさ
		*/
		Vector2DI GetSize() const;

		/**
		@brief	四隅の座標を(X,Y)、(X+Width,Y)、(X+Width,Y+Height)、(X,Y+Height)の順に配列として取得する。
		@return	座標
		*/
		std::array<Vector2DI, 4> GetVertexes() const;

		bool operator == (const RectI& other) const;
	};
}

namespace culling2d
{
	class Layer;
	class World;
	class Object;
	class Grid;
}

namespace culling2d
{
	class Layer
		:public ReferenceObject
	{
		int resolution;
		std::vector<Grid*> grids;

	public:
		Layer(int resolution);
		~Layer();

		int GetResolution() const;
		const std::vector<Grid*> &GetGrids();
		void AddGrid(Grid* grid);
		void RemoveGrid(Grid* grid);
	};
}

namespace culling2d
{
	class World
		:public ReferenceObject
	{
		friend Object;
		int resolution;
		int maxResolution;
		RectF worldRange;
		int nextID;
		std::vector<Layer*> layers;
		std::vector<Object*> tempObjects;
		std::set<Object*> improperObjects;
		std::map<Object*, Grid*> mapObjectToGrid;

		void initQuadtreeGrids(int layerResolution, RectF range);
		void initQuadtree();

		Grid* searchDestinationGrid(Object * object);
		void NotifyMoved(Object *object);
	public:
		World(int resolution, RectF worldRange);
		~World();

		std::vector<Object*> &GetCullingObjects(RectF cullingRange);
		void Update();
		int GetResolution() const;
		int RecalculateResolution();
		RectF GetWorldRange() const;
		Grid* AddObject(Object* object);
		bool RemoveObject(Object* object);

		void ResetNextID();
	};
}

namespace culling2d
{
	class World;
	class Grid;

	class Object
		:public ReferenceObject
	{
		friend World;
		Circle circle;
		void *userData;
		World *worldRef;

		RectF currentRange;
		unsigned long id;
		Object(void* userdata, World *worldRef);

		void SetID(unsigned long id);
	public:
		~Object();

		const Circle& GetCircle() const;
		void SetCircle(Circle circle);
		void* GetUserData() const;
		void SetUserData(void* userData);

		RectF GetCurrentRange() const;
		void SetCurrentRange(RectF range);

		bool IsProperPosition() const;

		unsigned long GetID() const;

		static Object* Create(void *userdata, World* worldRef);
	};
}

namespace culling2d
{
	class Grid
		:public ReferenceObject
	{
		int resolutionLevel;
		RectF gridRange;
		int index;
		std::set<Object*> objects;
		static std::array<int, 4> childrenIndices;
	public:
		Grid(int resolutionLevel, RectF gridRange);
		~Grid();
		int GetResolutionLevel() const;
		RectF GetGridRange() const;

		int GetCullingObjects(RectF cullingRange, std::vector<Object*> &cullingObjects);

		static std::array<int, 4> &GetChildrenIndices(int index, int currentResolution);

		bool AddObject(Object* object);
		bool RemoveObject(Object* object);
	};
}