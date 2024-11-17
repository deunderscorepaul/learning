#pragma once

// used: mem_pad
#include "../../utilities/memory.h"

// used: cusercmd
#include "../datatypes/usercmd.h"

#define MULTIPLAYER_BACKUP 150

class CTinyMoveStepData
{
public:
	float flWhen; //0x0000
	MEM_PAD(0x4); //0x0004
	std::uint64_t nButton; //0x0008
	bool bPressed; //0x0010
	MEM_PAD(0x7); //0x0011
}; //Size: 0x0018

class CMoveStepButtons
{
public:
	std::uint64_t nKeyboardPressed; //0x0000
	std::uint64_t nMouseWheelheelPressed; //0x0008
	std::uint64_t nUnPressed; //0x0010
	std::uint64_t nKeyboardCopy; //0x0018
}; //Size: 0x0020

// @credits: www.unknowncheats.me/forum/members/2943409.html
class CExtendedMoveData : public CMoveStepButtons
{
public:
	float flForwardMove; //0x0020
	float flSideMove; //0x0024
	float flUpMove; //0x0028
	std::int32_t nMouseDeltaX; //0x002C
	std::int32_t nMouseDeltaY; //0x0030
	std::int32_t nAdditionalStepMovesCount; //0x0034
	CTinyMoveStepData tinyMoveStepData[12]; //0x0038
	Vector_t vecViewAngle; //0x0158
	std::int32_t nTargetHandle; //0x0164
}; //Size:0x0168



class CCSGOInput
{
public:
	MEM_PAD(0x251); //0x0000
	bool m_bInThirdPerson; //0x0251
	MEM_PAD(0x6); //0x0252
	QAngle_t m_angThirdPersonAngles; //0x0258
	MEM_PAD(20); //0x0264
	MEM_PAD(0x20);
	CExtendedMoveData m_CurrentMoveData;
	MEM_PAD(0x230); //0x03DC
	std::int8_t m_nMouseisIntialized; //0x060C
	std::int8_t m_bInAttack; //0x060D
	std::int8_t m_bInAttack2; //0x060E
	std::int8_t N00000135; //0x060F
	int32_t m_nAttackStartHistoryIndex3; //0x5508
	int32_t m_nAttackStartHistoryIndex1; //0x550C
	int32_t m_nAttackStartHistoryIndex2; //0x5510


	void SetViewAngle(QAngle_t& angView)
	{
		// @ida: this got called before GetMatricesForView
		using fnSetViewAngle = std::int64_t(CS_FASTCALL*)(void*, std::int32_t, QAngle_t&);
		static auto oSetViewAngle = reinterpret_cast<fnSetViewAngle>(MEM::FindPattern(CLIENT_DLL, CS_XOR("85 D2 75 3F 48")));

		#ifdef CS_PARANOID
		CS_ASSERT(oSetViewAngle != nullptr);
		#endif

		oSetViewAngle(this, 0, std::ref(angView));
	}

	QAngle_t GetViewAngles()
	{
		using fnGetViewAngles = std::int64_t(CS_FASTCALL*)(CCSGOInput*, std::int32_t);
		static auto oGetViewAngles = reinterpret_cast<fnGetViewAngles>(MEM::FindPattern(CLIENT_DLL, CS_XOR("4C 8B C1 85 D2 74 08 48 8D 05 ? ? ? ? C3")));

		#ifdef CS_PARANOID
		CS_ASSERT(oGetViewAngles != nullptr);
		#endif

		return *reinterpret_cast<QAngle_t*>(oGetViewAngles(this, 0));
	}
};
