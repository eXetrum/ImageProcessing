#include <SFML/Graphics.hpp>
#include "LFSR.hpp"
#include <iostream>
#include <string>
using namespace std;

sf::Image transformImg(sf::Image const &image_in, LFSR &lfsr);
void printUsage();

int main(int argc, char *argv[]) {
	// Check if we have enough cmd arguments
	if(argc != 5) {
		printUsage();
		return 0;
	}
	// Get command arguments
	string file_in	= argv[1];
	string file_out = argv[2];
	string seed		= argv[3];
	int tap			= atoi(argv[4]);
	// Create LFSR object with initial seed and tap
	LFSR lfsr(seed, tap);
	// Load input image
	sf::Image image_in, image_out;
	if (!image_in.loadFromFile(file_in))
		return -1;
	// Get image resolution
	sf::Vector2u size = image_in.getSize();
	// Create two windows
	sf::RenderWindow window1(sf::VideoMode(size.x, size.y), "Original image");
	sf::RenderWindow window2(sf::VideoMode(size.x, size.y), "Encrypted/Decrypted image");
	// Get desktop resolution
	sf::VideoMode mode = sf::VideoMode ::getDesktopMode();
	// Calculate center of the screen
	int center_y = mode.height / 2;
	int center_x = mode.width / 2;
	// Set windows position to the center and in same time not overlap each other
	window1.setPosition(sf::Vector2i(center_x - size.x, center_y - size.y / 2));
	window2.setPosition(sf::Vector2i(center_x + 20,     center_y - size.y / 2));
	// Create textures and sprites
	sf::Texture texture1, texture2;
	sf::Sprite sprite1, sprite2;
	// Set input image to the texture and add texture to the sprite
	texture1.loadFromImage(image_in);	
	sprite1.setTexture(texture1);

	// EncryptDecrypt
	image_out = transformImg(image_in, lfsr);
	// Save output image
	if (!image_out.saveToFile(file_out))
		return -1;
	// Load output image to the texture and add texture to the sprite
	texture2.loadFromImage(image_out);
	sprite2.setTexture(texture2);
	// Message queue loop
	while (window1.isOpen() && window2.isOpen()) { 
		sf::Event event;
		while (window1.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window1.close();
		}
		while (window2.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window2.close();
		}
		window1.clear();
		window1.draw( sprite1 );
		window1.display();
		window2.clear();
		window2.draw( sprite2 );
		window2.display();
	}

	return 0;
}

sf::Image transformImg(sf::Image const &image_in, LFSR &lfsr) {
	// Create empty image
	sf::Image image_out;
	// Get input image resolution
	sf::Vector2u size = image_in.getSize();
	// Create output image with same resolution
	image_out.create(size.x, size.y, sf::Color::White); 
	// p is a pixel
	sf::Color p;
	// Iterate throught image pixels
	for (size_t x = 0; x < size.x; x++) {
		for (size_t y = 0; y < size.y; y++) {
			// Generate pseudo random values using LFSR object for each pixel component
			unsigned char redByte = static_cast<unsigned char>( lfsr.generate(8) );
			unsigned char greenByte = static_cast<unsigned char>( lfsr.generate(8) );
			unsigned char blueByte = static_cast<unsigned char>( lfsr.generate(8) );
			// Get pixel
			p = image_in.getPixel(x, y);
			// Xor each random value with current chanel component
			p.r = p.r ^ redByte;
			p.g = p.g ^ greenByte;
			p.b = p.b ^ blueByte;
			// Set new pixel to the output image
			image_out.setPixel(x, y, p);
		}
	}
	// Return proceseed img
	return image_out;
}
// Print usage
void printUsage() {
	cout << "Usage: <input_file> <output_file> <LFSR seed> <LFSR tap>" << endl;
}
