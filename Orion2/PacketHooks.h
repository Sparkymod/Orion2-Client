/**
* 
* @author Kaz
*
*/
#ifndef PACKETHOOKS_H
#define PACKETHOOKS_H

#include "Orion.h"

//COutPacket
#define COutPacket__AppendBuffer	0x04186A0
#define COutPacket__Encode1			0x0418700
#define COutPacket__Encode2			0x0418740
#define COutPacket__Encode4			0x0418780
#define COutPacket__Encodef			0x0418780
#define COutPacket__Encode8			0x0418800
#define COutPacket__EncodeStr		0x04189B0 // Unsure
#define COutPacket__EncodeStrA		0x04188B0 // Unsure

//CInPacket
#define CInPacket__DecodeHeader		0x0418BB0
#define CInPacket__Decode1			0x05E32C0
#define CInPacket__Decode2			0x05E3380
#define CInPacket__Decode4			0x05E3440
#define CInPacket__Decodef			0x05E3500
#define CInPacket__Decode8			0x05E35C0
#define CInPacket__DecodeBuffer		0x05E3680
#define CInPacket__DecodeStr		0x05E3740
#define CInPacket__DecodeStrA		0x05E3910

class InPacket {
public:
	bool Decode1_Hook();
	bool Decode2_Hook();
	bool Decode4_Hook();
private:
	typedef int(__thiscall* pCInPacket__DecodeHeader)(void* pInPacket);
	typedef signed int(__cdecl* pCInPacket__Decode1)(int pInPacket, char* pDest, char* pSrc, unsigned int nLength);
	typedef signed int(__cdecl* pCInPacket__Decode2)(int pInPacket, short* pDest, short* pSrc, unsigned int nLength);
	typedef signed int(__cdecl* pCInPacket__Decode4)(int pInPacket, int* pDest, int* pSrc, unsigned int nLength);
	typedef signed int(__cdecl* pCInPacket__Decodef)(int pInPacket, float* pDest, float* pSrc, unsigned int nLength);
	typedef signed int(__cdecl* pCInPacket__Decode8)(int pInPacket, long* pDest, long* pSrc, unsigned int nLength);
	typedef signed int(__cdecl* pCInPacket__DecodeBuffer)(int pInPacket, int pDest, unsigned int nSize, int pSrc, int* nLength);
	typedef signed int(__cdecl* pCInPacket__DecodeStr)(int pInPacket, int pDest, unsigned short* pSrc, unsigned int nLength);
	typedef signed int(__cdecl* pCInPacket__DecodeStrA)(int pInPacket, int pDest, unsigned short* pSrc, unsigned int nLength);
};

class OutPacket {
public:
	typedef char(__thiscall* pCOutPacket__AppendBuffer)(unsigned int* pOutPacket, int nSize);
	typedef unsigned int(__thiscall* pCOutPacket__Encode1)(unsigned int* pOutPacket, char nValue);
	typedef unsigned int(__thiscall* pCOutPacket__Encode2)(unsigned int* pOutPacket, __int16 nValue);
	typedef unsigned int(__thiscall* pCOutPacket__Encode4)(unsigned int* pOutPacket, int nValue);
	typedef unsigned int(__thiscall* pCOutPacket__Encodef)(unsigned int* pOutPacket, int nValue);
	typedef unsigned int(__thiscall* pCOutPacket__Encode8)(unsigned int* pOutPacket, int nLow, int nHigh);
	typedef unsigned int(__thiscall* pCOutPacket__EncodeStr)(unsigned int* pOutPacket, int a2);
	typedef unsigned int(__thiscall* pCOutPacket__EncodeStrA)(unsigned int* pOutPacket, int a2);
};

//Hook Functions
bool InitializePacketHooks();

#endif