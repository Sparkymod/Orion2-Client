/**
* 
* @author Kaz
*
*/
#ifndef PACKETHOOKS_H
#define PACKETHOOKS_H

#include "Orion.h"

//Config
#define LOG_BUFFER FALSE
#define LOG_PACKET TRUE

//COutPacket
#define COutPacket__COutPacket		0x05E2960
#define COutPacket__AppendBuffer	0x04186A0
#define COutPacket__Encode1			0x0418700
#define COutPacket__Encode2			0x0418740
#define COutPacket__Encode4			0x0418780
#define COutPacket__Encodef			0x0418780
#define COutPacket__Encode8			0x0418800
#define COutPacket__EncodeStr		0x04189B0 // Unsure
#define COutPacket__EncodeStrA		0x04188B0 // Unsure

//CBuffer
#define CBuffer__DecodeHeader		0x05E2730
#define CBuffer__Decode1			0x05E32C0
#define CBuffer__Decode2			0x05E3380
#define CBuffer__Decode4			0x05E3440
#define CBuffer__Decodef			0x05E3500
#define CBuffer__Decode8			0x05E35C0
#define CBuffer__DecodeBuffer		0x05E3680
#define CBuffer__DecodeStr			0x05E3740
#define CBuffer__DecodeStrA			0x05E3910

//CInPacket
#define CInPacket__DecodeB			0x05E2460
#define CInPacket__Decode1			0x05E3C20
#define CInPacket__Decode2			0x05E3C70
#define CInPacket__Decode4			0x05E3CC0
#define CInPacket__Decode8			0x05E3D10
#define CInPacket__Decodef			0x05E3D60
#define CInPacket__DecodeWstrA		0x05E3FE0
#define CInPacket__DecodeStrA		0x05E3DB0
#define CInPacket__DecodeStrW		0x05E3E40
#define CInPacket__DecodeBuffer		0x05E3ED0
#define CInPacket__DecodeCoordsf	0x05E3B70
#define CInPacket__DecodeCoords2	0x05E3BB0
#define CInPacket__Decode2ft10		0x05E3B10
#define CInPacket__Decode2ft100		0x05E3B30
#define CInPacket__Decode2ftx		0x05E3B50
#define CInPacket__Decode2ftp1		0x05E3AD0
#define CInPacket__Decode2fdx		0x05E3AF0
#define CInPacket__End				0x05E3BF9

//Unk Decoders (Another buffer instance? Maybe an extended class?)
#define CUnknown__DecodeUnknown		0x0639310
#define CUnknown__Decode1			0x0639340
#define CUnknown__Decode2			0x0639390
#define CUnknown__Decode4			0x06393E0
#define CUnknown__Decode8			0x0639430
#define CUnknown__Decodef			0x0639480
#define CUnknown__DecodeBuffer		0x06394D0
#define CUnknown__DecodeStrA		0x0639520
#define CUnknown__DecodeStr			0x06395B0
#define CUnknown__End				0x0639620

static bool ReturnsToWrapper(int dwReturnAddress)
{
	bool bInPacketRet = dwReturnAddress > CInPacket__Decode1 && dwReturnAddress < CInPacket__End;
	bool bUnknownRet = dwReturnAddress > CUnknown__DecodeUnknown && dwReturnAddress < CUnknown__End;
	return bInPacketRet || bUnknownRet;
}

class Buffer {
public:
	bool DecodeHeader__Hook();
	bool Decode1_Hook();
	bool Decode2_Hook();
	bool Decode4_Hook();
	bool Decodef_Hook();
	bool Decode8_Hook();
	bool DecodeBuffer_Hook();
	bool DecodeStr_Hook();
	bool DecodeStrA_Hook();
private:
	typedef int(__fastcall* pCBuffer__DecodeHeader)(void* pInPacket, void* edx);
	typedef int(__cdecl* pCBuffer__Decode1)(void* pInPacket, uint8_t* pDest, uint8_t* pSrc, int nLength);
	typedef int(__cdecl* pCBuffer__Decode2)(void* pInPacket, uint16_t* pDest, uint16_t* pSrc, unsigned int nLength);
	typedef int(__cdecl* pCBuffer__Decode4)(void* pInPacket, uint32_t* pDest, uint32_t* pSrc, unsigned int nLength);
	typedef int(__cdecl* pCBuffer__Decodef)(void* pInPacket, uint32_t* pDest, uint32_t* pSrc, unsigned int nLength);
	typedef int(__cdecl* pCBuffer__Decode8)(void* pInPacket, uint64_t* pDest, uint64_t* pSrc, unsigned int nLength);
	typedef unsigned int(__cdecl* pCBuffer__DecodeBuffer)(void* pInPacket, int pDest, unsigned int nLength, int nDecodeLen, uint32_t* pSrc);
	typedef unsigned int(__cdecl* pCBuffer__DecodeStr)(void* pInPacket, int pDest, uint16_t* pSrc, unsigned int nLength);
	typedef unsigned int(__cdecl* pCBuffer__DecodeStrA)(void* pInPacket, int pDest, uint16_t* pSrc, unsigned int nLength);
};

