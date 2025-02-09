// Copyright (C) 2021 Helen Ginn

#ifndef __practical__Button__
#define __practical__Button__

#include "Text.h"

class ButtonResponder;

class Button : virtual public Box
{
public:
	Button(ButtonResponder *sender = NULL);
	
	void setSender(ButtonResponder *sender)
	{
		_sender = sender;
	}

	void setReturnTag(std::string tag)
	{
		_tag = tag;
	}
	
	std::string tag()
	{
		return _tag;
	}
	
	/** Renders button unable to be highlighted and suppresses action when
	 * pressed */
	void setInert(bool inert)
	{
		_inert = inert;
	}

	virtual void unMouseOver();
	virtual bool mouseOver();

	virtual void click();

	void setTickable(bool tick)
	{
		_tickable = tick;
	}
protected:
	bool _inert;
	bool _tickable;
	ButtonResponder *_sender;
private:
	std::string _tag;

};

#endif
