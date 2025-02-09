// Copyright (C) 2021 Helen Ginn

#include "AskYesNo.h"
#include "TextButton.h"
#include "Text.h"

AskYesNo::AskYesNo(Scene *scene, std::string text, std::string tag,
                   ButtonResponder *sender) : 
Modal(scene, 0.6, 0.4)
{
	Text *t = new Text(text);
	setCentre(t, 0.5, 0.35);
	addObject(t);

	{
		TextButton *button = new TextButton("No", this);
		button->setReturnTag("no");
		setCentre(button, 0.2, 0.8);
		addObject(button);
	}

	{
		TextButton *button = new TextButton("Yes", this);
		button->setReturnTag("yes");
		setCentre(button, 0.8, 0.8);
		addObject(button);
	}
	
	_sender = sender;
	_tag = tag;

	setDismissible(false);
}

void AskYesNo::buttonPressed(std::string tag, Button *button)
{
	_sender->buttonPressed(tag + "_" + _tag);

	hide();
}


