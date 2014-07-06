﻿#pragma once

//----------------------------------------------------------------------------------
// Include
//----------------------------------------------------------------------------------
#include "../culling2d.common.Base.h"

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