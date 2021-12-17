#include "EventItemAction.h"

#include <Exd/ExdData.h>
#include <Exd/Structs.h>

#include <Actor/Player.h>
#include <Network/PacketWrappers/EffectPacket.h>

#include "Manager/PlayerMgr.h"
#include <Service.h>
#include <Network/CommonActorControl.h>
#include <WorldServer.h>
#include "Network/PacketWrappers/ActorControlPacket.h"
#include "Network/PacketWrappers/ActorControlSelfPacket.h"
#include "Network/PacketWrappers/ActorControlTargetPacket.h"
#include <Util/UtilMath.h>
#include <Common.h>


using namespace Sapphire;
using namespace Sapphire::Common;
using namespace Sapphire::World::Action;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;
using namespace Sapphire::Network::ActorControl;

EventItemAction::EventItemAction( Sapphire::Entity::CharaPtr source, uint32_t eventItemId,
                                  std::shared_ptr< Component::Excel::ExcelStruct< Component::Excel::EventItem > > eventItemActionData,
                                  uint32_t sequence, uint64_t targetId  ) :
  m_eventItemAction( std::move( eventItemActionData ) )
{
  m_id = eventItemId;
  m_eventItem = eventItemId;
  m_pSource = std::move( source );
  m_sequence = sequence;
  m_targetId = targetId;
  m_interruptType = Common::ActionInterruptType::None;
  m_actionKind = Common::SkillType::EventItem;
}

bool EventItemAction::init()
{
  auto& exdData = Common::Service< Data::ExdData >::ref();
  auto actionInfoPtr = exdData.getRow< Component::Excel::Action >( m_eventItemAction->data().Action );

  m_castTimeMs = static_cast< uint32_t >( m_eventItemAction->data().CastTime * 1000 );
  m_recastTimeMs = static_cast< uint32_t >( actionInfoPtr->data().RecastTime * 100 );
  m_cooldownGroup = actionInfoPtr->data().RecastGroup;
  m_id = m_eventItemAction->data().Action;
  return true;
}

void EventItemAction::execute()
{
  Manager::PlayerMgr::sendDebug( *getSourceChara()->getAsPlayer(), "EventItemAction type {0} execute called.", m_eventItemAction->data().Action );
}

void EventItemAction::onStart()
{
}

void EventItemAction::onInterrupt()
{
}