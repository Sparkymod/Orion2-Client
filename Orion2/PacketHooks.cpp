#include "PacketHooks.h"

bool InitializePacketHooks()
{
	bool result = true;

	STATIC_SINGLETON(pBuffer, Buffer);
	result &= pBuffer->DecodeHeader__Hook();
	result &= pBuffer->Decode1_Hook();
	result &= pBuffer->Decode2_Hook();
	result &= pBuffer->Decode4_Hook();
	result &= pBuffer->Decodef_Hook();
	result &= pBuffer->Decode8_Hook();
	result &= pBuffer->DecodeStr_Hook();
	result &= pBuffer->DecodeStrA_Hook();
	
	STATIC_SINGLETON(pInPacket, InPacket);
	result &= pInPacket->DecodeB_Hook();
	result &= pInPacket->Decode1_Hook();
	result &= pInPacket->Decode2_Hook();
	result &= pInPacket->Decode4_Hook();
	result &= pInPacket->Decode8_Hook();
	result &= pInPacket->Decodef_Hook();
	result &= pInPacket->DecodeWstrA_Hook();
	result &= pInPacket->DecodeStrA_Hook();
	result &= pInPacket->DecodeStrW_Hook();
	result &= pInPacket->DecodeBuffer_Hook();
	result &= pInPacket->DecodeCoordsf_Hook();
	result &= pInPacket->DecodeCoords2_Hook();
	result &= pInPacket->Decode2ft10_Hook();
	result &= pInPacket->Decode2ft100_Hook();
	result &= pInPacket->Decode2ftx_Hook();
	result &= pInPacket->Decode2ftp1_Hook();
	result &= pInPacket->Decode2fdx_Hook();

	STATIC_SINGLETON(pUnknown, UnknownPacket);
	result &= pUnknown->DecodeUnknown_Hook();
	result &= pUnknown->Decode1_Hook();
	result &= pUnknown->Decode2_Hook();
	result &= pUnknown->Decode4_Hook();
	result &= pUnknown->Decodef_Hook();
	result &= pUnknown->Decode8_Hook();
	result &= pUnknown->DecodeStr_Hook();
	result &= pUnknown->DecodeStrA_Hook();

	STATIC_SINGLETON(pOutPacket, OutPacket);
	result &= pOutPacket->OutPacket__Hook();

	return result;
}

#pragma region CBuffer

bool Buffer::DecodeHeader__Hook()
{
	static auto _CBuffer__DecodeHeader = (pCBuffer__DecodeHeader)(CBuffer__DecodeHeader);
	pCBuffer__DecodeHeader CBuffer__DecodeHeader_Hook = [](void* pInPacket, void* edx)
		-> int
	{
		auto pRet = (DWORD)_ReturnAddress();
		int nPacketID = _CBuffer__DecodeHeader(pInPacket, edx);
		if (LOG_BUFFER && !ReturnsToWrapper(pRet) && nPacketID != 89 && nPacketID != 128) // spam
			Log("[CInPacket] [%#08x] PacketID: %#08x (%d).", pRet, nPacketID, nPacketID);
		return nPacketID;
	};

	return SetHook(true, reinterpret_cast<void**>(&_CBuffer__DecodeHeader), CBuffer__DecodeHeader_Hook);
}


bool Buffer::Decode1_Hook()
{
	static auto _CBuffer__Decode1 = (pCBuffer__Decode1)(CBuffer__Decode1);
	pCBuffer__Decode1 CBuffer__Decode1_Hook = [](void* pInPacket, uint8_t* pDest, uint8_t* pSrc, int nLength)
		-> int
	{
		int nResult = _CBuffer__Decode1(pInPacket, pDest, pSrc, nLength);
		if (nResult)
		{
			uint8_t nValue = (uint8_t)pDest;
			auto pRet = (DWORD)_ReturnAddress();
			if (LOG_BUFFER && !ReturnsToWrapper(pRet))
				Log("[CBuffer] [%#08x] Decode1: %#02x, %d", pRet, nValue, nValue);
		}
		return nResult; // 1
	};
	return SetHook(true, reinterpret_cast<void**>(&_CBuffer__Decode1), CBuffer__Decode1_Hook);
}

