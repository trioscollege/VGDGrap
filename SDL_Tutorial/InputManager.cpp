#include "InputManager.hpp"

InputManager * InputManager::sInstance = nullptr;

InputManager * InputManager::Instance() {
	if (sInstance == nullptr) {
		sInstance = new InputManager();
	}
	return sInstance;
}

void InputManager::Release() {
	delete sInstance;
	sInstance = nullptr;
}
 
bool InputManager::KeyDown(SDL_Scancode scancode) {
	return mKeyboardStates[scancode];
}

void InputManager::Update() {
	mKeyboardStates = SDL_GetKeyboardState(nullptr);
}

InputManager::InputManager() { }

InputManager::~InputManager() { }
