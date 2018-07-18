// SDLtest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#define SDL_MAIN_HANDLED
#include <iostream>
#include <vector>
#include "maze.h"
#include <SDL.h>
#define bx 66
#define by 66
#define gap 66
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

void maze::render() const {
	for (int j = 0; j<MX; j++) {
		if (cells[0][j].top == 0) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		}
		else {
			SDL_SetRenderDrawColor(renderer, 175, 175, 225, 0);
		}
		SDL_RenderDrawLine(renderer, bx + j*gap, by, bx + (j + 1)*gap, by);
	}
	for (int i = 0; i<MY; i++) {
		if (cells[i][0].left == 0) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		}
		else {
			SDL_SetRenderDrawColor(renderer, 175, 175, 225, 0);
		} SDL_RenderDrawLine(renderer, bx, by + i*gap, bx, by + (i + 1)*gap);
	}

	for (int i = 0; i<MY; i++) {
		for (int j = 0; j<MX; j++) {
			if (cells[i][j].down == 0) {
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			}
			else {
				SDL_SetRenderDrawColor(renderer, 175, 175, 225, 0);
			} SDL_RenderDrawLine(renderer, bx + j*gap, by + (i + 1)*gap, bx + (j + 1)*gap, by + (i + 1)*gap);
			if (cells[i][j].right == 0) {
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			}
			else {
				SDL_SetRenderDrawColor(renderer, 175, 175, 225, 0);
			} SDL_RenderDrawLine(renderer, bx + (j + 1)*gap, by + i*gap, bx + (j + 1)*gap, by + (i + 1)*gap);
		}
	}
}
void maze::renderroute() const {
	if (route.empty()) {
		return;
	}
	int x1, x2, y1, y2;
	for (auto it = route.begin(); it != (route.end() - 1); it++) {
		y1 = (it->i)*gap + 0.5*gap + by;
		y2 = ((it + 1)->i)*gap + 0.5*gap + by;
		x1 = (it->j)*gap + 0.5*gap + bx;
		x2 = ((it + 1)->j)*gap + 0.5*gap + bx;
		SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
	}
}
void init() {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
	window = SDL_CreateWindow("MAZE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 480, 480, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED || SDL_RENDERER_PRESENTVSYNC);
}
void close() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
int main() {
	maze m;
	m.generate();
	m.find(0, 0);
	init();
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
		"PROMPT", "Click on the screen to create a new maze", NULL);
	SDL_SetRenderDrawColor(renderer, 100, 100, 200, 0);
	SDL_RenderClear(renderer);
	bool quit = false;
	SDL_Event e;
	while (!quit) {
		SDL_SetRenderDrawColor(renderer, 155, 155, 200, 0);
		SDL_RenderClear(renderer);
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT: quit = true;
				break;
			case SDL_MOUSEBUTTONUP:
				m.generate();
				if (m.find(0, 0)) {
					SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
						"result", "Found it.", NULL);
				}
				else {
					SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
						"result", "Cannot find the route.please try more.", NULL);

				}
				break;
			default:
				break;
			}


		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		m.render();
		SDL_SetRenderDrawColor(renderer, 250, 0, 0, 0);
		m.renderroute();
		SDL_RenderPresent(renderer);


	}
	return 0;
}