/*
  ==============================================================================

    Footer.h
    Created: 26 Jun 2022 11:25:58pm
    Author:  Boss

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/


class Footer  : public juce::Component
{
public:
    Footer();
	Footer(int const sizeX, int const sizeY);
	~Footer() override;

    void paint (juce::Graphics&) override;
    void resized() override;


private:

	std::unique_ptr<ImageButton> CreateImageButton(Image& const img, Colour& const colour, int& size, int x, int y);

	std::unique_ptr< Label > musicLabel;

	std::unique_ptr < ImageButton > iBPlay;
	std::unique_ptr < ImageButton > iBNext;
	std::unique_ptr < ImageButton > iBPrevious;

	std::unique_ptr< Slider > volumeSlider;
	std::unique_ptr< Slider > musicSlider;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Footer)
};
