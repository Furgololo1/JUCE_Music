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
    ~Footer() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

	TextButton* buttonPlay;
	TextButton* buttonStop;
	Slider* volumeSlider;
	Label* musicLabel;

	ImageButton* imageButtonPlay;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Footer)
};
