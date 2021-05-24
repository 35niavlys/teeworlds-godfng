/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#ifndef GAME_SERVER_ENTITIES_SHIELD_H
#define GAME_SERVER_ENTITIES_SHIELD_H

#include <game/server/entity.h>

class CShield : public CEntity
{
public:
	CShield(CGameWorld *pGameWorld, vec2 Pos, int Owner, int Type);

	virtual void Tick();
	virtual void Snap(int SnappingClient);

private:
	int m_Owner;
	vec2 m_Pos;
	vec2 m_Vel;
};

#endif
