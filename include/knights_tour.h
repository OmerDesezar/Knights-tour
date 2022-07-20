#ifndef __KNIGHTS_TOUR_H__
#define __KNIGHTS_TOUR_H__

typedef enum return_status
{
    TRUE,
    FALSE,
    TIMEOUT
} return_status_t;

return_status_t KnightsTour(unsigned char, unsigned, unsigned char *);

return_status_t WarnsdorffKnightsTour(unsigned char, unsigned char, unsigned char *);

#endif /*__KNIGHTS_TOUR_H__*/