bool Buffer::Decode2_Hook()
{
	static auto _CBuffer__Decode2 = (pCBuffer__Decode2)(CBuffer__Decode2);
	pCBuffer__Decode2 CBuffer__Decode2_Hook = [](void* pInPacket, uint16_t* pDest, uint16_t* pSrc, unsigned int nLength)
		-> int
	{
		int nResult = _CBuffer__Decode2(pInPacket, pDest, pSrc, nLength);
		if (nResult)
		{
			uint16_t nValue = (uint16_t)pDest;
			auto pRet = (DWORD)_ReturnAddress();
			if (LOG_BUFFER && !ReturnsToWrapper(pRet))
				Log("[CBuffer] [%#08x] Decode2: %#04x, %d", pRet, nValue, nValue);
		}
		return nResult; // 2
	};
	return SetHook(true, reinterpret_cast<void**>(&_CBuffer__Decode2), CBuffer__Decode2_Hook);
}

bool Buffer::Decode4_Hook()
{
	static auto _CBuffer__Decode4 = (pCBuffer__Decode4)(CBuffer__Decode4);
	pCBuffer__Decode4 CBuffer__Decode4_Hook = [](void* pInPacket, uint32_t* pDest, uint32_t* pSrc, unsigned int nLength)
		-> int
	{
		int nResult = _CBuffer__Decode4(pInPacket, pDest, pSrc, nLength);
		if (nResult)
		{
			int nValue = (int)pDest;
			auto pRet = (DWORD)_ReturnAddress();
			if (LOG_BUFFER && !ReturnsToWrapper(pRet))
				Log("[CBuffer] [%#08x] Decode4: %#08x, %d", pRet, nValue, nValue);
		}
		return nResult; // 2
	};
	return SetHook(true, reinterpret_cast<void**>(&_CBuffer__Decode4), CBuffer__Decode4_Hook);
}

bool Buffer::Decodef_Hook()
{
	static auto _CBuffer__Decodef = (pCBuffer__Decodef)(CBuffer__Decodef);
	pCBuffer__Decodef CBuffer__Decodef_Hook = [](void* pInPacket, uint32_t* pDest, uint32_t* pSrc, unsigned int nLength)
		-> int
	{
		int nResult = _CBuffer__Decodef(pInPacket, pDest, pSrc, nLength);
		if (nResult)
		{
			uint32_t nValue = (uint32_t) pDest;
			auto pRet = (DWORD)_ReturnAddress();
			if (LOG_BUFFER && !ReturnsToWrapper(pRet))
				Log("[CBuffer] [%#08x] Decodef: %#08x, %d", pRet, nValue, (float)nValue);
		}
		return nResult; // 2
	};
	return SetHook(true, reinterpret_cast<void**>(&_CBuffer__Decodef), CBuffer__Decodef_Hook);
}

bool Buffer::Decode8_Hook()
{
	static auto _CBuffer__Decode8 = (pCBuffer__Decode8)(CBuffer__Decode8);
	pCBuffer__Decode8 CBuffer__Decode8_Hook = [](void* pInPacket, uint64_t* pDest, uint64_t* pSrc, unsigned int nLength)
		-> int
	{
		int nResult = _CBuffer__Decode8(pInPacket, pDest, pSrc, nLength);
		if (nResult)
		{
			int64_t nValue = (int64_t) pDest;
			auto pRet = (DWORD)_ReturnAddress();
			if (LOG_BUFFER && !ReturnsToWrapper(pRet))
				Log("[CBuffer] [%#08x] Decode8: %#16x, %d", pRet, (uint64_t)pDest, nValue);
		}
		return nResult; // 2
	};
	return SetHook(true, reinterpret_cast<void**>(&_CBuffer__Decode8), CBuffer__Decode8_Hook);
}

