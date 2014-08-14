#include <SFML/Graphics.hpp>
#include <sstream>

/* Game system planning:
Every object has several functions that contain game logic.
- constructor
- destructor
- begin step (called before all step functions)
- step (happens every 1/60th of a second)
- end step (called after all step functions are finished)
- draw (called every 1/60th of a second. Frameskip if the framerate drops)
Every object can have different types. Examples are:
- actor (any playable or non-playable character). Those have playable, friendly, or enemy subtype.
- solid (platforms you can walk on). These should be defined by just vector lines.
- particle (step logic might be done in draw function as it is entirely cosmetic)
There's a master object for every "scene" (= every separate environment) that controls lists of actors, solids, etc. and unloads most of these at a scene change. */
// TODO: After implementing the game system, remove FPS counter from this file and add as separate game object

int main() {
	sf::RenderWindow window(sf::VideoMode(1080, 720), "SFML works!");
	sf::CircleShape shape(240.f);
	shape.setFillColor(sf::Color::Green);

	sf::Font testFont;
	if (!testFont.loadFromFile("arial.ttf")) {
		return 0;
	}

	sf::Clock clock;
	sf::Text fpsText;
	fpsText.setColor(sf::Color::White);
	fpsText.setFont(testFont);
	float currentTime;
	float fps;
	std::ostringstream ss;

	while (window.isOpen()) {
		// Every 1/60th second:
		// Handle window events here
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		// GAME LOGIC (speed can be configured, pass supposed fps to all objects!)
		// Execute Begin Step instructions (those with begin step events register to Begin Step listener)
		// Execute Step instructions (those with step events register to Step listener)
		// Execute End Step instructions (those with end step events register to End Step listener)

		currentTime = clock.restart().asSeconds();
		fps = 1.f / (currentTime);
		ss << "FPS: " << fps;
		fpsText.setString(ss.str());

		window.clear();
		window.draw(shape);
		window.draw(fpsText);
		window.display();
		ss.str(std::string());
	}

	return 0;
}