#ifndef GENERICNODE_H
#define GENERICNODE_H

#include "exceptions.h"

using namespace std;

template<class T>
class GenericNode {
public:
    T *data;
    GenericNode *father;
    GenericNode *left_son;
    GenericNode *right_son;
    int height, bf;
    int num_teams_in_sub_tree;
    int num_teams_in_left_sub_tree; 
    

    // ======================== we don't need these ======================== //
    //int num_teams_in_sub_tree;    // num of total emps in the sub-tree
    long long sumOfGradesInSubTree; // sum of total grades in the sub-tree
    long long extraGrade;           // for bonus
    int grade;
    long long tempExtra;
    // ===================================================================== //

    


    GenericNode() : data(nullptr), father(nullptr), left_son(nullptr), right_son(nullptr), height(0), bf(0),
                    num_teams_in_sub_tree(0),num_teams_in_left_sub_tree(0), sumOfGradesInSubTree(0), extraGrade(0), tempExtra(0) {}

    GenericNode(const GenericNode &copyNode) {
        data = new T(*(copyNode.data));
        height = copyNode.height;
        left_son = copyNode.left_son;
        right_son = copyNode.right_son;
        father = copyNode.father;
        num_teams_in_sub_tree = copyNode.num_teams_in_sub_tree;
        num_teams_in_left_sub_tree=copyNode.num_teams_in_left_sub_tree;
        sumOfGradesInSubTree = copyNode.sumOfGradesInSubTree;
        grade = copyNode.grade;
        extraGrade = copyNode.extraGrade;
        tempExtra = copyNode.tempExtra;

    }

    ~GenericNode() {
        delete data;
    }

    GenericNode<T> *createNode(T val) {
        GenericNode<T> *node = new GenericNode<T>;
        node->data = new T(val);
        node->height = 0;
        node->left_son = nullptr;
        node->right_son = nullptr;
        node->father = nullptr;
        node->num_teams_in_sub_tree = 0;
        node->num_teams_in_left_sub_tree=0;
        node->sumOfGradesInSubTree = 0;
        node->grade = 0;
        node->extraGrade = 0;
        node->tempExtra = 0;
        return node;
    }

    GenericNode &operator=(const GenericNode &node) {
        if (this == &node) {
            return *this;
        }
        data = node.data;
        height = node.height;
        left_son = node.left_son;
        right_son = node.right_son;
        father = node.father;
        num_teams_in_sub_tree = node.num_teams_in_sub_tree;
        num_teams_in_left_sub_tree=node.num_teams_in_left_sub_tree;
        sumOfGradesInSubTree = node.sumOfGradesInSubTree;
        extraGrade = node.extraGrade;
        grade = node.grade;
        extraGrade = node.extraGrade;
        tempExtra = node.tempExtra;
        return *this;
    }

    bool operator==(const T &data1) {
        return data == data1;
    }

    bool operator!=(const T &data1) {
        return data == data1;
    }

    bool operator>(const T &data1) {
        return data > data1;
    }

    void updateHeight() {
        if (this == nullptr) {
            return;
        }
        int rightH, leftH;
        // calc right son height
        if (this->right_son == nullptr) {
            rightH = -1;
        } else {
            rightH = right_son->height;
        }
        // calc left son height
        if (this->left_son == nullptr) {
            leftH = -1;
        } else {
            leftH = left_son->height;
        }
        // updates the height
        if (rightH > leftH) {
            this->height = rightH + 1;
        } else {
            this->height = leftH + 1;
        }
    }

