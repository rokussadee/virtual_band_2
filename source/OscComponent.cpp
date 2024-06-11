//
// Created by Admin on 10/06/2024.
//

#include "OscComponent.h"
#include "GlobalState.h"

OscComponent::OscComponent(){}

OscComponent::~OscComponent(){}

bool OscComponent::connect (int port)
{
    bool connectionStatus = juce::OSCReceiver::connect(port);
    if (!connectionStatus)
    {
        DBG ("OSCReceiver not connected to port " << port);
    }
    else
    {
        DBG("OSCReceiver connected. connectionStatus: " << juce::String::toHexString(connectionStatus));
    }
}

void OscComponent::disconnect()
{
    juce::OSCReceiver::disconnect();
}

void OscComponent::addListener (const juce::String& address)
{
    juce::OSCReceiver::addListener(this, address);
}

void OscComponent::oscMessageReceived(const juce::OSCMessage &message)
{
    DBG("OSC message received: " << message.getAddressPattern().toString());

    if (message.getAddressPattern() == juce::OSCAddressPattern("/live/bpm"))
    {
        for (int i = 0; i < message.size(); ++i)
        {
            if (message[i].isInt32())
            {
                DBG("Argument " << i << " is an int32: " << message[i].getInt32());
            }
            else if (message[i].isFloat32())
            {
                DBG("Argument " << i << " is a float32: " << message[i].getFloat32());
            }
            else if (message[i].isString())
            {
                DBG("Argument " << i << " is a string: " << message[i].getString());
            }
            else
            {
                DBG("Argument " << i << " is of unknown type.");
            }
        }
        DBG("Address pattern matched: /live/bpm");
        DBG("message type[0]: " << message[0].getType());
        if (message.size() == 1 && message[0].isFloat32())
        {
            float OSCValue = message[0].getFloat32();
            float bpm = (OSCValue +  0.020429f) / 0.00102145f;
            GlobalState::getInstance().setSongTempo(bpm);
            std::cout << "bpm: " << bpm << " " << std::endl;
        }
        else
        {
            DBG("Message size or type mismatch.");
        }
    }
    else if (message.getAddressPattern() == juce::OSCAddressPattern("/"))
    {
        for (int i = 0; i < message.size(); ++i)
        {
            if (message[i].isInt32())
            {
                DBG("Argument " << i << " is an int32: " << message[i].getInt32());
            }
            else if (message[i].isFloat32())
            {
                DBG("Argument " << i << " is a float32: " << message[i].getFloat32());
            }
            else if (message[i].isString())
            {
                DBG("Argument " << i << " is a string: " << message[i].getString());
            }
            else
            {
                DBG("Argument " << i << " is of unknown type.");
            }
        }
        DBG("Address pattern matched: /");
    }
    else
    {
        DBG("Address pattern did not match: /live/bpm");
    }
}