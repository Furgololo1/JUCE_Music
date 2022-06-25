
#include "MainComponent.h"
#include <memory>

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (300, 300);

    // Some platforms require permissions to open input channels so request that here
    if (RuntimePermissions::isRequired (RuntimePermissions::recordAudio)
        && ! RuntimePermissions::isGranted (RuntimePermissions::recordAudio))
    {
        RuntimePermissions::request (RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (2, 2);
    }

	buttonOpen = new TextButton("Open...");
	buttonPlay = new TextButton("Play");
	buttonStop = new TextButton("Stop");
	musicLabel = new Label("Select Song");
	volumeSlider = new Slider();

	getLookAndFeel().setColour(Slider::thumbColourId, Colour(0xFF339FEB));
	getLookAndFeel().setColour(Slider::trackColourId, Colour(0xFF339FEB));
	getLookAndFeel().setColour(Slider::backgroundColourId, Colour(0x22339FEB));

	addAndMakeVisible(buttonOpen);
	addAndMakeVisible(buttonPlay);
	addAndMakeVisible(buttonStop);
	addAndMakeVisible(musicLabel);
	addAndMakeVisible(volumeSlider);

	buttonPlay->setEnabled(false);
	buttonStop->setEnabled(false);

	buttonOpen->setBounds(10, 10, 280, 20);
	buttonPlay->setBounds(10, 40, 280, 20);
	buttonStop->setBounds(10, 70, 280, 20);
	musicLabel->setBounds(10, 100, 280, 20);
	volumeSlider->setBounds(10, 130, 280, 20);

	volumeSlider->setRange(0.f, 100.f, 1);
	volumeSlider->setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);

	buttonOpen->onClick = [this] { onOpenFile(); };
	buttonPlay->onClick = [this] { onPlayFile(); };
	buttonStop->onClick = [this] { onStopFile(); };
	volumeSlider->onValueChange = [this] { onVolumeChanged(); };

	formatManager.registerBasicFormats();
	transportSource.addChangeListener(this);

	state = Stopped;
	volume = 0.f;

}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
	deleteAllChildren();
    shutdownAudio();

}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // This function will be called when the audio device is started, or when
    // its settings (i.e. sample rate, block size, etc) are changed.

    // You can use this function to initialise any resources you might need,
    // but be careful - it will be called on the audio thread, not the GUI thread.

	transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    // Your audio-processing code goes here!

	if (readerSource.get() == nullptr) {
		bufferToFill.clearActiveBufferRegion();
		return;
	}

	transportSource.getNextAudioBlock(bufferToFill);

	for (auto channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel)
	{
		auto* buffer = bufferToFill.buffer->getWritePointer(channel, bufferToFill.startSample);

		for (auto sample = 0; sample < bufferToFill.numSamples; ++sample)
		{
			buffer[sample] = buffer[sample] * (volume / 100);
		}
	}

}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

	transportSource.releaseResources();
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    // You can add your drawing code here!


}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}

void MainComponent::changeListenerCallback(ChangeBroadcaster * source)
{
	if (source == &transportSource) {
		if (transportSource.isPlaying())
			changeState(Playing);
		else if((state == Stopping) || (state == Playing))
			changeState(Stopped);
		else if (state == Pausing)
			changeState(Paused);
	}
}

void MainComponent::changeState(const TransportState newState)
{
	if (state != newState) {
		state = newState;

		switch (state) {
			case Stopped:
				buttonStop->setEnabled(false);
				buttonPlay->setEnabled(true);
				transportSource.setPosition(0.0f);
			break;

			case Starting:
				buttonPlay->setEnabled(false);
				transportSource.start();
			break;

			case Playing:
				buttonStop->setEnabled(true);
			break;

			case Pausing:
				transportSource.stop();
			break;

			case Paused:
				buttonPlay->setButtonText("Resume");
				buttonStop->setButtonText("Return to zero");
			break;

			case Stopping:
				transportSource.stop();
			break;
		}
	}
}

void MainComponent::onOpenFile()
{
	chooser = std::make_unique<FileChooser>("Select a Wave file to play...", File{}, "*.wav", "*.aif", "*.aiff");
	auto chooserFlags = FileBrowserComponent::openMode | FileBrowserComponent::canSelectFiles;

	chooser->launchAsync(chooserFlags, [this](const FileChooser& fc) 
	{
		auto file = fc.getResult();
		if (file != File{}) {
			auto* reader = formatManager.createReaderFor(file);

			if (reader != nullptr) {
				auto newSource = std::make_unique<AudioFormatReaderSource>(reader, true);
				transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
				musicLabel->setText(file.getFileName(), NotificationType::dontSendNotification);
				buttonPlay->setEnabled(true);
				readerSource.reset(newSource.release());
			}
		}
	});
}

void MainComponent::onPlayFile()
{
	if ((state == Stopped) || (state == Paused)) 
		changeState(Starting);
	else if (state == Playing) 
		changeState(Pausing);
}

void MainComponent::onStopFile()
{
	if(state == Paused)
		changeState(Stopped);
	else
		changeState(Stopping);
}

void MainComponent::onVolumeChanged()
{
	volume = volumeSlider->getValue();
	DBG("volume " << volume);
}

