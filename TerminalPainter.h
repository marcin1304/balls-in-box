#ifndef SO2_P1_TERMINALPAINTER_H
#define SO2_P1_TERMINALPAINTER_H

#include <ncurses.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <vector>
#include <iostream>

#include "Ball.h"
#include "Wall.h"

// slightly over 30 frames per second
#define BALL_MOVE_PERIOD 33000

class TerminalPainter {
    private:
        int delayBetweenAddingBallsInSeconds;
        std::vector<Ball *> * balls;
        std::vector<pthread_t> * ballThreads;
        pthread_t wallThread;
        Wall wall;
        int max_y;
        int max_x;
        int xDividerPosition;

        void initializeTerminal();
        void addBall();
        void refreshBallsPosition();
        void endBallsThreads();

        bool keyPressed();

    public:
        explicit TerminalPainter(int delayBetweenAddingBallsInSeconds);
        void executeProgram();
};


#endif //SO2_P1_TERMINALPAINTER_H
