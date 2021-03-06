//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// paddle location
#define PADDLEX 550


// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);


int main(void)
{

    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    // keep playing until game over
    
    double velocityX = drand48(), velocityY = 1.0;
 
    waitForClick();
    while (lives > 0 && bricks > 0)
    
    {

        //Sets paddle to mouse location
    
        GEvent movement = getNextEvent(MOUSE_EVENT);
            if (movement != NULL)
            {
                if (getEventType(movement) == MOUSE_MOVED)
                {
                    double x = getX(movement);
                    setLocation(paddle, x, PADDLEX);
                }
            }
            
        //Sets ball in motion
        
            move(ball, velocityX, velocityY);
            
            // Change horizontal direction
            
            if (getX(ball) + getWidth(ball) >= getWidth(window))
            {
                velocityX = -velocityX;
            }
        
            else if (getX(ball) <= 0)
            {
                velocityX = -velocityX;
            } 
            
            // Change vertical direction & takes life if you hit the bottom
            
            if (getY(ball) + getHeight(ball) >= getHeight(window))
            {
                velocityY = -velocityY;
                lives--;
                setLocation(ball, 192.5, 292.5);
                waitForClick();
            }
        
            else if (getY(ball) <= 0)
            {
                velocityY = -velocityY;
            }
            
            // Changes if hits paddle & bricks
            
            GObject object = detectCollision(window, ball);
            
            if (object != NULL)
            {
                if (strcmp(getType(object), "GRect") == 0)
                {
                velocityY = -velocityY;
                }
                if (object != paddle && object != label)
                {
                removeGWindow(window, object);
                
                points++;
                updateScoreboard(window, label, points);
                
                }   
            } 
            pause(3);
        }
        

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{

for (int j = 0, spaceY = 60; j < ROWS; j++, spaceY = spaceY + 15)
{ 
    for (int i = 0, spaceX = 10; i < COLS; i++, spaceX = spaceX + 39)
    {
        GRect brick = newGRect(spaceX,spaceY,30,7);
        setFilled(brick, true);
        
        if (j == 0)
        {
        setColor(brick, "Blue");
        }
        else if (j == 1)
        {
        setColor(brick, "Red");
        }
        else if (j == 2)
        {
        setColor(brick, "Yellow");
        }
        else if (j == 3)
        {
        setColor(brick, "Green");
        }
        else
        {
        setColor(brick, "Orange");
        }
        
        add(window, brick);
    }
}
}
/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval ball = newGOval(192.5, 292.5, 15, 15);
    setFilled(ball, true);
    setColor(ball, "Black");
    add(window, ball);
    
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    
    GRect paddle = newGRect(PADDLEX,550,80,20);
    setFilled(paddle, true);
    setColor(paddle, "Black");
    add(window, paddle);
    
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel("0");
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);  
    setFont(label, "SansSerif-30");
    setColor(label,"Gray");
    add(window, label);
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */

void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
