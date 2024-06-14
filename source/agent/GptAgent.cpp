//
// Created by Admin on 14/06/2024.
//

#include "GptAgent.h"
#include <iostream>
#include "../openai-cpp/nlohmann/json.hpp"

GptAgent::GptAgent() {
    initialize();
}

GptAgent::~GptAgent() {
    // Any necessary cleanup
}

void GptAgent::initialize() {
//    openai::start(); // Uses the API key provided by the `OPENAI_API_KEY` environment variable
    openai::start("", "EHB"); // Or you can handle it yourself
}
:w

std::string GptAgent::getCompletion(const std::string& prompt) {
    nlohmann::json request = {
        {"model", "text-davinci-003"},
        {"prompt", prompt},
        {"max_tokens", 7},
        {"temperature", 0}
    };

    auto completion = openai::completion().create(request);

    std::cout << "Response is: \n" << completion.dump(2) << "\n";
    return completion["choices"][0]["text"];
}