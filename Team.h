//
// Created by admin on 24/11/2022.
//

#ifndef WET1_DS_WINTER_TEAM_H
#define WET1_DS_WINTER_TEAM_H

#include "Player.h"
#include "linkedList.h"
#include "wet2util.h"
class PlayerNode;

class Team{
public:    
   friend class PlayerNode;
    int teamId;
    int points;
    int num_players;
    bool has_goal_keeper;
    int num_goals_keepers;
    int games_played;
    int ability;
    int mul_spirit;
    PlayerNode *p_in_uf;
    permutation_t total_spirit;
    
 //LinkedList<Player*> players; askkkkkkkkkkkkkkkkkk

    
public:
friend class Player;
    
    Team(int teamId);
    Team()=default;
    ~Team()=default;
    Team(const Team&)=delete; // =delete? 

    Team& operator=(const Team&) = default; //=delete? 
    //static void storeMax(const Team& t, int* T_arr , int* index);
    bool operator==(const Team &t) const;
    bool operator!=(const Team &t) const;
    bool operator<(const Team &t) const;
    bool operator>(const Team &t) const;
    bool operator<=(const Team &t) const;
    bool operator>=(const Team &t) const;
    int getTeamId()const;
    void updateTeamId(int new_id);
    int getNumPlayers() const;
    void updateNumPlayers(int new_num);
    int getPoints() const;
    void updatePoints(int new_points);
    bool getHasGoalKeeper()const;
    void updateHasGoalKeeper(bool new_val);
    int getGamesPlayed()const;
    void updateGamesPlayed(int games);
    int getNumGoalsKeepers() const;
    void updNumGoalsKeepers(int new_num) ;
    // PlayerNode* getPlayerInUf() const;
    // bool updPlayerInUF(PlayerNode* p);

    
};
class CompTeamsByID {
public:
    bool operator()(Team *t1, Team *t2) const {
        return t1->getTeamId() < t2->getTeamId();
    }
};
class EqualTeams {
public:
    bool operator()(Team *t1, Team *t2) const {
        return t1->teamId == t2->teamId;
    }
};
class CompTeamsByAbility{
    public:
    bool operator()(Team *t1, Team *t2) const {
        if(t1->ability == t2->ability) return t1->getTeamId() < t2->getTeamId();
        return t1->ability < t2->ability;
    }
};






#endif //WET1_DS_WINTER_TEAM_H