    void updateAllRanksToRoot() {
        /* if (this == nullptr) {
             return;
         }*/
        GenericNode<T> *curr = this;
        while (curr != nullptr) {
            if (curr->father == nullptr) {
                break;
            }

            // is left son and his father has right son
            if (curr->isLeftSon() && curr->father->right_son) {
                curr->father->num_teams_in_sub_tree =
                        curr->num_teams_in_sub_tree + curr->father->right_son->num_teams_in_sub_tree + 1;
                curr->father->sumOfGradesInSubTree =
                        curr->sumOfGradesInSubTree + curr->father->right_son->sumOfGradesInSubTree +
                        curr->father->grade + curr->father->extraGrade * curr->father->num_teams_in_sub_tree;
                curr->father->num_teams_in_left_sub_tree=curr->num_teams_in_sub_tree;  /// --> I added this       
            }

            // is left son and his father has no right son
            if (curr->isLeftSon() && curr->father->right_son == nullptr) {
                curr->father->num_teams_in_sub_tree = curr->num_teams_in_sub_tree + 1;
                curr->father->sumOfGradesInSubTree =
                        curr->sumOfGradesInSubTree + curr->father->grade +
                        curr->father->extraGrade * curr->father->num_teams_in_sub_tree;
                curr->father->num_teams_in_left_sub_tree=curr->num_teams_in_sub_tree;  /// --> I added this       

            }

            // is right son and his father has left son
            if (curr->isRightSon() && curr->father->left_son) {
                curr->father->num_teams_in_sub_tree =
                        curr->num_teams_in_sub_tree + curr->father->left_son->num_teams_in_sub_tree + 1;
                curr->father->sumOfGradesInSubTree =
                        curr->sumOfGradesInSubTree + curr->father->left_son->sumOfGradesInSubTree +
                        curr->father->grade + curr->father->extraGrade * curr->father->num_teams_in_sub_tree;
                curr->father->num_teams_in_left_sub_tree=curr->father->num_teams_in_sub_tree; // --> I added this       
            }

            // is right son and his father has no left son
            if (curr->isRightSon() && curr->father->left_son == nullptr) {
                curr->father->num_teams_in_sub_tree = curr->num_teams_in_sub_tree + 1;
                curr->father->sumOfGradesInSubTree =
                        curr->sumOfGradesInSubTree + curr->father->grade +
                        curr->father->extraGrade * curr->father->num_teams_in_sub_tree;
                curr->father->num_teams_in_left_sub_tree=0;  /// --> I added this       

            }
            curr = (curr->father);
        }
    }


    void updateRanks() {
        if (this == nullptr) {
            return;
        }
        int leftNumOfEmp = 0, rightNumOfEmp=0;
        if (this->right_son != nullptr) {
            rightNumOfEmp = this->right_son->num_teams_in_sub_tree;
        }

        if (this->left_son != nullptr) {
            leftNumOfEmp = this->left_son->num_teams_in_sub_tree;
        }

        this->num_teams_in_sub_tree = rightNumOfEmp + leftNumOfEmp + 1;
        this->num_teams_in_left_sub_tree = leftNumOfEmp;
        // this->sumOfGradesInSubTree = rightSumGrades + leftSumGrades + grade;
        // if (extraGrade != 0) {
        //     this->sumOfGradesInSubTree += this->num_teams_in_sub_tree * extraGrade;
        // }
    }

    int NodeGetBF() const {
        if (this == nullptr)
            return 0;
        if (this->left_son && this->right_son)
            return (left_son->height - right_son->height);
        if (this->left_son && this->right_son == nullptr)
            return this->left_son->height + 1;
        if (this->left_son == nullptr && this->right_son)
            return -1 - (this->right_son->height);
        return 0;
    }

    GenericNode<T> *nodeGetRight() {
        if (this == nullptr)
            return nullptr;
        return this->right_son;
    }

    GenericNode<T> *nodeGetLeft() {
        if (this == nullptr)
            return nullptr;
        return this->left_son;
    }
    int GetNumInLeftSubTree(){
        if (this == nullptr)
            return 0;
        return this->num_teams_in_left_sub_tree;
    }

    int GetNumInSubTree(){
        if (this == nullptr)
            return 0;
        return this->num_teams_in_sub_tree;
    }
    // int GetNumInSubTreeLeft()(

    // )



    // returns if the balance factor of the node is valid
    bool isValidBF() {
        return (this->NodeGetBF() < 2 && this->NodeGetBF() > -2);
    }

    bool isLeftSon() {
        if (father == nullptr) {
            return false;
        }
        return father->left_son == this;
    }

    bool isRightSon() {
        if (father == nullptr) {
            return false;
        }
        return father->right_son == this;
    }
    GenericNode<T>* getMax(GenericNode<T>* root){
        if(root==nullptr){
            return nullptr;
        }
        if(!root->right_son){
            return root;
        }
        return getMax(root->right_son);
    }
};

#endif // GENERICNODE_H