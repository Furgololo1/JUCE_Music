#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/

enum TransportState
{
	Stopped,
	Starting,
	Pausing,
	Paused,
	Playing,
	Stopping
};

class MainComponent  : public AudioAppComponent,
					   public ChangeListener
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (Graphics& g) override;
    void resized() override;

protected:

	void changeListenerCallback(ChangeBroadcaster* source) override;

private:
    //==============================================================================
    // Your private member variables go here...

	void changeState(const TransportState newState);

	void onOpenFile();
	void onPlayFile();
	void onStopFile();
	void onVolumeChanged();

	TextButton* buttonOpen;
	TextButton* buttonPlay;
	TextButton* buttonStop;

	Slider* volumeSlider;

	Label* musicLabel;
	
	AudioFormatManager formatManager;
	std::unique_ptr<AudioFormatReaderSource> readerSource;
	AudioTransportSource transportSource;
	TransportState state;
	std::unique_ptr<FileChooser> chooser;

	Random random;

	float volume;


	//LookAndFeel lookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
