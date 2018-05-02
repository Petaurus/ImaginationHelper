#pragma once
#include <vector>
#include <SFML\Graphics\Image.hpp>
#include "rgb_colors.h"

const int HEIGHT = 512;
const int WIDTH = 640;

class ImageCreator {
public:
	ImageCreator();
	~ImageCreator();

	void initialize(std::string linksFile);
	void create();

private:
	RGB_i8 * getImage(int t);
	void addImage(RGB_i8 * sourse);

private:
	std::vector<std::string> m_links;

	RGB_i8* m_rgbImage;
};