bool Buffer::DecodeBuffer_Hook()
{
	static auto _CBuffer__DecodeBuffer = (pCBuffer__DecodeBuffer)(CBuffer__DecodeBuffer);
	pCBuffer__DecodeBuffer CBuffer__DecodeBuffer_Hook = [](void* pInPacket, int pDest, unsigned int nLength, int nDecodeLen, uint32_t* pSrc)
		-> unsigned int
	{
		int nResult = _CBuffer__DecodeBuffer(pInPacket, pDest, nLength, nDecodeLen, pSrc);
		if (nResult)
		{
			auto pRet = (DWORD)_ReturnAddress();
			if (LOG_BUFFER && !ReturnsToWrapper(pRet))
				Log("[CBuffer] [%#08x] DecodeBuffer: %#08x, pDest: %#08x", pRet, pDest);
		}
		return nResult; // nLength
	};
	return SetHook(true, reinterpret_cast<void**>(&_CBuffer__DecodeBuffer), CBuffer__DecodeBuffer_Hook);
}

bool Buffer::DecodeStr_Hook()
{
	static auto _CBuffer__DecodeStr = (pCBuffer__DecodeStr)(CBuffer__DecodeStr);
	pCBuffer__DecodeStr CBuffer__DecodeStr_Hook = [](void* pInPacket, int pDest, uint16_t* pSrc, unsigned int nLength)
		-> unsigned int
	{
		int nResult = _CBuffer__DecodeStr(pInPacket, pDest, pSrc, nLength);
		if (nResult)
		{
			auto pRet = (DWORD)_ReturnAddress();
			if (LOG_BUFFER && !ReturnsToWrapper(pRet))
				Log("[CBuffer] [%#08x] DecodeStr: %#08x, pDest: %#08x", pRet, pDest);
		}
		return nResult; // nLength
	};
	return SetHook(true, reinterpret_cast<void**>(&_CBuffer__DecodeStr), CBuffer__DecodeStr_Hook);
}

bool Buffer::DecodeStrA_Hook()
{
	static auto _CBuffer__DecodeStrA = (pCBuffer__DecodeStrA)(CBuffer__DecodeStrA);
	pCBuffer__DecodeStrA CBuffer__DecodeStrA_Hook = [](void* pInPacket, int pDest, uint16_t* pSrc, unsigned int nLength)
		-> unsigned int
	{
		int nResult = _CBuffer__DecodeStrA(pInPacket, pDest, pSrc, nLength);
		if (nResult)
		{
			auto pRet = (DWORD)_ReturnAddress();
			if (LOG_BUFFER && !ReturnsToWrapper(pRet))
				Log("[CBuffer] [%#08x] DecodeStrA: %#08x, pDest: %#08x", pRet, pDest);
		}
		return nResult; // nLength
	};
	return SetHook(true, reinterpret_cast<void**>(&_CBuffer__DecodeStrA), CBuffer__DecodeStrA_Hook);
}
#pragma endregion

#pragma region CInPacket

bool InPacket::DecodeB_Hook()
{
	static auto _CInPacket__DecodeB = (pCInPacket__DecodeB)(CInPacket__DecodeB);
	pCInPacket__DecodeB CInPacket__DecodeB_Hook = [](void* ecx, void* edx)
		-> bool
	{
		bool nResult = _CInPacket__DecodeB(ecx, edx);
		auto pRet = (DWORD)_ReturnAddress();
		if (LOG_PACKET)
			Log("[CInPacket] [%#08x] DecodeB: %#08x, %d", pRet, nResult, nResult);
		return nResult;
	};

	return SetHook(true, reinterpret_cast<void**>(&_CInPacket__DecodeB), CInPacket__DecodeB_Hook);
}

