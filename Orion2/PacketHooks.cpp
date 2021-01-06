#include "PacketHooks.h"

bool InitializePacketHooks()
{
	bool result = true;

	STATIC_SINGLETON(pInPacket, InPacket);
	result &= pInPacket->Decode1_Hook();
	result &= pInPacket->Decode2_Hook();
	result &= pInPacket->Decode4_Hook();

	STATIC_SINGLETON(pOutPacket, OutPacket);
	result &= pOutPacket->OutPacket__Hook();

	return result;
}

bool InPacket::Decode1_Hook()
{
	static auto _CInPacket__Decode1 = (pCInPacket__Decode1)(CInPacket__Decode1);
	pCInPacket__Decode1 CInPacket__Decode1_Hook = [](int pInPacket, char* pDest, char* pSrc, unsigned int nLength)
		-> signed int
	{
		int nResult = _CInPacket__Decode1(pInPacket, pDest, pSrc, nLength);
		if (nResult)
		{
			char nValue = (char)pSrc;
			auto pRet = (DWORD)_ReturnAddress();
			//Log("[CInPacket] [%#08x] Decode1: %#08x, %d", pRet, nValue, nValue);
		}
		return nResult; // 1
	};

	return SetHook(true, reinterpret_cast<void**>(&_CInPacket__Decode1), CInPacket__Decode1_Hook);
}

bool InPacket::Decode2_Hook()
{
	static auto _CInPacket__Decode2 = (pCInPacket__Decode2)(CInPacket__Decode2);
	pCInPacket__Decode2 CInPacket__Decode2_Hook = [](int pInPacket, short* pDest, short* pSrc, unsigned int nLength)
		-> signed int
	{
		int nResult = _CInPacket__Decode2(pInPacket, pDest, pSrc, nLength);
		if (nResult)
		{
			short nValue = (short)pSrc;
			auto pRet = (DWORD)_ReturnAddress();
			//Log("[CInPacket] [%#08x] Decode2: %#08x, %d", pRet, nValue, nValue);
		}
		return nResult; // 1
	};

	return SetHook(true, reinterpret_cast<void**>(&_CInPacket__Decode2), CInPacket__Decode2_Hook);
}

bool InPacket::Decode4_Hook()
{
	static auto _CInPacket__Decode4 = (pCInPacket__Decode4)(CInPacket__Decode4);
	pCInPacket__Decode4 CInPacket__Decode4_Hook = [](int pInPacket, int* pDest, int* pSrc, unsigned int nLength)
		-> signed int
	{
		int nResult = _CInPacket__Decode4(pInPacket, pDest, pSrc, nLength);
		if (nResult)
		{
			char nValue = (char)pSrc;
			auto pRet = (DWORD)_ReturnAddress();
			//Log("[CInPacket] [%#08x] Decode4: %#08x, %d", pRet, nValue, nValue);
		}
		return nResult; // 1
	};

	return SetHook(true, reinterpret_cast<void**>(&_CInPacket__Decode4), CInPacket__Decode4_Hook);
}

bool OutPacket::OutPacket__Hook()
{
	static auto _COutPacket__COutPacket = (pCOutPacket__COutPacket)(COutPacket__COutPacket);
	pCOutPacket__COutPacket COutPacket__COutPacket_Hook = [](void* pOutPacket, void* edx, int nPacketID, int a3)
		-> void*
	{
		auto pRet = (DWORD)_ReturnAddress();
		if (nPacketID != 18) // spam
			Log("[COutPacket] [%#08x] PacketID: %#08x (%d).", pRet, nPacketID, nPacketID);
		return _COutPacket__COutPacket(pOutPacket, edx, nPacketID, a3);
	};

	return SetHook(true, reinterpret_cast<void**>(&_COutPacket__COutPacket), COutPacket__COutPacket_Hook);
}
