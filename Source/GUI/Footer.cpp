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
}

Footer::Footer(int const sizeX, int const sizeY)
{
	setSize(sizeX, sizeY);

	int playButtonsSize = 25;
	int smallButtonsSize = 20;

	File playImageFile = File::getCurrentWorkingDirectory().getChildFile("F:/JuceProjects/JUCE_Music/Images/play.png");
	File nextImageFile = File::getCurrentWorkingDirectory().getChildFile("F:/JuceProjects/JUCE_Music/Images/next.png");
	File previousImageFile = File::getCurrentWorkingDirectory().getChildFile("F:/JuceProjects/JUCE_Music/Images/previous.png");

	Image playImage = ImageCache::getFromFile(playImageFile);
	Image nextImage = ImageCache::getFromFile(nextImageFile);
	Image prevoiusImage = ImageCache::getFromFile(previousImageFile);

	volumeSlider = std::make_unique<Slider>();
	musicSlider = std::make_unique<Slider>();

	//addAndMakeVisible(volumeSlider.get());
	addAndMakeVisible(musicSlider.get());

	Point<int> coords;
	coords.addXY(sizeX, sizeY);

	iBPlay = CreateImageButton(playImage, Colour(0xFF0193FA), playButtonsSize, coords.getX()/2, coords.getY() / 4);
	iBPrevious = CreateImageButton(prevoiusImage, Colour(0xFF0193FA), smallButtonsSize, (coords.getX() / 2) - smallButtonsSize*2, coords.getY() / 4);
	iBNext = CreateImageButton(nextImage, Colour(0xFF0193FA), smallButtonsSize, (coords.getX()/2) + smallButtonsSize*2, coords.getY() / 4);

	volumeSlider->setBounds(100, 25, 100, 50);
	musicSlider->setBounds(sizeX / 6, sizeY / 2, (sizeX/3)*2, sizeY/4);
	musicSlider->setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);

}

Footer::~Footer()
{
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
}

std::unique_ptr<ImageButton> Footer::CreateImageButton(Image & const img, Colour & const colour, int& size, int x, int y)
{
	std::unique_ptr<ImageButton> btn = std::make_unique<ImageButton>();

	btn->setImages(false, true, true,
		img, 1.0f, Colour(0xFF0193FA),
		img, 0.5f, Colour(0xFF0193FA),
		img, 0.2f, Colour(0xFF0193FA), 1.0f);

	btn->setSize(size, size);
	btn->setCentrePosition(x, y);

	addAndMakeVisible(btn.get());

	return std::move(btn);

}
