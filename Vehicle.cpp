#include "Vehicle.h"

Vehicle::Vehicle(Player* player)
    : m_Owner(player)
{
    m_state = VEHICLE_STATE_ALIVE;
    m_type = VEHICLE_TYPE_NONE;
    m_health = DEFAULT_PLANE_HEALTH;
    m_maxHealth = DEFAULT_PLANE_HEALTH;
}

Vehicle::~Vehicle()
{

}

void Vehicle::Reset()
{
    m_health = DEFAULT_PLANE_HEALTH;
    m_maxHealth = DEFAULT_PLANE_HEALTH;
}

void Vehicle::Die()
{
    // We're not on the plane anymore
    SetState(VEHICLE_STATE_DEAD);
    m_Owner->LoadAndInitPlayerSprite();
}
