//
// Created by Admin on 14/06/2024.
//

#ifndef VIRTUALBAND2_GPTAGENT_H
#define VIRTUALBAND2_GPTAGENT_H

#include <string>
#include "../openai-cpp/openai.hpp"

class GptAgent {
public:
    GptAgent();
    ~GptAgent();

    static std::string getCompletion(const std::string& prompt);

private:
    void initialize();

};

#endif // GPT_AGENT_H