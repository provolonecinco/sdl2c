#include <SDL2/SDL.h>
#include <stdio.h>
#include "input.h"

void CheckInput() {
	if (keys[SDL_SCANCODE_UP]) {
		if (!input.UP) {input.UP = PRESSED;} 
		else {input.UP = HELD;}
	} else {input.UP = NONE;}

	if (keys[SDL_SCANCODE_DOWN]) {
		if (!input.DOWN) {input.DOWN = PRESSED;} 
		else {input.DOWN = HELD;}
	} else {input.DOWN = NONE;}

	if (keys[SDL_SCANCODE_LEFT]) {
		if (!input.LEFT) {input.LEFT = PRESSED;} 
		else {input.LEFT = HELD;}
	} else {input.LEFT = NONE;}

	if (keys[SDL_SCANCODE_RIGHT]) {
		if (!input.RIGHT) {input.RIGHT = PRESSED;} 
		else {input.RIGHT = HELD;}
	} else {input.RIGHT = NONE;}

	if (keys[SDL_SCANCODE_W]) {
		if (!input.W) {input.W = PRESSED;} 
		else {input.W = HELD;}
	} else {input.W = NONE;}

	if (keys[SDL_SCANCODE_A]) {
		if (!input.A) {input.A = PRESSED;} 
		else {input.A = HELD;}
	} else {input.A = NONE;}

	if (keys[SDL_SCANCODE_S]) {
		if (!input.S) {input.S = PRESSED;} 
		else {input.S = HELD;}
	} else {input.S = NONE;}

	if (keys[SDL_SCANCODE_D]) {
		if (!input.D) {input.D = PRESSED;} 
		else {input.D = HELD;}
	} else {input.D = NONE;}

	if (keys[SDL_SCANCODE_LSHIFT]) {
		if (!input.SHIFT) {input.SHIFT = PRESSED;} 
		else {input.SHIFT = HELD;}
	} else {input.SHIFT = NONE;}
}
