#include "Ball.h"

Ball::Ball(int yPositionMax, int xPositionMax, int xDividerPosition, int delayInMicroseconds, Wall * wall) {

    this -> xMax = xPositionMax;
    this -> yMax = yPositionMax;
    this -> xDividerPosition = xDividerPosition;
    this -> wall = wall;

    this -> y = yPositionMax;
    this -> x = xPositionMax / 2;

    this -> delayInMicroseconds = delayInMicroseconds;

    xMin = 0;
    yMin = 0;

    angle = getRandomAngle();

    direction = 1;

    ballMutex = new pthread_mutex_t;
    pthread_mutex_init(ballMutex, NULL);
}

Ball::Ball() {

};

int Ball::getX() {
    return x;
}

int Ball::getY() {
    return y;
}

void *Ball::start() {
    this->endThreadFlag = false;
    while(!endThreadFlag) {
        usleep(delayInMicroseconds);
        pthread_mutex_lock(ballMutex);
        move();
        pthread_mutex_unlock(ballMutex);
    }
    pthread_exit(NULL);
}

void * Ball::getItRolling(void *ballObject) {
    return ((Ball *)ballObject)-> start();
}

void Ball::move() {

    if(angle == 45) {
        y -= direction;
        x += direction;

        if((y == yMin && x == xMax) || (y == yMax && x == xMin))
            direction *= -1;

        else if(x == xMax || x == xMin)
            angle = 135;

        else if(y == yMin || y == yMax) {
            angle = 135;
            direction *= -1;
        }
    }

    else if(angle == 135) {
        y -= direction;
        x -= direction;

        if((y == yMin && x == xMin) || (y == yMax && x == xMax))
            direction *= -1;

        else if(x == xMin || x == xMax)
            angle = 45;

        else if(y == yMin || y == yMax) {
            angle = 45;
            direction *= -1;
        }
    }

    else {
        y -= direction;

        if(y >= yMax || y <= yMin)
            direction *= -1;
    }

    if(x == xDividerPosition)
        blockMovement();

}

int Ball::getRandomAngle() {
    int randomValue = rand() % 100;

    if(randomValue < ZERO_DEGREES_PERCENT_PROBABILITY)
        return 0;
    else if(randomValue < ZERO_DEGREES_PERCENT_PROBABILITY + FORTY_FIVE_DEGREES_PERCENT_PROBABILITY)
        return 45;
    return 135;
}

void Ball::endRunningThread() {
    endThreadFlag = true;
}

void Ball::blockMovement() {
    wall -> blockBall(ballMutex);
}
