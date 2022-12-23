#include "Game.h"
#include "helper.h"
#include <libdio/display.h>

#include <ctime>
#include <map>
#include <string>
#include <vector>

using namespace std;


const int ROBOT_NUMBER = 7;
int main() {
    //The list and number of robots we want to play with
    const vector<RobotPack> robotPacks = {{"Roboto", 4}, {"BetterR", 1}, {"RandomRoboto", 2}};

    const bool TEST_MODE = true;               //the test mode runs TEST_ROUNDS_NUMBER rounds without display and show live stats
    const unsigned int TEST_ROUNDS_NUMBER = 250;//number of rounds for the test mode

    //Seed randomness and init console
    srand(time(0));
    Display::init();

    //Run test mode with hundreds of rounds or a single round
    if (TEST_MODE) {
        vector<string> winnersList;
        map<string, unsigned> counters;

        //Play the TEST_ROUNDS_NUMBER rounds and store winners
        for (unsigned i = 1; i <= TEST_ROUNDS_NUMBER; i++) {
            Game game(ROBOT_NUMBER);
            string winner = game.start(robotPacks, false);
            if (!winner.empty()) {
                winnersList.push_back(winner);
            }

            //Calculate and display live statistics
            counters.clear();
            for (const auto& pack: robotPacks) {
                counters.insert({pack.className, 0});//set counters to 0 for all robot classes
            }
            //Count the entire list
            for (const auto& currentWinner: winnersList) {
                counters.at(currentWinner)++;
            }
            //Order by descending wins count
            vector<pair<string, unsigned>> orderedCounters = vector<pair<string, unsigned>>(counters.size(), pair<string, unsigned>());
            copy(counters.begin(), counters.end(), orderedCounters.begin());
            sort(orderedCounters.begin(), orderedCounters.end(), [](const pair<string, unsigned> &count1, const pair<string, unsigned> &count2) -> bool {
                return count1.second > count2.second;
            });
            //Finally, display the stats
            Display::DString stats(Display::Color::AQUA);
            stats << "LIVE STATS - Round: " << i << "/" << TEST_ROUNDS_NUMBER << ":\n";
            stats.setColor(Display::Color::ORANGE);
            for (const auto& count: orderedCounters) {
                stats << count.first << " " << count.second << " wins - " << (int) ((double) count.second / i * 100) << "% \n";
            }
            Display::clearScreen();
            stats.print();
        }
    } else {
        //Just turn once
        Game game(ROBOT_NUMBER);
        game.start(robotPacks);
    }
}
