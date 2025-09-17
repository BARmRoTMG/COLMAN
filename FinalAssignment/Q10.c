#include "exam.h"

char* findTopVisitorToDestination(MoovitDB *db, char *destination)
{
    // בדיקות
    if (!db || !destination || db->numCustomers <= 0 || !db->customers)
        return NULL;

    // מספר נסיעות מקסימאלי
    int maxCount = 0;
    char* bestName = NULL;

    for (int i = 0; i < db->numCustomers; ++i)
    {
        Customer* c = db->customers[i];
        if (!c || !c->trips || c->numTrips <= 0) continue;

        int count = 0;
        for (int j = 0; j < c->numTrips; ++j)
        {
            Trip* t = c->trips[j];
            if (!t || !t->endTrip) continue;
            if (strcmp(t->endTrip, destination) == 0)
            {
                ++count;
            }
        }

        // עדכון מקסימום: מחליף רק אם גדול באמת - שוברת שוויון לטובת הראשון
        if (count > maxCount)
        {
            maxCount = count;
            bestName = c->fullName; // החזרה תהיה המצביע הזה - לא להקצות/לשחרר
        }
    }

    // אם לא נמצא אף לקוח עם לפחות נסיעה אחת ליעד — נחזיר NULL
    return (maxCount > 0) ? bestName : NULL;
}
