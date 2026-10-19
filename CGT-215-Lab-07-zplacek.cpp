#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>

using namespace std;
using namespace sf;
using namespace sfp;

int main()
{
	RenderWindow window(VideoMode(800, 600), "Bounce"); // creates window
	World world(Vector2f(0, 1)); // with gravity downwards

    PhysicsCircle ball; // creates ball
    ball.setCenter(Vector2f(400, 200));
    ball.setRadius(20);
    world.AddPhysicsBody(ball);

    // gives ball an initial push to start scene
    ball.applyImpulse(Vector2f(0.7f, -0.9f));
    // SCENE
    // floor
    PhysicsRectangle floor;
    floor.setSize(Vector2f(800, 20));
    floor.setCenter(Vector2f(400, 590));
	floor.setStatic(true); // doesn't move
	world.AddPhysicsBody(floor); // adds floor to scene
    // left wall
    PhysicsRectangle leftWall;
    leftWall.setSize(Vector2f(20, 600));
    leftWall.setCenter(Vector2f(10, 300));
    leftWall.setStatic(true); // doesn't move
	world.AddPhysicsBody(leftWall); // adds left wall to scene
    // right wall
    PhysicsRectangle rightWall;
    rightWall.setSize(Vector2f(20, 600));
    rightWall.setCenter(Vector2f(790, 300));
    rightWall.setStatic(true); // doesn't move
	world.AddPhysicsBody(rightWall); // adds right wall to scene
    // ceiling
    PhysicsRectangle ceiling;
    ceiling.setSize(Vector2f(800, 20));
    ceiling.setCenter(Vector2f(400, 10));
    ceiling.setStatic(true); // doesn't move
	world.AddPhysicsBody(ceiling); // adds ceiling to scene
    // middle box
    PhysicsRectangle target;
    target.setSize(Vector2f(200, 40));
    target.setCenter(Vector2f(400, 300));
    target.setStatic(true); // doesn't move
	world.AddPhysicsBody(target); // adds target to scene
    
	// collision noise counters
    int thudCount = 0;
    int bangCount = 0;
    //thud
    auto thudLambda = [&](PhysicsBodyCollisionResult result) { 
		cout << "thud " << thudCount << endl; // prints thud count
        thudCount++;
        };

    floor.onCollision = thudLambda; 
    leftWall.onCollision = thudLambda;
    rightWall.onCollision = thudLambda;
    ceiling.onCollision = thudLambda;
    // bang
    target.onCollision = [&](PhysicsBodyCollisionResult result) {
		cout << "bang " << bangCount << endl; // prints bang count
        bangCount++; 
		// exit after 3 bangs
        if (bangCount >= 3) {
            cout << "Target box hit three times." << endl;
            exit(0);
        }
        };

	// clock for timing
    Clock clock;
    Time lastTime(clock.getElapsedTime());

	// main loop
    while (window.isOpen()) {

        // time since last frame
        Time currentTime(clock.getElapsedTime());
        Time deltaTime(currentTime - lastTime);
        int deltaMS = deltaTime.asMilliseconds();

		if (deltaMS > 0) { // only update if time has passed
            world.UpdatePhysics(deltaMS);
            lastTime = currentTime;
        }

        // draws everything
        window.clear(Color::Black);
        window.draw(ball);
        window.draw(floor);
        window.draw(leftWall);
        window.draw(rightWall);
        window.draw(ceiling);
        window.draw(target);
        window.display();
    }
}

