//
// Created by admin on 24/11/2022.
//

#include "Team.h"

Team::Team(int teamId)
        :teamId(teamId), points(0) , num_players(0), has_goal_keeper(false),num_goals_keepers(0),games_played(0),ability(0),mul_spirit(1), p_in_uf(nullptr),total_spirit(permutation_t::neutral()) {}

bool Team::operator==(const Team &t) const {
    return teamId == t.teamId;
}

bool Team::operator!=(const Team &t) const {
    return !(t == *this);
}

bool Team::operator<(const Team &t) const {
    return teamId < t.teamId;
}

bool Team::operator>(const Team &t) const {
    return t < *this;
}

bool Team::operator<=(const Team &t) const {
    return !(t < *this);
}

bool Team::operator>=(const Team &t) const {
    return !(*this < t);
}


int Team::getTeamId() const {
    return this->teamId;
}
void Team::updateTeamId(int new_id){
    this->teamId=new_id;
}

int Team::getNumPlayers() const {
    return num_players;
}
void Team::updateNumPlayers(int new_num){
    this->num_players=new_num;
}
int Team::getPoints() const{
    return this->points;
}
void Team::updatePoints(int new_points){
    this->points=new_points;
}
bool Team::getHasGoalKeeper()const{
    return this->has_goal_keeper;
}
void Team::updateHasGoalKeeper(bool new_val){
    this->has_goal_keeper=new_val;
}
int Team::getNumGoalsKeepers() const {
    return num_goals_keepers;
}
void Team::updNumGoalsKeepers(int new_num){
    this->num_goals_keepers=new_num;
}
int Team::getGamesPlayed()const{
    return games_played;
}
void Team::updateGamesPlayed(int games){
    games_played=games;
}

// Node<Team*>* Team::getMinNode(Node<Team*>* node) {
//     if (node == NULL) {
//         return NULL;
//     }
//     if (node->getLeftSon() == NULL) {
//         return node;
//     }
//     return getMinNode(node->getLeftSon());
// }
/*void Team::storeMax(const Team &t, int *T_arr, int *index) {
    T_arr[*index]=t.players_goals_sorted->getMax()->playerId;
    *(index)+=1;
}*/

// PlayerNode* Team::getPlayerInUf() const{
//     retrun player_in_uf;
// }

// bool Team::updPlayerInUF(PlayerNode* p){
//     this->player_in_uf=p;
// }