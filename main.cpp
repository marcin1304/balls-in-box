#include <iostream>

#include "TerminalPainter.h"

using namespace std;

int main() {
    int delayBetweenAddingBallsInSeconds;

    cout << "Delay before adding new ball (in seconds): ";
    cin >> delayBetweenAddingBallsInSeconds;
    if(delayBetweenAddingBallsInSeconds > 0) {
        TerminalPainter terminalPainter = TerminalPainter(delayBetweenAddingBallsInSeconds);
        terminalPainter.executeProgram();
    }
}