bool InPacket::Decode1_Hook()
{
	static auto _CInPacket__Decode1 = (pCInPacket__Decode1)(CInPacket__Decode1);
	pCInPacket__Decode1 CInPacket__Decode1_Hook = [](void* ecx, void* edx)
		-> char
	{
		char nResult = _CInPacket__Decode1(ecx, edx);
		auto pRet = (DWORD)_ReturnAddress();
		if (LOG_PACKET)
			Log("[CInPacket] [%#08x] Decode1: %#08x, %d", pRet, nResult, nResult);
		return nResult;
	};

	return SetHook(true, reinterpret_cast<void**>(&_CInPacket__Decode1), CInPacket__Decode1_Hook);
}

bool InPacket::Decode2_Hook()
{
	static auto _CInPacket__Decode2 = (pCInPacket__Decode2)(CInPacket__Decode2);
	pCInPacket__Decode2 CInPacket__Decode2_Hook = [](void* ecx, void* edx)
		-> short
	{
		short nResult = _CInPacket__Decode2(ecx, edx);
		auto pRet = (DWORD)_ReturnAddress();
		if (LOG_PACKET)
			Log("[CInPacket] [%#08x] Decode2: %#08x, %d", pRet, nResult, nResult);
		return nResult;
	};

	return SetHook(true, reinterpret_cast<void**>(&_CInPacket__Decode2), CInPacket__Decode2_Hook);
}

bool InPacket::Decode4_Hook()
{
	static auto _CInPacket__Decode4 = (pCInPacket__Decode4)(CInPacket__Decode4);
	pCInPacket__Decode4 CInPacket__Decode4_Hook = [](void* ecx, void* edx)
		-> int
	{
		int nResult = _CInPacket__Decode4(ecx, edx);
		auto pRet = (DWORD)_ReturnAddress();
		if (LOG_PACKET)
			Log("[CInPacket] [%#08x] Decode4: %#08x, %d", pRet, nResult, nResult);
		return nResult;
	};

	return SetHook(true, reinterpret_cast<void**>(&_CInPacket__Decode4), CInPacket__Decode4_Hook);
}

bool InPacket::Decodef_Hook()
{
	static auto _CInPacket__Decodef = (pCInPacket__Decodef)(CInPacket__Decodef);
	pCInPacket__Decodef CInPacket__Decodef_Hook = [](void* ecx, void* edx)
		-> float
	{
		float nResult = _CInPacket__Decodef(ecx, edx);
		auto pRet = (DWORD)_ReturnAddress();
		if (LOG_PACKET)
			Log("[CInPacket] [%#08x] Decodef: %#08x, %f", pRet, nResult, nResult);
		return nResult;
	};

	return SetHook(true, reinterpret_cast<void**>(&_CInPacket__Decodef), CInPacket__Decodef_Hook);
}

bool InPacket::Decode8_Hook()
{
	static auto _CInPacket__Decode8 = (pCInPacket__Decode8)(CInPacket__Decode8);
	pCInPacket__Decode8 CInPacket__Decode8_Hook = [](void* ecx, void* edx)
		-> int64_t
	{
		int64_t nResult = _CInPacket__Decode8(ecx, edx);
		auto pRet = (DWORD)_ReturnAddress();
		if (LOG_PACKET)
			Log("[CInPacket] [%#08x] Decode8: %llx, %ll", pRet, nResult, nResult);
		return nResult;
	};

	return SetHook(true, reinterpret_cast<void**>(&_CInPacket__Decode8), CInPacket__Decode8_Hook);
}

bool InPacket::DecodeWstrA_Hook()
{
	static auto _CInPacket__DecodeWStrA = (pCInPacket__DecodeWStrA)(CInPacket__DecodeWstrA);
	pCInPacket__DecodeWStrA CInPacket__DecodeWstrA_Hook = [](void* ecx, void* edx, int pDest)
		-> int
	{
		int nResult = _CInPacket__DecodeWStrA(ecx, edx, pDest);
		auto pRet = (DWORD)_ReturnAddress();
		if (LOG_PACKET)
			Log("[CInPacket] [%#08x] DecodeWStrA: nLen: %d, pDest: %#08x", pRet, nResult, pDest);
		return nResult;
	};

	return SetHook(true, reinterpret_cast<void**>(&_CInPacket__DecodeWStrA), CInPacket__DecodeWstrA_Hook);
}