class InPacket {
public:
	bool DecodeB_Hook();
	bool Decode1_Hook();
	bool Decode2_Hook();
	bool Decode4_Hook();
	bool Decode8_Hook();
	bool Decodef_Hook();
	bool DecodeWstrA_Hook();
	bool DecodeStrA_Hook();
	bool DecodeStrW_Hook();
	bool DecodeBuffer_Hook();
	bool DecodeCoordsf_Hook();
	bool DecodeCoords2_Hook();
	bool Decode2ft10_Hook();
	bool Decode2ft100_Hook();
	bool Decode2ftx_Hook();
	bool Decode2ftp1_Hook();
	bool Decode2fdx_Hook();
private:
	typedef bool(__fastcall* pCInPacket__DecodeB)(void* ecx, void* edx);
	typedef char(__fastcall* pCInPacket__Decode1)(void* ecx, void* edx);
	typedef short(__fastcall* pCInPacket__Decode2)(void* ecx, void* edx);
	typedef int(__fastcall* pCInPacket__Decode4)(void* ecx, void* edx);
	typedef float(__fastcall* pCInPacket__Decodef)(void* ecx, void* edx);
	typedef int64_t(__fastcall* pCInPacket__Decode8)(void* ecx, void* edx);
	typedef int(__fastcall* pCInPacket__DecodeWStrA)(void* ecx, void* edx, int pDest);
	typedef int(__fastcall* pCInPacket__DecodeStrA)(void* ecx, void* edx, int pDest);
	typedef int(__fastcall* pCInPacket__DecodeStrW)(void* ecx, void* edx, int pDest);
	typedef unsigned int(__fastcall* pCInPacket__DecodeBuffer)(void* ecx, void* edx, int pDest, unsigned int nLength);
	typedef float*(__fastcall* pCInPacket__DecodeCoordsf)(void* ecx, void* edx, float* pDest);
	typedef float*(__fastcall* pCInPacket__DecodeCoords2)(void* ecx, void* edx, float* pDest);
	typedef double(__fastcall* pCInPacket__Decode2ft10)(void* ecx, void* edx);
	typedef double(__fastcall* pCInPacket__Decode2ft100)(void* ecx, void* edx);
	typedef double(__fastcall* pCInPacket__Decode2ftx)(void* ecx, void* edx, int pDest); // pDest?
	typedef double(__fastcall* pCInPacket__Decode2ftp1)(void* ecx, void* edx);
	typedef double(__fastcall* pCInPacket__Decode2fdx)(void* ecx, void* edx, int pDest); // pDest?
};

class UnknownPacket {
public:
	bool DecodeUnknown_Hook();
	bool Decode1_Hook();
	bool Decode2_Hook();
	bool Decode4_Hook();
	bool Decode8_Hook();
	bool Decodef_Hook();
	bool DecodeStr_Hook();
	bool DecodeStrA_Hook();
	bool DecodeBuffer_Hook();
private:
	typedef int(__fastcall* pCUnknown__DecodeUnknown)(void* ecx, void* edx, int nValue, void* pInPacket); // What is this?
	typedef char(__fastcall* pCUnknown__Decode1)(void* ecx, void* edx);
	typedef short(__fastcall* pCUnknown__Decode2)(void* ecx, void* edx);
	typedef int(__fastcall* pCUnknown__Decode4)(void* ecx, void* edx);
	typedef float(__fastcall* pCUnknown__Decodef)(void* ecx, void* edx);
	typedef int64_t(__fastcall* pCUnknown__Decode8)(void* ecx, void* edx);
	typedef int(__fastcall* pCUnknown__DecodeStr)(void* ecx, void* edx, int pDest);
	typedef int(__fastcall* pCUnknown__DecodeStrA)(void* ecx, void* edx, int pDest);
	typedef unsigned int(__fastcall* pCUnknown__DecodeBuffer)(void* ecx, void* edx, int pDest, unsigned int nLength);
};

class OutPacket {
public:
	bool OutPacket__Hook();
private:
	typedef void*(__fastcall* pCOutPacket__COutPacket)(void* pOutPacket, void* edx, int nPacketID, int a3);
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