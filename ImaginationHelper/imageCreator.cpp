#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <urlmon.h>
#include <ctime>
#include <cstdio>
#include <assert.h>
#include <gdiplus.h>
#include "imageCreator.h"
#include "filters.h"
#include "vec2.h"

void WriteToBMP(uint8_t * image, const char* fileName);

const int imagesCount = 5;
const int string_size = 255;

ImageCreator::ImageCreator() {
	m_rgbImage = new RGB_i8[HEIGHT * WIDTH];
}

ImageCreator::~ImageCreator() {
	if (m_rgbImage) {
		delete[] m_rgbImage;
	}
}

void ImageCreator::initialize(std::string linksFile) {
	srand(time(0));

	std::ifstream input(linksFile);
	char stream_link[string_size];
	m_links.resize(imagesCount);

	int count = 0;
	while (input >> stream_link) {
		if (count < imagesCount) {
			m_links[count] = std::string(stream_link);
		}
		else if(rand() % 2) {
			m_links[rand() % imagesCount] = std::string(stream_link);
		}
		count++;
	}

	input.close();
}

RGB_i8 * ImageCreator::getImage(int t) {

	std::string link = *(m_links.begin() + t);
	std::string format = link.substr(link.size() - 4, 4);
	sf::Image tmp;

	const char* path = 0;
	// Check if this is link to image
	if (link.substr(0, 4) == "http") {
		if(format == "jpeg" || format == ".jpg") {
			path = "tmp.jpg";
		}
		else if (format == ".png") {
			path = "tmp.png";
		}
		else if (format == ".bmp") {
			path = "tmp.bmp";
		}

		// Download image
		if (path != 0) {
			URLDownloadToFile(0, link.c_str(), path, 0, 0);
		}
		// Load image to memory
		assert( tmp.loadFromFile(path) );
		// Delete image
		remove(path);
	}
	// If this is path to image
	else {
		assert(tmp.loadFromFile(link));
	}

	// Calculate the position and size of part of the image to use
	int x = (int)(WIDTH - tmp.getSize().x) / 2;
	int y = (int)(HEIGHT - tmp.getSize().y) / 2;
	int left = (x < 0) ? 0 : x;
	int top = (y < 0) ? 0 : y;
	int width = (tmp.getSize().x > WIDTH) ? WIDTH : tmp.getSize().x;
	int height = (tmp.getSize().y > HEIGHT) ? HEIGHT : tmp.getSize().y;

	sf::IntRect sourseRect( (x < 0)? -x : 0, (y < 0)? -y : 0, width, height);

	// Copy the used part
	sf::Image image;
	image.create(WIDTH, HEIGHT);
	image.copy(tmp, left, top, sourseRect);

	// Get RGB image
	const sf::Uint8 * imagePtr = image.getPixelsPtr();
	uint8_t * result = new sf::Uint8[WIDTH * HEIGHT * 3];
	for (int i = 0; i < WIDTH * HEIGHT; i++) {
		for (int j = 0; j < 3; j++) {
			result[i * 3 + j] = imagePtr[i * 4 + j];
		}
	}

	return (RGB_i8*)result;
}

void ImageCreator::addImage(RGB_i8 * sourse) {
	// Use random filter
	switch (rand() % 3)
	{
	case 0:
		average(m_rgbImage, sourse);
		break;
	case 1:
		multiplication(m_rgbImage, sourse);
		break;
	case 2:
		lighting(m_rgbImage, sourse);
		break;
	}
}

void ImageCreator::create() {
	m_rgbImage = getImage(0);

	for (int i = 1; i < imagesCount; i++) {

		addImage(getImage(i));
	}

	//smoothingImage(m_rgbImage, 40);
	WriteToBMP((uint8_t*)m_rgbImage, "output.bmp");
}

void WriteToBMP(uint8_t * image, const char* fileName) {

	FILE* file = fopen(fileName, "wb");

	if (file)
	{
		// Create BMP header
		int imageSizeInBytes = 3 * WIDTH * HEIGHT;
		int headersSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
		int fileSize = headersSize + imageSizeInBytes;

		uint8_t * pData = new uint8_t[headersSize];

		if (pData != NULL)
		{
			BITMAPFILEHEADER& bfHeader = *((BITMAPFILEHEADER *)(pData));

			bfHeader.bfType = 'MB';
			bfHeader.bfSize = fileSize;
			bfHeader.bfOffBits = headersSize;
			bfHeader.bfReserved1 = bfHeader.bfReserved2 = 0;

			BITMAPINFOHEADER& bmiHeader = *((BITMAPINFOHEADER *)(pData + headersSize - sizeof(BITMAPINFOHEADER)));

			bmiHeader.biBitCount = 3 * 8;
			bmiHeader.biWidth = WIDTH;
			bmiHeader.biHeight = HEIGHT;
			bmiHeader.biPlanes = 1;
			bmiHeader.biSize = sizeof(bmiHeader);
			bmiHeader.biCompression = BI_RGB;
			bmiHeader.biClrImportant = bmiHeader.biClrUsed =
				bmiHeader.biSizeImage = bmiHeader.biXPelsPerMeter =
				bmiHeader.biYPelsPerMeter = 0;

			fwrite(pData, headersSize, 1, file);

			// Write image data
			uint8_t *pBits = image + HEIGHT * WIDTH * 3 - WIDTH * 3;
			int nSpan = -WIDTH * 3;

			int numberOfBytesToWrite = 3 * WIDTH;

			for (size_t i = 0; i < HEIGHT; ++i, pBits += nSpan)
			{
				fwrite(pBits, numberOfBytesToWrite, 1, file);
			}
			delete[] pData;
		}

		fclose(file);
	}

}