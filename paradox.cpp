/**
 * @file paradox.cpp
 * @author Garritt Baker
 * @date 2024-12-02
 * @brief Monty Hall Paradox Simulator
 * 
 * Runs the Monty Hall Paradox problem with enough iterations to show the difference in staying or switching doors.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
using namespace std;

// Function to simulate a single round of Monty Hall where the player always switches
bool monty_hall_always_switch() {
    // Randomly assign car and goats behind doors
    vector<string> doors = {"goat", "goat", "car"};
    shuffle(doors.begin(), doors.end(), mt19937(random_device()()));

    // User selects a random door
    int user_choice = rand() % 3;

    // Host reveals a door with a goat that is not the user's choice
    int host_choice;
    do {
        host_choice = rand() % 3;
    } while (host_choice == user_choice || doors[host_choice] == "car");

    // User always switches
    int final_choice = 3 - user_choice - host_choice;

    // Return true if the user finds the car, false otherwise
    return doors[final_choice] == "car";
}

// Function to simulate a single round of Monty Hall where the player always stays
bool monty_hall_always_stay() {
    // Randomly assign car and goats behind doors
    vector<string> doors = {"goat", "goat", "car"};
    shuffle(doors.begin(), doors.end(), mt19937(random_device()()));

    // User selects a random door
    int user_choice = rand() % 3;

    // Host reveals a door with a goat that is not the user's choice
    int host_choice;
    do {
        host_choice = rand() % 3;
    } while (host_choice == user_choice || doors[host_choice] == "car");

    // User always stays (final choice is the initial choice)
    int final_choice = user_choice;

    // Return true if the user finds the car, false otherwise
    return doors[final_choice] == "car";
}

// Function to simulate the Monty Hall problem with a given strategy function
void simulate_strategy(bool (*strategy_function)(), int num_iterations) {
    int wins = 0;

    for (int i = 0; i < num_iterations; ++i) {
        if (strategy_function()) {
            ++wins;
        }
    }

    double win_ratio = static_cast<double>(wins) / num_iterations;
    cout << "Total Simulations: " << num_iterations << endl;
    cout << "Times Won: " << wins << endl;
    cout << "Win Ratio: " << win_ratio * 100 << "%" << endl;
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr))); // Seed the random number generator

    int num_iterations = 100000;

    cout << "Simulation when always switching:" << endl;
    simulate_strategy(monty_hall_always_switch, num_iterations);

    cout << "Simulation when always staying:" << endl;
    simulate_strategy(monty_hall_always_stay, num_iterations);

    return 0;
}
