#include <SDL.h>
#include <iostream>

void copyToRect (SDL_Surface* source, SDL_Surface* dest, Uint16 x)
{
	SDL_Surface* dst = dest;
	SDL_Surface* src = SDL_ConvertSurface (source, dst->format, SDL_SWSURFACE);
	char* srcData = (char*)src->pixels;	
	char* dstData = (char*)dst->pixels;
	
	dstData += x;
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
	SDL_Surface* frame;
	
	if (argc < 2)
	{
		std::cerr << "Usage: program_name output_file input_file(s)";
		return -1;
	}
	
	frame = SDL_LoadBMP(argv[2]);
	if (frame == NULL)
	{
		std::cerr << "Error loading bitmap: " << SDL_GetError();
		return -2;
	}
	
	int numFrames = argc - 2;
	
	row = SDL_CreateRGBSurface(SDL_SWSURFACE, frame->w*numFrames, frame->h, 
		32, 0xff000000, 0xff0000, 0xff00, 0x00);
		//frame->format->BitsPerPixel, 
		//frame->format->Rmask, frame->format->Gmask, frame->format->Bmask, 
		//frame->format->Amask);
	
	copyToRect(frame, row, 0);
	
	for (int i = 3; i < argc; ++i)
	{
		std::cout << i << std::endl;
		SDL_FreeSurface(frame);
		frame = SDL_LoadBMP(argv[i]);
		if (frame == NULL)
		{
			std::cerr << "Error loading bitmap: " << SDL_GetError();
			return -2;
		}
		copyToRect(frame, row, (i-2)*frame->w*row->format->BytesPerPixel);
	}
	
	SDL_SaveBMP (row, argv[1]);
	SDL_FreeSurface(frame);
	SDL_FreeSurface(row);
	return 0;
}
