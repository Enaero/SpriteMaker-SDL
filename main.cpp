#include <SDL.h>
#include <iostream>

<<<<<<< HEAD
void copyToRect (SDL_Surface* source, SDL_Surface* dest, Uint16 x)
=======
void copyToRect (SDL_Surface* source, SDL_Surface* dest, Uint16 y)
>>>>>>> 22a9e7259a45f3ce263c6e657552aa7c66b55b22
{
	SDL_Surface* dst = dest;
	SDL_Surface* src = SDL_ConvertSurface (source, dst->format, SDL_SWSURFACE);
	char* srcData = (char*)src->pixels;	
	char* dstData = (char*)dst->pixels;
	
<<<<<<< HEAD
	dstData += x;
=======
	dstData += dst->pitch*y;
>>>>>>> 22a9e7259a45f3ce263c6e657552aa7c66b55b22
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
<<<<<<< HEAD
	SDL_Surface* frame;
=======
	SDL_Surface* image;
>>>>>>> 22a9e7259a45f3ce263c6e657552aa7c66b55b22
	
	if (argc < 2)
	{
		std::cerr << "Usage: program_name output_file input_file(s)";
		return -1;
	}
	
<<<<<<< HEAD
	frame = SDL_LoadBMP(argv[2]);
	if (frame == NULL)
=======
	row = SDL_LoadBMP(argv[2]);
	if (row == NULL)
>>>>>>> 22a9e7259a45f3ce263c6e657552aa7c66b55b22
	{
		std::cerr << "Error loading bitmap: " << SDL_GetError();
		return -2;
	}
	
<<<<<<< HEAD
	int numFrames = argc - 2;
	
	row = SDL_CreateRGBSurface(SDL_SWSURFACE, frame->w*numFrames, frame->h, 
=======
	int numRows = argc - 2;
	std::cout << numRows << std::endl;
	image = SDL_CreateRGBSurface(SDL_SWSURFACE, row->w, row->h*numRows, 
>>>>>>> 22a9e7259a45f3ce263c6e657552aa7c66b55b22
		32, 0xff000000, 0xff0000, 0xff00, 0x00);
		//frame->format->BitsPerPixel, 
		//frame->format->Rmask, frame->format->Gmask, frame->format->Bmask, 
		//frame->format->Amask);
	
<<<<<<< HEAD
	copyToRect(frame, row, 0);
=======
	copyToRect(row, image, 0);
>>>>>>> 22a9e7259a45f3ce263c6e657552aa7c66b55b22
	
	for (int i = 3; i < argc; ++i)
	{
		std::cout << i << std::endl;
<<<<<<< HEAD
		SDL_FreeSurface(frame);
		frame = SDL_LoadBMP(argv[i]);
		if (frame == NULL)
=======
		SDL_FreeSurface(row);
		row = SDL_LoadBMP(argv[i]);
		if (row  == NULL)
>>>>>>> 22a9e7259a45f3ce263c6e657552aa7c66b55b22
		{
			std::cerr << "Error loading bitmap: " << SDL_GetError();
			return -2;
		}
<<<<<<< HEAD
		copyToRect(frame, row, (i-2)*frame->w*row->format->BytesPerPixel);
	}
	
	SDL_SaveBMP (row, argv[1]);
	SDL_FreeSurface(frame);
=======
		copyToRect(row, image, (i-2)*row->h);
	}
	
	SDL_SaveBMP (image, argv[1]);
	SDL_FreeSurface(image);
>>>>>>> 22a9e7259a45f3ce263c6e657552aa7c66b55b22
	SDL_FreeSurface(row);
	return 0;
}
