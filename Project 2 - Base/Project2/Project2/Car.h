#pragma once

enum class Direction
{
    North = 0,
    East,
    South,
    West
};

struct Car
{
    int         m_id;
    Direction   m_dir;
    float       m_waitTime = 0.f;
    bool        m_crossing = false;
};