bool InPacket::DecodeStrA_Hook()
{
	static auto _CInPacket__DecodeStrA = (pCInPacket__DecodeStrA)(CInPacket__DecodeStrA);
	pCInPacket__DecodeStrA CInPacket__DecodeStrA_Hook = [](void* ecx, void* edx, int pDest)
		-> int
	{
		int nResult = _CInPacket__DecodeStrA(ecx, edx, pDest);
		auto pRet = (DWORD)_ReturnAddress();
		if (LOG_PACKET)
			Log("[CInPacket] [%#08x] DecodeStrA: nLen: %d, pDest: %#08x", pRet, nResult, pDest);
		return nResult;
	};

	return SetHook(true, reinterpret_cast<void**>(&_CInPacket__DecodeStrA), CInPacket__DecodeStrA_Hook);
}

bool InPacket::DecodeStrW_Hook()
{
	static auto _CInPacket__DecodeStrW = (pCInPacket__DecodeStrW)(CInPacket__DecodeStrW);
	pCInPacket__DecodeStrW CInPacket__DecodeStrW_Hook = [](void* ecx, void* edx, int pDest)
		-> int
	{
		int nResult = _CInPacket__DecodeStrW(ecx, edx, pDest);
		auto pRet = (DWORD)_ReturnAddress();
		if (LOG_PACKET)
			Log("[CInPacket] [%#08x] DecodeStrW: nLen: %d, pDest: %#08x", pRet, nResult, pDest);
		return nResult;
	};

	return SetHook(true, reinterpret_cast<void**>(&_CInPacket__DecodeStrW), CInPacket__DecodeStrW_Hook);
}

bool InPacket::DecodeBuffer_Hook()
{
	static auto _CInPacket__DecodeBuffer = (pCInPacket__DecodeBuffer)(CInPacket__DecodeBuffer);
	pCInPacket__DecodeBuffer CInPacket__DecodeBuffer_Hook = [](void* ecx, void* edx, int pDest, unsigned int nLength)
		-> unsigned int
	{
		unsigned int nResult = _CInPacket__DecodeBuffer(ecx, edx, pDest, nLength);
		auto pRet = (DWORD)_ReturnAddress();
		if (LOG_PACKET)
			Log("[CInPacket] [%#08x] DecodeBuffer: nLen: %d, pDest: %#08x", pRet, nResult, pDest);
		return nResult;
	};

	return SetHook(true, reinterpret_cast<void**>(&_CInPacket__DecodeBuffer), CInPacket__DecodeBuffer_Hook);
}

bool InPacket::DecodeCoordsf_Hook()
{
	static auto _CInPacket__DecodeCoordsf = (pCInPacket__DecodeCoordsf)(CInPacket__DecodeCoordsf);
	pCInPacket__DecodeCoordsf CInPacket__DecodeCoordsf_Hook = [](void* ecx, void* edx, float* pDest)
		-> float*
	{
		float* nResult = _CInPacket__DecodeCoordsf(ecx, edx, pDest);
		auto pRet = (DWORD)_ReturnAddress();
		if (LOG_PACKET)
			Log("[CInPacket] [%#08x] DecodeCoordsf: nLen: %d, pDest: %#08x", pRet, nResult, pDest);
		return nResult;
	};

	return SetHook(true, reinterpret_cast<void**>(&_CInPacket__DecodeCoordsf), CInPacket__DecodeCoordsf_Hook);
}

bool InPacket::DecodeCoords2_Hook()
{
	static auto _CInPacket__DecodeCoords2 = (pCInPacket__DecodeCoords2)(CInPacket__DecodeCoords2);
	pCInPacket__DecodeCoords2 CInPacket__DecodeCoords2_Hook = [](void* ecx, void* edx, float* pDest)
		-> float*
	{
		float* nResult = _CInPacket__DecodeCoords2(ecx, edx, pDest);
		auto pRet = (DWORD)_ReturnAddress();
		if (LOG_PACKET)
			Log("[CInPacket] [%#08x] DecodeCoords2: nLen: %d, pDest: %#08x", pRet, nResult, pDest);
		return nResult;
	};

	return SetHook(true, reinterpret_cast<void**>(&_CInPacket__DecodeCoords2), CInPacket__DecodeCoords2_Hook);
}

