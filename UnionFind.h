#ifndef UNIONFIND_H_
#define UNIONFIND_H_

#include "dynamicArr.h"
#include "Team.h"
//#include "wet2util.h"


class PlayerNode {
public:
    int index;
    int player_id;
    int teamId;
    int extra_r;/// for games aplayed
    Team *team;
    int size;
    int extra_spirit;
    PlayerNode *root;
    permutation_t e_p;       

    
    PlayerNode(int index,int player_id, int teamId,int extra_r, Team* team ) : index(index), player_id(player_id),teamId(teamId), extra_r(extra_r), team(team), size(1), extra_spirit(1), root(nullptr),e_p(permutation_t::neutral()) {}
    PlayerNode() :index(-1), player_id(0),teamId(0), extra_r(0),team(nullptr), size(1),extra_spirit(1), root(nullptr),e_p(permutation_t::neutral()) {}
    ~PlayerNode() {
        // delete team;
    }
    PlayerNode& operator=(PlayerNode &other) {
        if (this == &other) {
            return *this;
        }
        this->index = other.index;
        this->player_id = other.player_id;
        this->teamId = other.teamId;
        this->size = other.size;
        this->extra_r = other.extra_r;
        this->team=other.team;
        this->root = other.root;
        return *this;
    }
};

class UnionFind {
public:
    DynArray<PlayerNode*> *players_array;
    
    UnionFind() : players_array(new DynArray<PlayerNode*>(INITIAL_CAPACITY)) {}
        //for (int i = 0; i <INITIAL_CAPACITY ; i++) {
            // *(players_array[i]) = new PlayerNode();
            //players_array[i]->teamId = ();
        //}
    

    void Union(int index1, int index2);
    PlayerNode* MakeSet(int index, PlayerNode* player_to_add){
        PlayerNode* ptr;
       try
       {
            ptr = players_array->insert(player_to_add);
       }
       catch(const std::exception& e)
       {
            //std::cerr << e.what() << '\n';
            throw e;
       }
       return ptr;
    }

    PlayerNode* findPlayerNode(int player_index);

    Team *find(int playerToFindId);

    ~UnionFind() {
        delete players_array;
    }

    //long double getVal(int teamId);
};


#endif