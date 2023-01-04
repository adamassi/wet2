#include "UnionFind.h"

PlayerNode *UnionFind::findPlayerNode(int player_index) {
    /// updating extra_r isn't right - nor the ability one (add it and check both)
    
    PlayerNode *currPlayer = players_array->array[player_index]; //  I think without -1 - check !!!!!!!  
    if (currPlayer == nullptr) {
        return nullptr;
    }
    int extra_val = 0;
    int ex_strength=1;
    permutation_t e= permutation_t::neutral();
    PlayerNode *p = currPlayer;
    while (currPlayer->root != nullptr) {
        extra_val += currPlayer->extra_r; // sum of extra_r from curr to root (not included)
        ex_strength=ex_strength*currPlayer->extra_spirit;
        if(currPlayer->root->root != nullptr){
            e=e*currPlayer->e_p;
        }
        currPlayer = currPlayer->root;
    }    
    int t_id=currPlayer->teamId;
    PlayerNode *father = currPlayer;
    currPlayer = p;
    PlayerNode *temp = p->root;
    int temp_val = 0;
    if(temp!=nullptr){
        while (temp->root) {
        // int x = currPlayer->extra_r;
            temp_val+=currPlayer->extra_r;
            currPlayer->extra_r = (extra_val); // x was temp_val - I changed it
            currPlayer->extra_spirit=ex_strength;
        //    temp_val += x;
            //if(currPlayer->root->root != nullptr){
                currPlayer->e_p=e*currPlayer->e_p;
            //}
            currPlayer->root = father;
            currPlayer->teamId=t_id;
            //currPlayer = temp;
            temp = currPlayer->root;
            
        }
    }

    return father;
}

Team *UnionFind::find(int player_index) {
    if (findPlayerNode(player_index) == nullptr) {
        return nullptr;
    }
    return findPlayerNode(player_index)->team;
}


// long double UnionFind::getVal(int TeamId) {
//     PlayerNode *currPlayer = teamsArray[TeamId - 1];
//     long double val = currPlayer->team->points;
//     while (currPlayer != nullptr) {
//         val += currPlayer->extraVal;
//         currPlayer = currPlayer->root;
//     }
//     return val;
// }


// static GenericNode<Player *> **
// mergeArrays(GenericNode<Player *> *arr1[], GenericNode<Player *> *arr2[], int m, int n) {
//     GenericNode<Player *> **mergedArr = new GenericNode<Player *> *[m + n];
//     int i = 0, j = 0, k = 0;
//     CompPlayersByID Team;
//     while (i < m && j < n) {
//         if (Team(*arr1[i]->data, *arr2[j]->data)) {
//             mergedArr[k] = arr1[i];
//             i++;
//         } else {
//             mergedArr[k] = arr2[j];
//             j++;
//         }
//         k++;
//     }
//     // if m>n
//     while (i < m) {
//         mergedArr[k] = arr1[i];
//         i++;
//         k++;
//     }
//     // if n<m
//     while (j < n) {
//         mergedArr[k] = arr2[j];
//         j++;
//         k++;
//     }
//     return mergedArr;
// }

// LinkedList<Player *> *storeHashInList(HashTable<Player *> *empsHash, int extra) {
//     LinkedList<Player *> *list = new LinkedList<Player *>;
//     for (unsigned int i = 0; i < empsHash->capacity; i++) {
//         Node<Player *> *currNode = empsHash->table[i].getHead();
//         for (int j = 0; j < empsHash->table[i].size(); j++) {
//             currNode->data->grade += extra;
//             list->insert(currNode->data);
//             currNode = currNode->next;
//         }
//     }
//     return list;
// }

// HashTable<Player *> *mergeLists(LinkedList<Player *> *first, LinkedList<Player *> *sec) {
//     Node<Player *> *curr1 = sec->getHead();
//     for (int i = 0; i < sec->size(); i++) {
//         first->insert(curr1->data);
//         curr1 = curr1->next;
//     }
//     HashTable<Player *> *merged = new HashTable<Player *>();
//     Node<Player *> *curr2 = first->getHead();
//     for (int i = 0; i < first->size(); i++) {
//         merged->Insert(curr2->data->PlayerId, (curr2->data));
//         curr2 = curr2->next;
//     }
//     return merged;
// }


void UnionFind::Union(int index1, int index2) {
    Team* buy_team=find(index1);
    int size1 = buy_team->getNumPlayers();
    int mul1=buy_team->mul_spirit;
    PlayerNode* root1=findPlayerNode(index1);

    Team* bought_team=find(index2);
    int size2 = bought_team->getNumPlayers();
    // int mul2=bought_team->mul_spirit;
    PlayerNode* root2=findPlayerNode(index2);
    if(root1->player_id==root2->player_id){
        return;
    }
    if(size1 < size2){
        root2->size+=root1->size;
        root1->extra_r-=root2->extra_r;
        root1->extra_spirit=(1/mul1);
        root1->e_p=(buy_team->total_spirit).inv();
        root2->extra_spirit=( root2->extra_spirit)*(mul1);
        root2->e_p=( root2->e_p)*(buy_team->total_spirit);
        root1->root=root2;
        buy_team->p_in_uf=root2;
        root2->team=buy_team;
        root2->teamId=buy_team->teamId;
    }
    else{
        root1->size+=root2->size;
        root2->extra_r-=root1->extra_r;
        root2->extra_spirit=(root2->extra_spirit)*(mul1);
        root2->e_p=( root2->e_p)*(buy_team->total_spirit);
        root2->root=root1;
    }
}

    