#pragma once

#include "JuceHeader.h"
#include "Node.h"

#define SLIDER_WIDTH 100
#define SLIDER_HIGHT 30

class AbstractNodeConroller : public Component, public juce::ReferenceCountedObject
{
public:
	explicit AbstractNodeConroller(Node* listener) : id (listener->getId()){}
	~AbstractNodeConroller()
	{
	}

	virtual void resized() override = 0;

	virtual bool operator==(AbstractNodeConroller& other) const
	{
		return this->id == other.id;
	}

	int getId() const
	{
		return id;
	}


protected:
	static void labelSetup(Label* lbl)
	{
		if (lbl != nullptr)
		{
			lbl->setFont(Font(15.00f, Font::plain));
			lbl->setJustificationType(Justification::centred);
			lbl->setEditable(false, false, false);
			lbl->setColour(TextEditor::textColourId, Colours::black);
		}
	}
	//sets up and displays a slider. DOES NOT set range
	void sliderSetup(ScopedPointer<Slider>* slider, const String name, Slider::SliderStyle style, Slider::TextEntryBoxPosition textBoxPosition, SliderListener* listener)
	{
		addAndMakeVisible(*slider = new Slider(style, textBoxPosition));
		(*slider)->setName(name);
		(*slider)->addListener(listener);
	}
	virtual void setComponentBoundsBelow(Component* toSetup, Component* reference) const 
	{
		toSetup->setBounds(reference->getX(), reference->getY() + reference->getHeight() + 5,
			SLIDER_WIDTH, SLIDER_HIGHT);
	}
	virtual void setComponentBoundsRight(Component* toSetup, Component* reference) const
	{
		toSetup->setBounds(reference->getX() + reference->getWidth() + 5, 0, SLIDER_WIDTH, SLIDER_HIGHT);
	}


private:
	int id; //always the same as the corresponing node
};
