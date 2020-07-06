#ifndef SO2_P1_BALL_H
#define SO2_P1_BALL_H

#include <ncurses.h>
#include <random>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <random>
#include <semaphore.h>
#include <vector>
#include "Wall.h"

// below probabilities have to sum up to 100
#define ZERO_DEGREES_PERCENT_PROBABILITY 40
#define FORTY_FIVE_DEGREES_PERCENT_PROBABILITY 35
#define HUNDRED_THIRTY_FIVE_DEGREES_PERCENT_PROBABILITY 25

class Ball {
    private:
        int y{};
        int x{};
        int xMax{};
        int yMax{};
        int xMin{};
        int yMin{};
        int xDividerPosition{};
        int angle{};
        int direction{};
        int delayInMicroseconds{};
        bool endThreadFlag{};
        pthread_mutex_t *ballMutex;
        void *start();
        void move();
        static int getRandomAngle();

        Wall * wall;
        void blockMovement();

    public:
        Ball();
        Ball(int yPositionMax, int xPositionMax, int xDividerPosition, int delayInMicroseconds, Wall * wall);
        int getX();
        int getY();
        static void *getItRolling(void *ballObject);
        void endRunningThread();
};


#endif //SO2_P1_BALL_H
