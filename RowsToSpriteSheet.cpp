#include <SDL.h>
#include <iostream>

void copyToRect (SDL_Surface* source, SDL_Surface* dest, Uint16 y)
{
	SDL_Surface* dst = dest;
	SDL_Surface* src = SDL_ConvertSurface (source, dst->format, SDL_SWSURFACE);
	char* srcData = (char*)src->pixels;	
	char* dstData = (char*)dst->pixels;
	
	dstData += dst->pitch*y;
	for (int i = 0; i < src->h; ++i)
	{
		memcpy (dstData, srcData, src->w*src->format->BytesPerPixel);
		dstData += dst->pitch;
		srcData += src->pitch;
	}
	
	SDL_FreeSurface(src);
}

int main (int argc, char** argv)
{
	SDL_Init (SDL_INIT_VIDEO);
	atexit(SDL_Quit);
	
	SDL_Surface* row;
	SDL_Surface* image;
	
	if (argc < 2)
	{
		std::cerr << "Usage: program_name output_file input_file(s)";
		return -1;
	}
	
	row = SDL_LoadBMP(argv[2]);
	if (row == NULL)
	{
		std::cerr << "Error loading bitmap: " << SDL_GetError();
		return -2;
	}
	
	int numRows = argc - 2;
	std::cout << numRows << std::endl;
	image = SDL_CreateRGBSurface(SDL_SWSURFACE, row->w, row->h*numRows, 
		32, 0xff000000, 0xff0000, 0xff00, 0x00);
		//frame->format->BitsPerPixel, 
		//frame->format->Rmask, frame->format->Gmask, frame->format->Bmask, 
		//frame->format->Amask);
	
	copyToRect(row, image, 0);
	
	for (int i = 3; i < argc; ++i)
	{
		std::cout << i << std::endl;
		SDL_FreeSurface(row);
		row = SDL_LoadBMP(argv[i]);
		if (row  == NULL)
		{
			std::cerr << "Error loading bitmap: " << SDL_GetError();
			return -2;
		}
		copyToRect(row, image, (i-2)*row->h);
	}
	
	SDL_SaveBMP (image, argv[1]);
	SDL_FreeSurface(image);
	SDL_FreeSurface(row);
	return 0;
}