bool InPacket::Decode2ft10_Hook()
{
	static auto _CInPacket__Decode2ft10 = (pCInPacket__Decode2ft10)(CInPacket__Decode2ft10);
	pCInPacket__Decode2ft10 CInPacket__Decode2ft10_Hook = [](void* ecx, void* edx)
		-> double
	{
		double nResult = _CInPacket__Decode2ft10(ecx, edx);
		auto pRet = (DWORD)_ReturnAddress();
		if (LOG_PACKET)
			Log("[CInPacket] [%#08x] Decode2ft10: nLen: %d", pRet, nResult);
		return nResult;
	};

	return SetHook(true, reinterpret_cast<void**>(&_CInPacket__Decode2ft10), CInPacket__Decode2ft10_Hook);
}

bool InPacket::Decode2ft100_Hook()
{
	static auto _CInPacket__Decode2ft100 = (pCInPacket__Decode2ft100)(CInPacket__Decode2ft100);
	pCInPacket__Decode2ft100 CInPacket__Decode2ft100_Hook = [](void* ecx, void* edx)
		-> double
	{
		double nResult = _CInPacket__Decode2ft100(ecx, edx);
		auto pRet = (DWORD)_ReturnAddress();
		if (LOG_PACKET)
			Log("[CInPacket] [%#08x] Decode2ft10: nLen: %d", pRet, nResult);
		return nResult;
	};

	return SetHook(true, reinterpret_cast<void**>(&_CInPacket__Decode2ft100), CInPacket__Decode2ft100_Hook);
}

bool InPacket::Decode2ftx_Hook()
{
	static auto _CInPacket__Decode2ftx = (pCInPacket__Decode2ftx)(CInPacket__Decode2ftx);
	pCInPacket__Decode2ftx CInPacket__Decode2ftx_Hook = [](void* ecx, void* edx, int pDest)
		-> double
	{
		double nResult = _CInPacket__Decode2ftx(ecx, edx, pDest);
		auto pRet = (DWORD)_ReturnAddress();
		if (LOG_PACKET)
			Log("[CInPacket] [%#08x] Decode2ftx: nLen: %d", pRet, nResult);
		return nResult;
	};

	return SetHook(true, reinterpret_cast<void**>(&_CInPacket__Decode2ftx), CInPacket__Decode2ftx_Hook);
}

bool InPacket::Decode2ftp1_Hook()
{
	static auto _CInPacket__Decode2ftp1 = (pCInPacket__Decode2ftp1)(CInPacket__Decode2ftp1);
	pCInPacket__Decode2ftp1 CInPacket__Decode2ftp1_Hook = [](void* ecx, void* edx)
		-> double
	{
		double nResult = _CInPacket__Decode2ftp1(ecx, edx);
		auto pRet = (DWORD)_ReturnAddress();
		if (LOG_PACKET)
			Log("[CInPacket] [%#08x] Decode2ftp1: nLen: %d", pRet, nResult);
		return nResult;
	};

	return SetHook(true, reinterpret_cast<void**>(&_CInPacket__Decode2ftp1), CInPacket__Decode2ftp1_Hook);
}

bool InPacket::Decode2fdx_Hook()
{
	static auto _CInPacket__Decode2fdx = (pCInPacket__Decode2fdx)(CInPacket__Decode2fdx);
	pCInPacket__Decode2fdx CInPacket__Decode2fdx_Hook = [](void* ecx, void* edx, int pDest)
		-> double
	{
		double nResult = _CInPacket__Decode2fdx(ecx, edx, pDest);
		auto pRet = (DWORD)_ReturnAddress();
		if (LOG_PACKET)
			Log("[CInPacket] [%#08x] Decode2fdx: nLen: %d", pRet, nResult);
		return nResult;
	};

	return SetHook(true, reinterpret_cast<void**>(&_CInPacket__Decode2fdx), CInPacket__Decode2fdx_Hook);
}

