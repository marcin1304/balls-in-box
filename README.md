#### Balls in a box simulator - terminal application
Program adds new ball in periods provided by the user. Ball starts moving in 1 of 3 directions (45, 90 or 135 degrees) randomly and when touches a terminal border it bounces. In 1/3 of the terminal width a special barrier is created, if ball is in the barrier it is stopped. The barrier lets the most recently stopped ball continue movement every 1 second.  User can terminate program by pressing 's' button. \
Each ball is created on a separate thread, balls are printed with ncurses
