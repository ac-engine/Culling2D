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
�����R�[�h
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
	@brief	�ő�l�擾
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
	@brief	�ŏ��l�擾
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
	@brief	�͈͓��l�擾
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
	@brief	�����R�[�h��ϊ�����B(UTF16 -> UTF8)
	@param	dst	[out]	�o�͔z��̐擪�|�C���^
	@param	dst_size	[in]	�o�͔z��̒���
	@param	src			[in]	���͔z��̐擪�|�C���^
	@return	������
	*/
	int32_t Utf16ToUtf8(int8_t* dst, int32_t dst_size, const int16_t* src);

	/**
	@brief	�����R�[�h��ϊ�����B(UTF8 -> UTF16)
	@param	dst			[out]	�o�͔z��̐擪�|�C���^
	@param	dst_size	[in]	�o�͔z��̒���
	@param	src			[in]	���͔z��̐擪�|�C���^
	@return	������
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
	@brief	�Q�ƃJ�E���^�I�u�W�F�N�g
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
	@brief	2�����x�N�g��
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
		@brief	�R���X�g���N�^
		*/
		Vector2DF();

		/**
		@brief	�R���X�g���N�^
		@param	x	X
		@param	y	Y
		*/
		Vector2DF(float x, float y);

		/**
		@brief	���̃x�N�g���̒������擾����B
		*/
		float GetLength() const
		{
			return sqrt(GetSquaredLength());
		}

		/**
		@brief	���̃x�N�g���̒����̓����擾����B
		*/
		float GetSquaredLength() const
		{
			return X * X + Y * Y;
		}

		/**
		@brief	���̃x�N�g���̒�����ݒ肷��B
		*/
		void SetLength(float value)
		{
			float length = GetLength();
			(*this) *= (value / length);
		}

		/**
		@brief	���̃x�N�g���̒P�ʃx�N�g�����擾����B
		*/
		Vector2DF GetNormal()
		{
			float length = GetLength();
			return Vector2DF(X / length, Y / length);
		}

		/**
		@brief	���̃x�N�g���̒P�ʃx�N�g��������B
		*/
		void Normalize()
		{
			float length = GetLength();
			(*this) /= length;
		}

		/**
		@brief	���̃x�N�g���̌������ʓx�@�Ŏ擾����B
		*/
		float GetRadian() const
		{
			return atan2(Y, X);
		}

		/**
		@brief	���̃x�N�g���̌������ʓx�@�Őݒ肷��B
		*/
		void SetRadian(float value)
		{
			float length = GetLength();
			SinCos(value, Y, X);
			X *= length;
			Y *= length;
		}

		/**
		@brief	���̃x�N�g���̌�����x���@�Ŏ擾����B
		*/
		float GetDegree() const
		{
			return RadianToDegree(atan2(Y, X));
		}

		/**
		@brief	���̃x�N�g���̌�����x���@�Őݒ肷��B
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
		@brief	���ς��擾����B
		@param	v1	�l1
		@param	v2	�l2
		*/
		static float Dot(const Vector2DF& v1, const Vector2DF& v2)
		{
			return v1.X * v2.X + v1.Y * v2.Y;
		}

		/**
		@brief	2�_�Ԃ̋������擾����B
		@param	v1	�l1
		@param	v2	�l2
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
	@brief	2�����x�N�g��(����)
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
		@brief	�R���X�g���N�^
		*/
		Vector2DI();

		/**
		@brief	�R���X�g���N�^
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
	@brief	3�����x�N�g��
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
		@brief	�R���X�g���N�^
		*/
		Vector3DF();

		/**
		@brief	�R���X�g���N�^
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
		@brief	���̃x�N�g���̒������擾����B
		*/
		float GetLength() const
		{
			return sqrt(GetSquaredLength());
		}

		/**
		@brief	���̃x�N�g���̒����̓����擾����B
		*/
		float GetSquaredLength() const
		{
			return X * X + Y * Y + Z * Z;
		}

		/**
		@brief	���̃x�N�g���̒�����ݒ肷��B
		*/
		void SetLength(float value)
		{
			float length = GetLength();
			(*this) *= (value / length);
		}

		/**
		@brief	���̃x�N�g���̒P�ʃx�N�g�����擾����B
		*/
		Vector3DF GetNormal()
		{
			float length = GetLength();
			return Vector3DF(X / length, Y / length, Z / length);
		}

		/**
		@brief	���̃x�N�g���̒P�ʃx�N�g��������B
		*/
		void Normalize()
		{
			float length = GetLength();
			(*this) /= length;
		}

		/**
		@brief	���ς��擾����B
		*/
		static float Dot(const Vector3DF& v1, const Vector3DF& v2);

		/**
		@brief	�O�ς��擾����B
		@note
		�E��n�̏ꍇ�A�E��̐e�w��v1�A�l�����w��v2�Ƃ����Ƃ��A���w�̕�����Ԃ��B<BR>
		����n�̏ꍇ�A����̐e�w��v1�A�l�����w��v2�Ƃ����Ƃ��A���w�̕�����Ԃ��B<BR>
		*/
		static Vector3DF Cross(const Vector3DF& v1, const Vector3DF& v2);

		/**
		@brief	2�_�Ԃ̋������擾����B
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
	@brief	4�����x�N�g��
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
		@brief	�R���X�g���N�^
		*/
		Vector4DF();

		/**
		@brief	�R���X�g���N�^
		@param	x	X
		@param	y	Y
		@param	z	Z
		@param	w	W
		*/
		Vector4DF(float x, float y, float z, float w);


		/**
		@brief	���̃x�N�g���̒������擾����B
		*/
		float GetLength() const
		{
			return sqrt(GetSquaredLength());
		}

		/**
		@brief	���̃x�N�g���̒����̓����擾����B
		*/
		float GetSquaredLength() const
		{
			return X * X + Y * Y + Z * Z + W * W;
		}

		/**
		@brief	���̃x�N�g���̒�����ݒ肷��B
		*/
		void SetLength(float value)
		{
			float length = GetLength();
			(*this) *= (value / length);
		}

		/**
		@brief	���̃x�N�g���̒P�ʃx�N�g�����擾����B
		*/
		Vector4DF GetNormal()
		{
			float length = GetLength();
			return Vector4DF(X / length, Y / length, Z / length, W / length);
		}

		/**
		@brief	���̃x�N�g���̒P�ʃx�N�g��������B
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
		@brief	���ς��擾����B
		*/
		static float Dot(const Vector4DF& v1, const Vector4DF& v2);

		/**
		@brief	2�_�Ԃ̋������擾����B
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
	@brief	3�~3�s���\���\���́B
	@note
	[0,0][0,1]
	[1,0][1,1]
	*/
	struct Matrix33
	{
	public:
		/**
		@brief	�I�u�W�F�N�g�𐶐����A�P�ʍs��ŏ���������B
		*/
		Matrix33();

		/**
		@brief	�s��̒l
		*/
		float Values[3][3];

		/**
		@brief	�P�ʍs���ݒ肷��B
		*/
		Matrix33& SetIdentity();

		/**
		@brief	�]�u�s���ݒ肷��B
		@return	���̃C���X�^���X�ւ̎Q��
		*/
		Matrix33& SetTransposed();

		/**
		@brief	�t�s���ݒ肷��B
		@return	���̃C���X�^���X�ւ̎Q��
		*/
		Matrix33& SetInverted();

		/**
		@brief	�t�s����擾����B
		@return	�t�s��
		*/
		Matrix33 GetInverted();

		/**
		@brief	���s�ړ��̍s���ݒ肷��B
		*/
		Matrix33& SetTranslation(float x, float y);

		/**
		@brief	��]�s���ݒ肷��B
		*/
		Matrix33& SetRotation(float angle);

		/**
		@brief	�g��E�k���s���ݒ肷��B
		*/
		Matrix33& SetScale(float x, float y);

		/**
		@brief	�s��Ńx�N�g����ό`������B
		@param	in	�ό`�O�x�N�g��
		@return	�ό`��x�N�g��
		*/
		Vector2DF Transform2D(const Vector2DF& in) const;

		/**
		@brief	�s��Ńx�N�g����ό`������B
		@param	in	�ό`�O�x�N�g��
		@return	�ό`��x�N�g��
		*/
		Vector3DF Transform3D(const Vector3DF& in) const;

		/**
		@brief	3�~3�s��̊|���Z���v�Z����B
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
	@brief	4�~4�s���\���\����
	@note
	M * V[x,y,z,1] �̌`<BR>
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
		@brief	�I�u�W�F�N�g�𐶐����A�P�ʍs��ŏ���������B
		*/
		Matrix44();

		/**
		@brief	�s��̒l
		*/
		float	Values[4][4];

		/**
		@brief	�P�ʍs���ݒ肷��B
		@return	���̃C���X�^���X�ւ̎Q��
		*/
		Matrix44& SetIndentity();

		/**
		@brief	�]�u�s���ݒ肷��B
		@return	���̃C���X�^���X�ւ̎Q��
		*/
		Matrix44& SetTransposed();

		/**
		@brief	�t�s���ݒ肷��B
		@return	���̃C���X�^���X�ւ̎Q��
		*/
		Matrix44& SetInverted();

		/**
		@brief	�t�s����擾����B
		@return	�t�s��
		*/
		Matrix44 GetInverted();


		/**
		@brief	�J�����s��(�E��n)��ݒ肷��B
		@param	eye	�J�����̈ʒu
		@param	at	�J�����̒����_
		@param	up	�J�����̏����
		@return	���̃C���X�^���X�ւ̎Q��
		*/
		Matrix44& SetLookAtRH(const Vector3DF& eye, const Vector3DF& at, const Vector3DF& up);

		/**
		@brief	�J�����s��(����n)��ݒ肷��B
		@param	eye	�J�����̈ʒu
		@param	at	�J�����̒����_
		@param	up	�J�����̏����
		@return	���̃C���X�^���X�ւ̎Q��
		*/
		Matrix44& SetLookAtLH(const Vector3DF& eye, const Vector3DF& at, const Vector3DF& up);

		/**
		@brief	�ˉe�s��(�E��n)��ݒ肷��B
		@param	ovY	Y�����ւ̎���p(���W�A��)
		@param	aspect	��ʂ̃A�X�y�N�g��
		@param	zn	�ŋߋ���
		@param	zf	�ŉ�����
		@return	���̃C���X�^���X�ւ̎Q��
		*/
		Matrix44& SetPerspectiveFovRH(float ovY, float aspect, float zn, float zf);

		/**
		@brief	OpenGL�p�ˉe�s��(�E��n)��ݒ肷��B
		@param	ovY	Y�����ւ̎���p(���W�A��)
		@param	aspect	��ʂ̃A�X�y�N�g��
		@param	zn	�ŋߋ���
		@param	zf	�ŉ�����
		@return	���̃C���X�^���X�ւ̎Q��
		*/
		Matrix44& SetPerspectiveFovRH_OpenGL(float ovY, float aspect, float zn, float zf);

		/**
		@brief	�ˉe�s��(����n)��ݒ肷��B
		@param	ovY	Y�����ւ̎���p(���W�A��)
		@param	aspect	��ʂ̃A�X�y�N�g��
		@param	zn	�ŋߋ���
		@param	zf	�ŉ�����
		@return	���̃C���X�^���X�ւ̎Q��
		*/
		Matrix44& SetPerspectiveFovLH(float ovY, float aspect, float zn, float zf);

		/**
		@brief	���ˉe�s��(�E��n)��ݒ肷��B
		@param	width	����
		@param	height	�c��
		@param	zn	�ŋߋ���
		@param	zf	�ŉ�����
		@return	���̃C���X�^���X�ւ̎Q��
		*/
		Matrix44& SetOrthographicRH(float width, float height, float zn, float zf);

		/**
		@brief	���ˉe�s��(����n)��ݒ肷��B
		@param	width	����
		@param	height	�c��
		@param	zn	�ŋߋ���
		@param	zf	�ŉ�����
		@return	���̃C���X�^���X�ւ̎Q��
		*/
		Matrix44& SetOrthographicLH(float width, float height, float zn, float zf);

		/**
		@brief	���s�ړ��s���ݒ肷��B
		@param	x	X�����ړ���
		@param	y	Y�����ړ���
		@param	z	Z�����ړ���
		@return	���̃C���X�^���X�ւ̎Q��
		*/
		Matrix44& SetTranslation(float x, float y, float z);

		/**
		@brief	X����]�s��(�E��)��ݒ肷��B
		@param	angle	X����]��(���W�A��)
		@return	���̃C���X�^���X�ւ̎Q��
		*/
		Matrix44& SetRotationX(float angle);

		/**
		@brief	Y����]�s��(�E��)��ݒ肷��B
		@param	angle	Y����]��(���W�A��)
		@return	���̃C���X�^���X�ւ̎Q��
		*/
		Matrix44& SetRotationY(float angle);

		/**
		@brief	Z����]�s��(�E��)��ݒ肷��B
		@param	angle	Z����]��(���W�A��)
		@return	���̃C���X�^���X�ւ̎Q��
		*/
		Matrix44& SetRotationZ(float angle);

		/**
		@brief	�C�ӎ��̔����v��]�s��(�E��)��ݒ肷��B
		@param	axis	��
		@param	angle	��]��(���W�A��)
		@return	���̃C���X�^���X�ւ̎Q��
		*/
		Matrix44& SetRotationAxis(const Vector3DF& axis, float angle);

		/**
		@brief	�N�I�[�^�j�I�������ɉ�]�s��(�E��)��ݒ肷��B
		@param	x	�N�I�[�^�j�I��
		@param	y	�N�I�[�^�j�I��
		@param	z	�N�I�[�^�j�I��
		@param	w	�N�I�[�^�j�I��
		@return	���̃C���X�^���X�ւ̎Q��
		*/
		Matrix44& SetQuaternion(float x, float y, float z, float w);

		/**
		@brief	�g��s���ݒ肷��B
		@param	x	X�����g�嗦
		@param	y	Y�����g�嗦
		@param	z	Z�����g�嗦
		@return	���̃C���X�^���X�ւ̎Q��
		*/
		Matrix44& SetScale(float x, float y, float z);

		/**
		@brief	�s��Ńx�N�g����ό`������B
		@param	in	�ό`�O�x�N�g��
		@return	�ό`��x�N�g��
		*/
		Vector3DF Transform3D(const Vector3DF& in) const;

		/**
		@brief	�s��Ńx�N�g����ό`������B
		@param	in	�ό`�O�x�N�g��
		@return	�ό`��x�N�g��
		*/
		Vector4DF Transform4D(const Vector4DF& in) const;

		Matrix44 operator * (const Matrix44& right) const;

		Vector3DF operator*(const Vector3DF& right) const;

		Vector4DF operator*(const Vector4DF& right) const;

		/**
		@brief	��Z���s���B
		@param	o	�o�͐�
		@param	in1	�s��1
		@param	in2	�s��2
		@return	�o�͐�̎Q��
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
	@brief	�����`(���������_)�̍\����
	*/
	struct RectF
	{
	public:
		/**
		@brief	����X���W
		*/
		float X;

		/**
		@brief	����Y���W
		*/
		float Y;

		/**
		@brief	����
		*/
		float Width;

		/**
		@brief	�c��
		*/
		float Height;

		/**
		@brief	�R���X�g���N�^
		*/
		RectF();

		/**
		@brief	�R���X�g���N�^
		@param	x	����X���W
		@param	y	����Y���W
		@param	width	����
		@param	height	�c��
		*/
		RectF(float x, float y, float width, float height);

		/**
		@brief	������W���擾����B
		@return	������W
		*/
		Vector2DF GetPosition() const;

		/**
		@brief	�傫�����擾����B
		@return	�傫��
		*/
		Vector2DF GetSize() const;

		/**
		@brief	�l���̍��W��(X,Y)�A(X+Width,Y)�A(X+Width,Y+Height)�A(X,Y+Height)�̏��ɔz��Ƃ��Ď擾����B
		@return	���W
		*/
		std::array<Vector2DF, 4> GetVertexes() const;

		/**
		@brief	�~�ƏՓ˂��Ă��邩�ۂ��𒲂ׂ�B
		@param circle �~
		@return	�Փ˂��Ă��邩�ۂ�
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
	@brief	�����`(����)�̍\����
	*/
	struct RectI
	{
	public:
		/**
		@brief	����X���W
		*/
		int X;

		/**
		@brief	����Y���W
		*/
		int Y;

		/**
		@brief	����
		*/
		int Width;

		/**
		@brief	�c��
		*/
		int Height;

		/**
		@brief	�R���X�g���N�^
		*/
		RectI();

		/**
		@brief	�R���X�g���N�^
		@param	x	����X���W
		@param	y	����Y���W
		@param	width	����
		@param	height	�c��
		*/
		RectI(int x, int y, int width, int height);

		/**
		@brief	������W���擾����B
		@return	������W
		*/
		Vector2DI GetPosition() const;

		/**
		@brief	�傫�����擾����B
		@return	�傫��
		*/
		Vector2DI GetSize() const;

		/**
		@brief	�l���̍��W��(X,Y)�A(X+Width,Y)�A(X+Width,Y+Height)�A(X,Y+Height)�̏��ɔz��Ƃ��Ď擾����B
		@return	���W
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