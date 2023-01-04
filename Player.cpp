//
// Created by admin on 24/11/2022.
//

#include "Player.h"



Player::Player(int playerId, int teamId, permutation_t spirit, int gamesPlayed, int ability, int cards, bool goalKeeper)
        : playerId(playerId), teamId(teamId),spirit(spirit), gamesPlayed(gamesPlayed), ability(ability), cards(cards), goalsKeeper(goalKeeper) {}

int Player::getPlayerId()const{
    return this->playerId;
}
int Player::getCards() const{
    return this->cards;
}

int Player::getGamesPlayed() const{
    return this->gamesPlayed;
}
int Player::getGoalsKeeper() const{
    return this->goalsKeeper;
}
int Player::getTeamId()const{
    return this->teamId;
}
/*
Team* Player::getTeam()const{
    return this->team_ptr;
} 
*/



void Player::updateTeamId( int team_id){
    this->teamId=team_id;
}
void Player::updateCards( int new_cards){
    this->cards+=new_cards;
}

void Player::updateGamesPlayed( int new_val){
    this->gamesPlayed=new_val;
}


bool Player::operator==(Player &player) const{
    return playerId == player.playerId;
}

bool Player::operator!=(Player &player) const{
    return !(*this == player);
}

bool Player::operator<(Player &player) const{
    return playerId < player.playerId;
}

bool Player::operator>(Player &player) const{
    return *this > player;
}

bool Player::operator<=(Player &player) const{
    return !(*this > player);
}

bool Player::operator>=(Player &player) const{
    return !(*this < player);
}
Player& Player::operator=(Player &other) {
        if (this == &other) {
            return *this;
        }
        this->playerId = other.playerId;
        this->teamId = other.teamId;
        this->spirit=other.spirit;
        this->gamesPlayed = other.gamesPlayed;
        this->ability=other.ability;
        this->cards = other.cards;
        this->goalsKeeper = other.goalsKeeper;
        this->index=other.index;
        return *this;
    }
