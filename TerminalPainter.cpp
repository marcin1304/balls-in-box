#include "TerminalPainter.h"

TerminalPainter::TerminalPainter(int delayBetweenAddingBallsInSeconds) {
    this -> delayBetweenAddingBallsInSeconds = delayBetweenAddingBallsInSeconds;

    balls = new std::vector<Ball *>();
    ballThreads = new std::vector<pthread_t>();

    wall = Wall();
    pthread_create(&wallThread, nullptr, Wall::getItRolling, &wall);
}

void TerminalPainter::executeProgram(){

    initializeTerminal();

    refreshBallsPosition();

    balls -> clear();
    ballThreads -> clear();

    endwin();
}

void TerminalPainter::initializeTerminal() {
    initscr();
    noecho();
    curs_set(FALSE);

    int max_y, max_x;

    // returns size of terminal to max_y and max_x
    getmaxyx(stdscr, max_y, max_x);

    // max_y and max_y are transformed to represent constraints for character visibility
    max_y -= 1;
    max_x -= 1;

    this->max_y = max_y;
    this->max_x = max_x;
    this->xDividerPosition = max_x / 3;

    // prerequisite needed for generating balls' pseudo random direction
    srand (time(nullptr));

    // keyPressed won't block
    nodelay(stdscr, TRUE);
}

bool TerminalPainter::keyPressed() {
    int ch = getch();

    if (ch != ERR && ch == 's') {
        ungetch(ch);
        return true;
    } else {
        return false;
    }
}

void TerminalPainter::refreshBallsPosition() {

    int cyclesBetweenNewBalls = (this->delayBetweenAddingBallsInSeconds * 1000000) / BALL_MOVE_PERIOD;
    int cycleNumber = cyclesBetweenNewBalls;

    while(true) {
        if(keyPressed())
            break;
        if(cycleNumber  == cyclesBetweenNewBalls) {
            addBall();
            cycleNumber = 0;
        }

        clear();

        // first print the divider, this assures that ball will always be seen
//        for(int currentY = 0; currentY <= max_y; currentY++)
//            mvprintw(currentY, xDividerPosition, "|");
        mvprintw(0, xDividerPosition, "|");
        mvprintw(max_y, xDividerPosition, "|");

        for(int ballNumber = 0; ballNumber < this->balls -> size(); ballNumber++) {
            mvprintw(balls->at(ballNumber) -> getY(), balls->at(ballNumber) -> getX(), "o");
        }

        refresh();
        usleep(BALL_MOVE_PERIOD);
        cycleNumber++;
    }

    wall.disable();
    pthread_join(wallThread, NULL);
    endBallsThreads();

}

void TerminalPainter::addBall() {
    Ball * newBall = new Ball(max_y, max_x, xDividerPosition, BALL_MOVE_PERIOD, &wall);
    balls -> push_back(newBall);
    pthread_t pthread;
    pthread_create(&pthread, nullptr, Ball::getItRolling, newBall);
    ballThreads -> push_back(pthread);
}

void TerminalPainter::endBallsThreads() {
    int size = balls->size();
    for(int i = 0; i < size ; i++)
        balls->at(i)->endRunningThread();

    for(int i = 0; i < size ; i++)
        pthread_join(ballThreads->at(i), NULL);
}