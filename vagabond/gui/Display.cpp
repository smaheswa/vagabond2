#include "Display.h"
#include "GuiAtom.h"
#include "TextButton.h"
#include <vagabond/core/AtomGroup.h>
#include <vagabond/core/Atom.h>
#include <vagabond/core/AlignmentTool.h>
#include "Window.h"
#include <SDL2/SDL.h>
#include <iostream>

Display::Display(Scene *prev) : Scene(prev)
{
	_guiAtoms = nullptr;
	_atoms = nullptr;
}

Display::~Display()
{
	deleteObjects();
	
	if (_atoms != nullptr)
	{
		delete _atoms;
		_atoms = nullptr;
	}
}

void Display::recalculateAtoms()
{
	AlignmentTool tool(_atoms);
	tool.run();
	_atoms->recalculate();
}

void Display::loadAtoms(AtomGroup *atoms)
{
	if (_guiAtoms != nullptr)
	{
		removeObject(_guiAtoms);
		delete _guiAtoms;
	}
	
	if (_atoms != nullptr)
	{
		delete _atoms;
	}
	
	_atoms = atoms;
	_guiAtoms = new GuiAtom();
	_guiAtoms->watchAtoms(_atoms);
	_guiAtoms->startBackgroundWatch();

	_centre = _guiAtoms->centroid();
	_translation = -_centre;
	_translation.z -= 30;

	updateCamera();

	addObject(_guiAtoms);
	tieButton();
}

void Display::tieButton()
{
	{
		TextButton *button = new TextButton("Tie up with bonds", 
		                                    this);
		button->setReturnTag("recalculate");
		button->resize(0.8);
		setCentre(button, 0.5, 0.9);
		addObject(button);
	}
}

void Display::setup()
{
	
}

void Display::buttonPressed(std::string tag, Button *button)
{
	if (tag == "back")
	{
		_atoms->cancelRefinement();
	}

	Scene::buttonPressed(tag, button);

	if (tag == "recalculate")
	{
		recalculateAtoms();
		removeObject(button);

		{
			TextButton *replace = new TextButton("Refine model positions", 
			                                    this);
			replace->setReturnTag("refine_positions");
			replace->resize(0.8);
			setCentre(replace, 0.5, 0.9);
			addObject(replace);
		}
	}
	else if (tag == "refine_positions")
	{
		_atoms->refinePositions();
	}
}

void Display::interpretMouseButton(SDL_MouseButtonEvent button, bool dir)
{
	if (button.button == SDL_BUTTON_LEFT)
	{
		_left = dir;
	}
	if (button.button == SDL_BUTTON_RIGHT)
	{
#ifdef __EMSCRIPTEN__
		if (_controlPressed)
		{
			_left = dir;
		}
		else
		{
			_right = dir;
		}
#else
		_right = dir;
#endif
	}
}

void Display::updateSpinMatrix()
{
	double x = _lastX;
	double y = _lastY;
	
	convertCoords(&x, &y);
	glm::vec3 pos = glm::vec3(x, y, 0);
	
	glm::vec3 c = _centre;

	glm::vec4 tmp = _proj * glm::vec4(c, 1.);
	tmp /= tmp[3];

	glm::vec3 projAxis = glm::normalize(pos - glm::vec3(tmp));

	glm::vec3 rotAxis = glm::normalize(glm::cross(projAxis, glm::vec3(1, 0, 0)));
	_spin[0] = rotAxis;
	_spin[1] = glm::cross(rotAxis, projAxis);
	_spin[2] = projAxis;
	
//	_spin = glm::transpose(_spin);

}

void Display::mousePressEvent(double x, double y, SDL_MouseButtonEvent button)
{
	Scene::mousePressEvent(x, y, button);

	interpretMouseButton(button, true);

	_lastX = x;
	_lastY = y;

	updateSpinMatrix();
}

void Display::mouseMoveEvent(double x, double y)
{
	Scene::mouseMoveEvent(x, y);

	if (_left && !_shiftPressed && !_controlPressed)
	{
		double dx = x - _lastX;
		double dy = y - _lastY;
		
		dx /= width();
		dy /= height();
		
		glm::vec4 start = _proj * glm::vec4(0, 0, -1, 1);
		glm::vec4 end = _proj * glm::vec4(dx, -dy, -1, 1);
		
		glm::vec3 move = start - end;
		move.z = 0;
		move = _spin * move;

		const float scale = 5;
		_camAlpha = move.x * scale;
		_camBeta =  move.y * scale;
		_camGamma = -move.z * scale;
		_camAlpha *= Window::aspect();
		
		updateCamera();
		updateSpinMatrix();
	}

	if (_left && !_shiftPressed && _controlPressed)
	{
		double dx = x - _lastX;
		double dy = y - _lastY;

		_translation.x = dx / 50;
		_translation.y = -dy / 50;
		
		updateCamera();
	}

	if (_right && !_shiftPressed && !_controlPressed)
	{
		double dy = y - _lastY;

		_translation.z = dy / 2;
		
		updateCamera();
	}

	_lastX = x;
	_lastY = y;
}

void Display::mouseReleaseEvent(double x, double y, SDL_MouseButtonEvent button)
{
	Scene::mouseReleaseEvent(x, y, button);
	interpretMouseButton(button, false);
}

void Display::interpretControlKey(SDL_Keycode pressed, bool dir)
{
	if (pressed == SDLK_LCTRL)
	{
		_controlPressed = dir;
	}

	if (pressed == SDLK_LSHIFT)
	{
		_shiftPressed = dir;
	}
}

void Display::keyPressEvent(SDL_Keycode pressed)
{
	interpretControlKey(pressed, true);
}

void Display::keyReleaseEvent(SDL_Keycode pressed)
{
	interpretControlKey(pressed, false);
}

