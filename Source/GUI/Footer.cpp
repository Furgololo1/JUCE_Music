/*
  ==============================================================================

    Footer.cpp
    Created: 26 Jun 2022 11:25:58pm
    Author:  Boss

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Footer.h"

//==============================================================================
Footer::Footer()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

	setSize(500, 50);


	float const smallButtonsSize = 20;

	Image playImage = ImageCache::getFromFile("F:/JuceProjects/JUCE_Music/Images/play.png");

	buttonPlay = new TextButton("Play");
	buttonStop = new TextButton("Stop");
	musicLabel = new Label("Select Song");
	volumeSlider = new Slider();

	imageButtonPlay = new ImageButton();

	addAndMakeVisible(buttonPlay);
	addAndMakeVisible(imageButtonPlay);
	addAndMakeVisible(buttonStop);
	addAndMakeVisible(musicLabel);
	addAndMakeVisible(volumeSlider);

	buttonPlay->setEnabled(false);
	buttonStop->setEnabled(false);

	juce::Rectangle<int> parentBounds = getLocalBounds();

	imageButtonPlay->setBounds( parentBounds.getCentreX() - smallButtonsSize, parentBounds.getCentreY() - smallButtonsSize,
						   smallButtonsSize, smallButtonsSize);
	//buttonStop->setBounds((getWidth() / 2) + 40, getHeight() / 2, 40, 20);
	//musicLabel->setBounds(10, 10, 280, 20);
	//volumeSlider->setBounds(getWidth() / 5, (getHeight() / 3) * 2, 280, 20);

	volumeSlider->setRange(0.f, 100.f, 1);
	volumeSlider->setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);

}

Footer::~Footer()
{
	deleteAllChildren();
}

void Footer::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
 //   g.drawText ("Footer", getLocalBounds(),
          //      juce::Justification::centred, true);   // draw some placeholder text
}

void Footer::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
