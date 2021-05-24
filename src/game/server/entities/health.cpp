/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#include "health.h"
#include <game/generated/protocol.h>
#include <game/server/gamecontext.h>

CHealth::CHealth(CGameWorld *pGameWorld, vec2 Pos, int Owner, int Type) : CEntity(pGameWorld, CGameWorld::ENTTYPE_PICKUP)
{
	m_Owner = Owner;
	m_Pos = Pos;

	GameWorld()->InsertEntity(this);
}

void CHealth::Tick()
{
	CCharacter *m_Chr = GameServer()->m_World.ClosestCharacter(m_Pos, 20.0f, 0);
	CCharacter *m_Ownerchar = GameServer()->GetPlayerChar(m_Owner);

	if(!m_Ownerchar)
	{
		GameWorld()->DestroyEntity(this);
		return;
	}

	m_Pos = m_Ownerchar->m_Pos - vec2(0, 45);
	if(GameServer()->m_World.m_Paused == true || !m_Ownerchar->Core()->m_ProtectedBy)
		GameWorld()->DestroyEntity(this);
}

void CHealth::Snap(int SnappingClient)
{
	if(NetworkClipped(SnappingClient, m_Pos)) // fix display m_Pos
		return;

	CNetObj_Pickup *pP = static_cast<CNetObj_Pickup *>(Server()->SnapNewItem(NETOBJTYPE_PICKUP, m_ID, sizeof(CNetObj_Pickup)));
	if(!pP)
		return;

	// if(SnappingClient != m_Owner) // fix display for others
	// return;

	pP->m_X = (int)m_Pos.x;
	pP->m_Y = (int)m_Pos.y;
	pP->m_Type = POWERUP_HEALTH;
	pP->m_Subtype = 0;
}
