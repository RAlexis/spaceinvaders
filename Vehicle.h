#ifndef _PLANE_H
#define _PLANE_H

#include "Player.h"

class Player;

#define DEFAULT_PLANE_HEALTH 300

enum VehicleState
{
    VEHICLE_STATE_DEAD  = 0,
    VEHICLE_STATE_ALIVE = 1
};

enum VehicleType
{
    VEHICLE_TYPE_NONE = 0,
    VEHICLE_TYPE_CAR = 1,
    VEHICLE_TYPE_PLANE = 2,
    VEHICLE_TYPE_HELICOPTER = 3
};

class Vehicle
{
    public:
        Vehicle(Player* player);
        ~Vehicle();

        void Reset();
        void Die();

        void SetHealth(int value)
        {
            m_health = value;
        }

        int GetHealth()
        {
            return m_health;
        }

        void SetMaxHealth(int value)
        {
            m_maxHealth = value;
        }

        int GetMaxHealth()
        {
            return m_maxHealth;
        }

       void SetType(int value)
        {
            m_type = value;
        }

        int GetType()
        {
            return m_type;
        }

        void SetState(int state)
        {
            m_state = state;
        }

        int GetState()
        {
            return m_state;
        }

    private:
        int m_health;
        int m_maxHealth;

        int m_type; // Vehicle type
        int m_state; // Vehicle state (dead / alive)

        Player* m_Owner; // Who's on the plane
};

#endif