#pragma endregion

#pragma region CUnknown

bool UnknownPacket::DecodeUnknown_Hook()
{
	static auto _CUnknown__DecodeUnknown = (pCUnknown__DecodeUnknown)(CUnknown__DecodeUnknown);
	pCUnknown__DecodeUnknown CUnknown__DecodeUnknown_Hook = [](void* ecx, void* edx, int nValue, void* pInPacket)
		-> int
	{
		int nResult = _CUnknown__DecodeUnknown(ecx, edx, nValue, pInPacket);
		auto pRet = (DWORD)_ReturnAddress();
		if (LOG_PACKET)
			Log("[CUnknown] [%#08x] DecodeUnknown: %#08x, %d", pRet, nResult, nResult);
		return nResult;
	};

	return SetHook(true, reinterpret_cast<void**>(&_CUnknown__DecodeUnknown), CUnknown__DecodeUnknown_Hook);
}

bool UnknownPacket::Decode1_Hook()
{
	static auto _CUnknown__Decode1 = (pCUnknown__Decode1)(CUnknown__Decode1);
	pCUnknown__Decode1 CUnknown__Decode1_Hook = [](void* ecx, void* edx)
		-> char
	{
		char nResult = _CUnknown__Decode1(ecx, edx);
		auto pRet = (DWORD)_ReturnAddress();
		if (LOG_PACKET)
			Log("[CUnknown] [%#08x] Decode1: %#08x, %d", pRet, nResult, nResult);
		return nResult;
	};

	return SetHook(true, reinterpret_cast<void**>(&_CUnknown__Decode1), CUnknown__Decode1_Hook);
}

bool UnknownPacket::Decode2_Hook()
{
	static auto _CUnknown__Decode2 = (pCUnknown__Decode2)(CUnknown__Decode2);
	pCUnknown__Decode2 CUnknown__Decode2_Hook = [](void* ecx, void* edx)
		-> short
	{
		short nResult = _CUnknown__Decode2(ecx, edx);
		auto pRet = (DWORD)_ReturnAddress();
		if (LOG_PACKET)
			Log("[CUnknown] [%#08x] Decode2: %#08x, %d", pRet, nResult, nResult);
		return nResult;
	};

	return SetHook(true, reinterpret_cast<void**>(&_CUnknown__Decode2), CUnknown__Decode2_Hook);
}

bool UnknownPacket::Decode4_Hook()
{
	static auto _CUnknown__Decode4 = (pCUnknown__Decode4)(CUnknown__Decode4);
	pCUnknown__Decode4 CUnknown__Decode4_Hook = [](void* ecx, void* edx)
		-> int
	{
		int nResult = _CUnknown__Decode4(ecx, edx);
		auto pRet = (DWORD)_ReturnAddress();
		if (LOG_PACKET)
			Log("[CUnknown] [%#08x] Decode4: %#08x, %d", pRet, nResult, nResult);
		return nResult;
	};

	return SetHook(true, reinterpret_cast<void**>(&_CUnknown__Decode4), CUnknown__Decode4_Hook);
}

bool UnknownPacket::Decodef_Hook()
{
	static auto _CUnknown__Decodef = (pCUnknown__Decodef)(CUnknown__Decodef);
	pCUnknown__Decodef CUnknown__Decodef_Hook = [](void* ecx, void* edx)
		-> float
	{
		float nResult = _CUnknown__Decodef(ecx, edx);
		auto pRet = (DWORD)_ReturnAddress();
		if (LOG_PACKET)
			Log("[CUnknown] [%#08x] Decodef: %#08x, %f", pRet, nResult, nResult);
		return nResult;
	};

	return SetHook(true, reinterpret_cast<void**>(&_CUnknown__Decodef), CUnknown__Decodef_Hook);
}

