// SFML_Test.cpp : snake game

  
#include <SFML/Graphics.hpp>   //using namespace sf

#include <time.h>

  

//dimensions for window size and background


int num_vertBox = 30, num_horzBox = 20;

int size = 16; //number of pixels

int w = size * num_horzBox;  //background number of pixels in width

int h = size * num_vertBox;    //background number of pixels in height

  

//Snake variables to dertermine length and direction

int direction, direction2;    //direction the snake is moving

int snake_length = 4; //initial size is 4

int snake2_length = 4; // initial size for second snake

float timer = 0.0f, delay = 0.1f;

//Actual Snake in game is an array of x,y coordinates of sprite2

struct Snake

{
    
    int x, y;        //each sprite of snake needs an x,y coordinate
    
}s[100];

struct Snake2

{
    
    int a, b;        //each sprite of snake needs an x,y coordinate
    
}n[100];


  

//***NEW*** this is the fruit or food that the snake will eat

struct Fruit

{
    
    int x, y;    // only need one sprite needed for one food item
    
}food;

  

//move snake head based on user input and body by incrementing

//forward by iterating through arrays previous position

void move() {
    
      
    
    //1st update body so everything updates in proper order
    
    //move the body only!  s[0] = head will not be changed here
    
    for (int i = snake_length; i > 0; i--)
        
    {
        
        s[i].x = s[i - 1].x;
        
        s[i].y = s[i - 1].y;
        
    }
    for (int i = snake2_length; i > 0; i--)
        
    {
        
        n[i].a = n[i - 1].a;
        
        n[i].b = n[i - 1].b;
        
    }
    
    //2nd update the head
    
    //Head of snake, s[0] depends on direction user inputs
    
    //User Down
    if (direction == 0)
        s[0].y -= 1;
    //User Left
    if (direction == 1)
        s[0].y += 1;
    //User Right
    if (direction == 2)
        s[0].x -= 1;
    //User Up
    if (direction == 3)
        s[0].x += 1;
    
    //direction of user n[0] for snake 2
    //User Down
    if (direction2 == 0)
        n[0].b += 1;
    //User Left
    if (direction2 == 1)
     n[0].a -= 1;
    //User Right
    if (direction2 == 2)
    n[0].a += 1;
    //User up
    if (direction2 == 3)
     n[0].b -= 1;
   
    
    //***NEW*** If Snake eats food it should grow
    
    //check if snake head = food location
    
    if (((s[0].x) == food.x) && ((s[0].y) == food.y))
        
    {
        
        //increment snake
        
        snake_length++;
        delay -= 0.001f;
        
        //Randomly place food somewhere else
        
        food.x = rand() % num_horzBox;
        
        food.y = rand() % num_vertBox;
        
    }
    
  //increment snake2
    if (((n[0].a) == food.x) && ((n[0].b) == food.y))
        
    {
        
        //increment snake
        
        snake2_length++;
        delay -= 0.001f;
          
        
        //Randomly place food somewhere else
        
        food.x = rand() % num_horzBox;
        
        food.y = rand() % num_vertBox;
        
    }
    
    
      
    
    //***NEW*** Boundary Checking snake as is hits screen end
    
    //loop snake back on other side
    
    //LEFT and RIGHT
    
    if (s[0].x > num_horzBox)
        
        s[0].x = 0;
    
    if (s[0].x < 0)
        
        s[0].x = num_horzBox;
    
    //TOP and BOTTOM
    
    if (s[0].y > num_vertBox)
        
        s[0].y = 0;
    
    if (s[0].y < 0)
        
        s[0].y = num_vertBox;
    
   //snake 2
    
    //LEFT AND RIGHT
    if (n[0].a > num_horzBox)
        
        n[0].a = 0;
    
    if (n[0].a < 0)
        
        n[0].a = num_horzBox;
    
    //TOP and BOTTOM
    
    if (n[0].b > num_vertBox)
        
        n[0].b = 0;
    
    if (n[0].b < 0)
        
        n[0].b = num_vertBox;
    
 
    //***NEW*** Check if you eat body of snake
    
    for (int i = 1; i < snake_length; i++)
        
    {
        
        //Cut Snake body from place eaten
        
        if (s[0].x == s[i].x && s[0].y == s[i].y)
            
            snake_length = i;
        
    }
    //snake2
    for (int i = 1; i < snake_length; i++)
        
    {
        
        //Cut Snake body from place eaten
        
        if (n[0].a == n[i].a && n[0].b == n[i].b)
            
            snake2_length = i;
        
    }
    
}

