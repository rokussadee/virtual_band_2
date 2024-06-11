//
// Created by Admin on 11/06/2024.
//

#ifndef VIRTUALBAND2_GLOBALSTATE_H
#define VIRTUALBAND2_GLOBALSTATE_H

class GlobalState
{
public:
    static GlobalState& getInstance()
    {
        static GlobalState instance;
        return instance;
    }

    void setSongTempo(float bpm)
    {
        songTempo = bpm;
    }

    float getSongTempo()
    {
        return songTempo;
    }

private:
    GlobalState(): songTempo(120.0f) {}
    ~GlobalState() {}

    GlobalState(const GlobalState&) = delete;
    GlobalState& operator=(const GlobalState&) = delete;
    float songTempo;
};

#endif //VIRTUALBAND2_GLOBALSTATE_H