bool UnknownPacket::Decode8_Hook()
{
	static auto _CUnknown__Decode8 = (pCUnknown__Decode8)(CUnknown__Decode8);
	pCUnknown__Decode8 CUnknown__Decode8_Hook = [](void* ecx, void* edx)
		-> int64_t
	{
		int64_t nResult = _CUnknown__Decode8(ecx, edx);
		auto pRet = (DWORD)_ReturnAddress();
		if (LOG_PACKET)
			Log("[CUnknown] [%#08x] Decode8: %llx, %ll", pRet, nResult, nResult);
		return nResult;
	};

	return SetHook(true, reinterpret_cast<void**>(&_CUnknown__Decode8), CUnknown__Decode8_Hook);
}

bool UnknownPacket::DecodeStr_Hook()
{
	static auto _CUnknown__DecodeStr = (pCUnknown__DecodeStr)(CUnknown__DecodeStr);
	pCUnknown__DecodeStr CUnknown__DecodeStr_Hook = [](void* ecx, void* edx, int pDest)
		-> int
	{
		int nResult = _CUnknown__DecodeStr(ecx, edx, pDest);
		auto pRet = (DWORD)_ReturnAddress();
		if (LOG_PACKET)
			Log("[CUnknown] [%#08x] DecodeStr: nLen: %d, pDest: %#08x", pRet, nResult, pDest);
		return nResult;
	};

	return SetHook(true, reinterpret_cast<void**>(&_CUnknown__DecodeStr), CUnknown__DecodeStr_Hook);
}

bool UnknownPacket::DecodeStrA_Hook()
{
	static auto _CUnknown__DecodeStrA = (pCUnknown__DecodeStrA)(CUnknown__DecodeStrA);
	pCUnknown__DecodeStrA CUnknown__DecodeStrA_Hook = [](void* ecx, void* edx, int pDest)
		-> int
	{
		int nResult = _CUnknown__DecodeStrA(ecx, edx, pDest);
		auto pRet = (DWORD)_ReturnAddress();
		if (LOG_PACKET)
			Log("[CUnknown] [%#08x] DecodeStrA: nLen: %d, pDest: %#08x", pRet, nResult, pDest);
		return nResult;
	};

	return SetHook(true, reinterpret_cast<void**>(&_CUnknown__DecodeStrA), CUnknown__DecodeStrA_Hook);
}

bool UnknownPacket::DecodeBuffer_Hook()
{
	static auto _CUnknown__DecodeBuffer = (pCUnknown__DecodeBuffer)(CUnknown__DecodeBuffer);
	pCUnknown__DecodeBuffer CUnknown__DecodeBuffer_Hook = [](void* ecx, void* edx, int pDest, unsigned int nLength)
		-> unsigned int
	{
		unsigned int nResult = _CUnknown__DecodeBuffer(ecx, edx, pDest, nLength);
		auto pRet = (DWORD)_ReturnAddress();
		if (LOG_PACKET)
			Log("[CUnknown] [%#08x] DecodeBuffer: nLen: %d, pDest: %#08x", pRet, nResult, pDest);
		return nResult;
	};

	return SetHook(true, reinterpret_cast<void**>(&_CUnknown__DecodeBuffer), CUnknown__DecodeBuffer_Hook);
}

#pragma endregion


bool OutPacket::OutPacket__Hook()
{
	static auto _COutPacket__COutPacket = (pCOutPacket__COutPacket)(COutPacket__COutPacket);
	pCOutPacket__COutPacket COutPacket__COutPacket_Hook = [](void* pOutPacket, void* edx, int nPacketID, int a3)
		-> void*
	{
		auto pRet = (DWORD)_ReturnAddress();
		if (LOG_PACKET && nPacketID != 18) // spam
			Log("[COutPacket] [%#08x] PacketID: %#08x (%d).", pRet, nPacketID, nPacketID);
		return _COutPacket__COutPacket(pOutPacket, edx, nPacketID, a3);
	};

	return SetHook(true, reinterpret_cast<void**>(&_COutPacket__COutPacket), COutPacket__COutPacket_Hook);
}