int main()

{
    
    //Setting pseudorandom time, TODO:discuss true random vs pseudorandom
    
    srand(time(0));
    
      
    
    //Window that we can play the game in
    
    sf::RenderWindow window(sf::VideoMode(w, h), "Snake Game");
    
      
    
    //Textures load an image into the GPU Memory
    
    sf::Texture t1, t2, t3, t4; //t4 is color of snake2
    
    t1.loadFromFile("/Users/kenneth-matthewvelarde/Desktop/testXcode/smfl_clt/smfl_clt/images/white.png");
    
    t2.loadFromFile("/Users/kenneth-matthewvelarde/Desktop/testXcode/smfl_clt/smfl_clt/images/red.png");
    
    t3.loadFromFile("/Users/kenneth-matthewvelarde/Desktop/testXcode/smfl_clt/smfl_clt/images/pen.gif");
    
    t4.loadFromFile("/Users/kenneth-matthewvelarde/Desktop/testXcode/smfl_clt/smfl_clt/images/green.png");
    
    //Sprite has physical dimmensions that can be set in
    
    //coordinate system, setPosition(x,y), and drawn on screen
    
    sf::Sprite sprite1(t1);
    
    sf::Sprite sprite2(t2);
    
    sf::Sprite sprite3(t3);
    
    sf::Sprite sprite4(t4);
    
    //***NEW*** initially place food somewhere on screen
    
    food.x = 10;
    
    food.y = 10;
    
      
    
    sf::Clock clock;
    
//    float timer = 0.0f, delay = 0.1f;
    
    while (window.isOpen())
        
    {
        
        //Error in class I placed this before the while loop
        
        //Should be placed in while loop as shown here to update
        
        //timer
        
        float time = clock.getElapsedTime().asSeconds();
        
        clock.restart();
        
        timer += time;
        
          
        
        //Allow us to check when a user does something
        
        sf::Event e;
        
          
        
        //Check when the window is closed
        
        while (window.pollEvent(e))
            
        {
            
            //If user presses x in the top right, Windows, top left, Mac,  close the window
            
            if (e.type == sf::Event::Closed)
                
            {
                
                window.close();
                
            }
            
        }
        
          
        
        //Control for Snake by User
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) direction = 0;
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) direction = 1;
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) direction = 2;
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) direction = 3;
        
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) direction2 = 0;
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) direction2 = 1;
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) direction2 = 2;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) direction2 = 3;
        
        if (timer > delay)
            
        {
            
            timer = 0; //reset timer
            
            move();    //move Snake one sprite forward
            
        }
        
        /*****************
         
         //Draw in window
         
         *****************/
        
        window.clear();    //clear the window so new frame can be drawn in
        
          
        
        //NOTE: Order matters as we will draw over items listed first.
        
        //Hence the background should be the first thing you will always do
        
        //1st: Draw Background first
        
        for (int i = 0; i < num_horzBox; i++)
            
        {
            
            for (int j = 0; j < num_vertBox; j++)
                
            {
                
                //Set position of sprite1 one at a time
                
                sprite1.setPosition(i*size, j*size);
                
                //Draw sprite1 but, do not show it on screen.
                
                window.draw(sprite1);
                
            }
            
        }
        
        
        //2nd: Then Draw snake otherwise background will be drawn over snake if order was reversed with background
        
        for (int i = 0; i < snake_length; i++)
            
        {
            
            //position sprite2 one at a time
            
            sprite2.setPosition(s[i].x*size, s[i].y*size);
            
            //Draw sprite2 one at a time by drawing over background
            
            window.draw(sprite2);
            
        }
     //DRAW SNAKE2 HERE
        for (int i = 0; i < snake2_length; i++)
            
        {
            
            //position sprite2 one at a time
            
            sprite4.setPosition(n[i].a*size, n[i].b*size);
            
            //Draw sprite2 one at a time by drawing over background
            
            window.draw(sprite4);
            
        }
        
          
        
        //***NEW*** 3rd: Draw Fruit
        
        sprite3.setPosition(food.x*size, food.y*size);
        
        window.draw(sprite3);
        
          
        
        //Show everything we have drawn on the screen
        
        window.display();
        
    }
    
    return 0;
    
}
