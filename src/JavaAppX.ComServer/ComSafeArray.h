#pragma once

#include <stdint.h>
#include <OAIdl.h>
#include <intrin.h>

namespace JdkComServer {
	class ComSafeArray final
	{
	private:
		SAFEARRAY* psa;

	public:
		ComSafeArray() : psa(nullptr) {}
		ComSafeArray(SAFEARRAY* psa) : psa(psa) {}
		~ComSafeArray() {
			Destroy();
		}

		SAFEARRAY** operator &(void) {
			assert(psa == nullptr);
			return &psa;
		}

		operator SAFEARRAY* (void) {
			assert(psa != nullptr);
			return psa;
		}

		HRESULT Create(VARTYPE vt, ULONG length) {
			SAFEARRAYBOUND dimensions[1];
			dimensions[0].lLbound = 0;
			dimensions[0].cElements = length;
			return Create(vt, dimensions);
		}

		template<UINT count>
		HRESULT Create(VARTYPE vt, const SAFEARRAYBOUND (&dimensions)[count]) {
			assert(psa == nullptr);
			psa = ::SafeArrayCreate(vt, count, (SAFEARRAYBOUND*)dimensions);
			return (psa != nullptr) ? S_OK : E_FAIL;
		}

		void Destroy() {
			if (psa != nullptr) ::SafeArrayDestroy(psa);
			psa = nullptr;
		}

		SAFEARRAY* Detach() {
			assert(psa != nullptr);
			SAFEARRAY * retval = psa;
			psa = nullptr;
			return retval;
		}

		UINT GetDimensionCount() {
			assert(psa != nullptr);
			return ::SafeArrayGetDim(psa);
		}

		LONG GetDimensionLowerBound(UINT dimension) {
			assert(psa != nullptr);

			LONG retval;
			::SafeArrayGetLBound(psa, dimension, &retval);
			return retval;
		}

		LONG GetDimensionUpperBound(UINT dimension) {
			assert(psa != nullptr);

			LONG retval;
			::SafeArrayGetUBound(psa, dimension, &retval);
			return retval;
		}

		HRESULT GetElement(LONG index, void* pv) {
			assert(psa != nullptr);
			assert(GetDimensionCount() == 1);
			return ::SafeArrayGetElement(psa, &index, pv);
		}

		template<UINT count>
		HRESULT GetElement(LONG indices[count], void* pv) {
			assert(psa != nullptr);
			assert(count == GetDimensionCount());
			return ::SafeArrayGetElement(psa, indices, pv);
		}

		HRESULT SetElement(LONG index, void* pv) {
			assert(psa != nullptr);
			assert(GetDimensionCount() == 1);
			return ::SafeArrayPutElement(psa, &index, pv);
		}

		template<LONG count>
		HRESULT SetElement(const LONG (&indices)[count], void* pv) {
			assert(psa != nullptr);
			assert(count == GetDimensionCount());
			return ::SafeArrayPutElement(psa, indices, pv);
		}

		UINT GetElementSize() {
			assert(psa != nullptr);
			return ::SafeArrayGetElemsize(psa);
		}

		template<typename TData, size_t bufferLength>
		HRESULT AccessData(TData buffer[bufferLength], size_t & elementCount)
		{
			assert(psa != nullptr);
			if (GetDimensionCount() != 1) return E_NOTIMPL;

			elementCount = GetElementSize() * (GetDimensionUpperBound(0) - GetDimensionLowerBound(0));
			return SafeArrayAccessData(psa, (void**)& buffer);
		}

		HRESULT UnaccessData()
		{
			assert(psa != nullptr);
			return SafeArrayUnaccessData(psa);
		}
	};
}
