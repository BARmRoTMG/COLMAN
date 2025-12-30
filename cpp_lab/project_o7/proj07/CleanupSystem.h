#pragma once
#include "World.h"
#include <vector>

class CleanupSystem
{
public:
    void Update(World& world)
    {
        // קבל את כל הרכבים
        auto cars = world.View<CarTag, Position>();

        // רשימה של רכבים למחיקה (לא נמחק בזמן הלולאה)
        std::vector<Entity> toDelete;

        for (Entity carEntity : cars)
        {
            auto& pos = world.GetComponent<Position>(carEntity);

            // בדוק אם הרכב יצא מגבולות המסך
            if (isOutOfBounds(pos))
            {
                toDelete.push_back(carEntity);
            }
        }

        // מחק את כל הרכבים שיצאו מהמסך
        for (Entity e : toDelete)
        {
            world.DestroyEntity(e);
        }
    }

private:
    bool isOutOfBounds(const Position& pos) const
    {
        // התאם את הגבולות לפי גודל החלון שלך
        const float screenWidth = 800.0f;   // רוחב המסך
        const float screenHeight = 600.0f;  // גובה המסך
        const float margin = 100.0f;        // מרווח בטיחות

        return pos.x < -margin ||
            pos.x > screenWidth + margin ||
            pos.y < -margin ||
            pos.y > screenHeight + margin;
    }
};