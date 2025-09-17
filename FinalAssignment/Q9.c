#include "exam.h"

int addTripPointerToCustomer(Customer *cust, Trip *newTrip)
{
    if (!cust || !newTrip) return -1;
    if (cust->numTrips == INT_MAX) return -1;  // הגנה תאורטית

    int n = cust->numTrips;

    // מגדילים/יוצרים את המערך באיבר אחד (realloc עובד גם כשcust->trips == NULL)
    Trip** bigger = (Trip**)realloc(cust->trips, (size_t)(n + 1) * sizeof(Trip*));
    if (!bigger) return -1;  // כשל הקצאה- לא משנים כלום

    cust->trips = bigger;
    cust->trips[n] = newTrip;   // מוסיפים בסוף
    cust->numTrips = n + 1;

    return cust->numTrips;
}