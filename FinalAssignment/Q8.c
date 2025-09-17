#include "exam.h"

Trip** getMostExpensiveTrips(const MoovitDB* db)
{
    if (!db || db->numCustomers <= 0) return NULL;

    Trip** result = (Trip**)calloc(db->numCustomers, sizeof(Trip*));
    if (!result) return NULL;  // כשל הקצאה

    for (int i = 0; i < db->numCustomers; ++i)
    {
        Customer* c = (db->customers ? db->customers[i] : NULL);

        if (!c || !c->trips || c->numTrips <= 0)
        {
            result[i] = NULL;                 // אין נסיעות ללקוח הזה
            continue;
        }

        Trip* best = NULL;
        int   bestCost = 0;

        for (int j = 0; j < c->numTrips; ++j)
        {
            Trip* t = c->trips[j];
            if (!t) continue;
            if (!best || t->costTrip > bestCost)
            { // '>': שוברת שוויון לטובת הראשונה
                best = t;
                bestCost = t->costTrip;
            }
        }

        result[i] = best;  // יכול להישאר NULL אם כל המצביעים היו NULL
    }

    return result;  // caller: free(result); לא משחררים את ה-Trip עצמם
}