#include <SFML\Graphics.hpp>
#include <iostream>
#include "imageCreator.h"

int main() {
	ImageCreator creator;

	creator.initialize("imagesLinks.txt");
	creator.create();

	//system("pause");
}