#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>

using namespace std;
using namespace sf;
using namespace sfp;
int main()
{

	RenderWindow window(VideoMode(800, 600), "Bounce");
	World world(Vector2f(0, 1));

	PhysicsCircle ball;
	ball.setCenter(Vector2f(400, 150));
	ball.setRadius(15);
	world.AddPhysicsBody(ball);
	ball.applyImpulse(Vector2f(10, 0));

	PhysicsRectangle centeredRect;
	centeredRect.setSize(Vector2f(100, 100));
	centeredRect.setCenter(Vector2f(400, 300));
	centeredRect.setStatic(true);
	world.AddPhysicsBody(centeredRect);

	PhysicsRectangle floor;
	floor.setSize(Vector2f(800, 20));
	floor.setCenter(Vector2f(400, 590));
	floor.setStatic(true);
	world.AddPhysicsBody(floor);

	PhysicsRectangle ceiling;
	ceiling.setSize(Vector2f(800, 20));
	ceiling.setCenter(Vector2f(400, 10)); // Adjust the position
	ceiling.setStatic(true);
	world.AddPhysicsBody(ceiling);

	PhysicsRectangle leftWall;
	leftWall.setSize(Vector2f(20, 600));
	leftWall.setCenter(Vector2f(10, 300)); // Adjust the position
	leftWall.setStatic(true);
	world.AddPhysicsBody(leftWall);

	PhysicsRectangle rightWall;
	rightWall.setSize(Vector2f(20, 600));
	rightWall.setCenter(Vector2f(790, 300)); // Adjust the position
	rightWall.setStatic(true);
	world.AddPhysicsBody(rightWall);

	int thudCount(0); \

		centeredRect.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
		};


	Clock clock;
	Time lastTime(clock.getElapsedTime());
	while (true) {
		// calculate MS since last frame
		Time currentTime(clock.getElapsedTime());
		Time deltaTime(currentTime - lastTime);
		int deltaTimeMS(deltaTime.asMilliseconds());
		if (deltaTimeMS > 0) {
			world.UpdatePhysics(deltaTimeMS);
			lastTime = currentTime;
		}
		window.clear(Color(0, 0, 0));
		window.draw(ball);
		window.draw(floor);
		window.draw(ceiling);
		window.draw(leftWall);
		window.draw(rightWall);
		window.draw(centeredRect);
		window.display();
	}
}