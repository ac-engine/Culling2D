#pragma once

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