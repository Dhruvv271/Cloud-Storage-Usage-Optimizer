#include "config.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

int HOT_THRESHOLD = 3;
double HOT_STORAGE_COST = 0.1;
double COLD_STORAGE_COST = 0.02;
int PRINT_EVERY_N_EVENTS = 5;

static void require(bool cond, const std::string& msg) {
    if (!cond) throw std::runtime_error("Config error: " + msg);
}

void loadConfig(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open config file: " + path);
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        std::string key;
        std::string value;
        std::stringstream ss(line);

        std::getline(ss, key, '=');
        std::getline(ss, value);

        if (key == "HOT_THRESHOLD") HOT_THRESHOLD = std::stoi(value);
        else if (key == "HOT_STORAGE_COST") HOT_STORAGE_COST = std::stod(value);
        else if (key == "COLD_STORAGE_COST") COLD_STORAGE_COST = std::stod(value);
        else if (key == "PRINT_EVERY_N_EVENTS") PRINT_EVERY_N_EVENTS = std::stoi(value);
        else {
            std::cerr << "Warning: Unknown config key: " << key << "\n";
        }
    }

    // ---- VALIDATION ----
    require(HOT_THRESHOLD > 0, "HOT_THRESHOLD must be > 0");
    require(HOT_STORAGE_COST > 0, "HOT_STORAGE_COST must be > 0");
    require(COLD_STORAGE_COST > 0, "COLD_STORAGE_COST must be > 0");
    require(PRINT_EVERY_N_EVENTS > 0, "PRINT_EVERY_N_EVENTS must be > 0");

    std::cout << "Config loaded successfully ✔️\n";
}
