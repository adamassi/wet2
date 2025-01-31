Wet2 - Data Structures Course Assignment

Overview

This repository contains my solution for Wet Assignment 2 in the Data Structures (234218) course at the Technion - Israel Institute of Technology, Winter 2022-23 semester. The assignment focuses on implementing a backend system for tracking teams and players in a World Cup tournament simulation.

Features Implemented

This project implements a data structure that efficiently manages teams, players, and game mechanics based on the given problem statement. The main operations implemented include:

Core Functionalities

Team Management

add_team(int teamId): Adds a new team to the tournament.

remove_team(int teamId): Removes a team along with its players.

buy_team(int buyerId, int boughtId): Merges two teams together.

Player Management

add_player(int playerId, int teamId, const permutation_t &spirit, int gamesPlayed, int ability, int cards, bool goalKeeper): Adds a new player to a team with specific attributes.

num_played_games_for_player(int playerId): Retrieves the number of games a player has participated in.

add_player_cards(int playerId, int cards): Adds yellow/red cards to a player.

get_player_cards(int playerId): Retrieves the total number of cards a player has received.

get_partial_spirit(int playerId): Computes a player's cumulative "spirit" value based on their team.

Game Simulation

play_match(int teamId1, int teamId2): Simulates a match between two teams and determines the winner based on their attributes.

get_team_points(int teamId): Retrieves the points accumulated by a team.

get_ith_pointless_ability(int i): Retrieves the i-th team in order of ability, ignoring accumulated points.

Data Structures Used

To efficiently support the above functionalities, I designed and implemented the following data structures:

Balanced Search Trees (AVL Trees / Red-Black Trees) for efficient player/team lookups and ranking operations.

Hash Maps for quick access to teams and players by their unique identifiers.

Linked Lists for maintaining player order within teams based on the chronological order of their addition.

Performance Considerations

All operations adhere to the required time complexities, ensuring efficiency in both worst-case and amortized scenarios.

Memory management is optimized using careful allocation and deallocation to prevent memory leaks.

The play_match function efficiently determines winners using predefined logic based on abilities, spirits, and previous game results.

Compilation & Execution

The program is implemented in C++ and is designed to compile using the following command:

 g++ -std=c++11 -DNDEBUG -Wall *.cpp

Make sure to place the required main23a1.cpp and wet1util.h files in the project directory before compiling.

Testing

The implementation was tested using sample input files provided with the assignment.

Custom test cases were created to check edge cases, memory allocation, and algorithm efficiency.



Notes & Challenges

Memory Management: Special attention was given to avoiding memory leaks, ensuring proper deallocation of dynamically allocated structures.

Optimizing buy_team Operation: This function needed careful handling of player ordering and merging team attributes, which required maintaining correct time complexities.

Handling Edge Cases: Proper checks were implemented for invalid inputs, including:

Adding duplicate players or teams.

Removing non-existent teams/players.

Playing matches with teams that do not have goalkeepers.

Conclusion

This project was an excellent exercise in advanced data structure design and algorithm implementation. It provided hands-on experience with tree-based data structures, memory management, and performance optimization.

Author: adam assi & zaina drawshy 

Course: Data Structures (234218), Technion - Israel Institute of Technology

