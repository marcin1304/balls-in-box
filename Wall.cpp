#include "Wall.h"

Wall::Wall() {
    blockedBalls = new std::vector<pthread_mutex_t *>();
    enabled = true;
    newBallsNumber = 0;
    blockedBallsMutex = new pthread_mutex_t;
    blockedBallsAddingThread = new pthread_t;
}

void *Wall::run() {
    int counter = 0;
    while(enabled) {
        pthread_mutex_lock(blockedBallsMutex);
        while (newBallsNumber) {
            pthread_mutex_lock(blockedBalls->at((blockedBalls -> size()) - newBallsNumber));
            newBallsNumber--;
        }

        if(counter == 50) {
            unblockLastBall();
            counter = 0;
        }
        pthread_mutex_unlock(blockedBallsMutex);
        counter++;
        usleep(20000);
    }
    pthread_mutex_lock(blockedBallsMutex);
    unblockAllBalls();
    pthread_mutex_unlock(blockedBallsMutex);
}

void Wall::unblockLastBall() {
    if(!blockedBalls -> empty()) {
        pthread_mutex_unlock(blockedBalls->back());
        blockedBalls->pop_back();
    }
}

void Wall::unblockAllBalls() {
    int blockedBallsNumber = blockedBalls -> size();
    for(int index = 0; index < blockedBallsNumber; index++)
        unblockLastBall();
}

void *Wall::getItRolling(void *wallObject) {
    return ((Wall *)wallObject)-> run();
}

void Wall::disable() {
    enabled = false;
}

void Wall::blockBall(pthread_mutex_t *mutex) {
    if(enabled) {
        pthread_mutex_lock(blockedBallsMutex);
        blockedBalls->push_back(mutex);
        newBallsNumber += 1;
        pthread_mutex_unlock(blockedBallsMutex);

    }
}
