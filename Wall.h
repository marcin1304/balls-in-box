#ifndef SO2_P1_WALL_H
#define SO2_P1_WALL_H

#include <vector>
#include <pthread.h>
#include <unistd.h>
#include <ncurses.h>

class Wall {
private:
    std::vector<pthread_mutex_t *> * blockedBalls;
    pthread_mutex_t * blockedBallsMutex;
    pthread_t * blockedBallsAddingThread;
    bool enabled;
    void *run();
    void unblockLastBall();
    void unblockAllBalls();
    int newBallsNumber;

public:
    Wall();
    static void *getItRolling(void *wallObject);
    void disable();
    void blockBall(pthread_mutex_t * mutex);
};


#endif //SO2_P1_WALL_H
