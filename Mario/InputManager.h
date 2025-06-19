#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_

#include "AllHeaderFiles.h"

class INPUTMANAGER {
public:
	INPUTMANAGER() { 
		keyPressed[256] = { false };
	}
	~INPUTMANAGER() {

	}

	bool keyPressed[256];
};

extern INPUTMANAGER inputManager;

#endif // !INPUTMANAGER_H_