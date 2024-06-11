//
// Created by Admin on 10/06/2024.
//

#ifndef VIRTUALBAND2_OSCCOMPONENT_H
#define VIRTUALBAND2_OSCCOMPONENT_H

#include <juce_osc/juce_osc.h>


class OscComponent : public juce::OSCReceiver, public juce::OSCReceiver::ListenerWithOSCAddress<juce::OSCReceiver::MessageLoopCallback>
{
public:
  OscComponent();
  ~OscComponent();

  bool connect(int port);
  void disconnect();
  void addListener( const juce::String& address);

  void oscMessageReceived(const juce::OSCMessage &message) override;
private:
  juce::OSCSender oscSender;
};

#endif //VIRTUALBAND2_OSCCOMPONENT_H
