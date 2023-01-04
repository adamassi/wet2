//
// Created by admin on 24/11/2022.
//

#ifndef WET1_DS_WINTER_Player_H
#define WET1_DS_WINTER_Player_H

#include "GenericNode.h"
#include <stdlib.h>
#include <stdbool.h>
#include "wet2util.h"

class Team;

class Player{
public:  
    int playerId;
    int teamId;
    permutation_t spirit;  
    int gamesPlayed;
    int ability;
    int cards;
    bool goalsKeeper; // 0 = (False)not keeper , 1=(True)keeper
    int index;
    

public:
    Player(int PlayerId, int teamId,permutation_t spirit, int gamesPlayed, int ability, int cards, bool goalKeeper);
    Player(int id) : playerId(id),teamId(0),spirit(permutation_t::neutral()),gamesPlayed(0),ability(0),cards(0),goalsKeeper(false),index(0) {};
    ~Player()=default;
    
    Player()=default;
    Player(const Player&)=default;
    //Player(const Player&); //// here 

    Player& operator=(Player&);
    int getPlayerId()const;
    int getTeamId() const;
    int getCards() const;
    int getGamesPlayed() const;
    int getGoalsKeeper() const;

    void updateTeamId( int team_id);
    void updateCards( int new_cards);
    void updateGamesPlayed( int new_val);

    bool operator==(Player &Player) const;
    bool operator!=(Player &Player) const;
    bool operator<(Player &Player) const;
    bool operator>(Player &Player) const;
    bool operator<=(Player &Player) const;
    bool operator>=(Player &Player) const;
};

class CompPlayersByID {
public:
    bool operator()(Player* p1, Player* p2) const {
        return p1->playerId < p2->playerId;
    }
};
class EqualPlayers {
public:
    bool operator()(Player* p1, Player* p2) const {
        return p1->playerId == p2->playerId;
    }
};
// class CompPlayersByClosest {
// public:
//     bool operator()(Player* p1, Player* p2) const {
//         if(p1->goals== p2->goals){

//             if(p1->cards==p2->cards){
//                 return (p1->playerId < p2->playerId);
//             }
//             return (p1->cards > p2->cards);
//         }
//         return (p1->goals < p2->goals);
//     }
// };





#endif //WET1_DS_WINTER_Player_H
