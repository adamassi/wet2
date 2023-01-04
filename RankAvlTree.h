#ifndef RANKAVLTREE_H
#define RANKAVLTREE_H

#include "GenericNode.h"

using namespace std;

template<class T, class Comp, class Equal>
class RankAvlTree {
public:
    typedef GenericNode<T> *Node;
    int num_of_nodes;
    Node root;
    Comp compare;
    Equal equal;

    RankAvlTree() : num_of_nodes(0), root(nullptr) {};

    RankAvlTree(int num_of_nodes, Node root) : num_of_nodes(num_of_nodes), root(root) {};

    ~RankAvlTree() {
        clear(root);
    }

    RankAvlTree(Node arr[], int size) {
        root = sortedArrayToAVL(arr, 0, size - 1);
        num_of_nodes = size;
    }

    void connectSubTreeToTree(Node originalRoot, Node newRoot) {
        if (originalRoot->father == nullptr) {
            root = newRoot;
        }
        if (originalRoot->isLeftSon()) {
            originalRoot->father->left_son = newRoot;
        }
        if (originalRoot->isRightSon()) {
            originalRoot->father->right_son = newRoot;
        }
        newRoot->father = originalRoot->father;
        originalRoot->father = newRoot;
    }

    void rollLeftLeft(Node currRoot) {
        Node originalRoot = currRoot;
        Node originalRootLeftTree = currRoot->left_son;
        Node originalRootLeftTreeRightSon = originalRootLeftTree->right_son;

        int originalRootExtra = originalRoot->extraGrade;
        int originalRootLeftTreeExtra = originalRootLeftTree->extraGrade;

        connectSubTreeToTree(originalRoot, originalRootLeftTree);
        currRoot = originalRootLeftTree;
        currRoot->right_son = originalRoot;
        currRoot->right_son->left_son = originalRootLeftTreeRightSon;
        if (currRoot->right_son->left_son != nullptr) {
            currRoot->right_son->left_son->father = currRoot->right_son;
            currRoot->right_son->left_son->extraGrade += originalRootLeftTreeExtra;
        }
        currRoot->right_son->extraGrade -= (originalRootLeftTreeExtra + originalRootExtra);
        currRoot->extraGrade += originalRootExtra;

        currRoot->right_son->left_son->updateRanks();
        currRoot->right_son->updateHeight();
        currRoot->right_son->updateRanks();
        currRoot->right_son->updateAllRanksToRoot();
        currRoot->updateHeight();
        currRoot->updateRanks();
        currRoot->updateAllRanksToRoot();
    }

    void rollLeftRight(Node currRoot) {
        Node originalRoot = currRoot;
        Node originalRootLeftTree = currRoot->left_son;
        Node originalRootLeftTreeRightSon = originalRootLeftTree->right_son;
        Node originalRootLeftTreeRightSonLeftSon = originalRootLeftTreeRightSon->left_son;
        Node originalRootLeftTreeRightSonRightSon = originalRootLeftTreeRightSon->right_son;

        int originalRootExtra = originalRoot->extraGrade;
        int originalRootLeftTreeExtra = originalRootLeftTree->extraGrade;
        int originalRootLeftTreeRightSonExtra = originalRootLeftTreeRightSon->extraGrade;

        connectSubTreeToTree(originalRoot, originalRootLeftTreeRightSon);
        currRoot = originalRootLeftTreeRightSon;
        currRoot->right_son = originalRoot;
        currRoot->right_son->left_son = originalRootLeftTreeRightSonRightSon;
        if (currRoot->right_son->left_son != nullptr) {
            currRoot->right_son->left_son->father = currRoot->right_son;
            currRoot->right_son->left_son->extraGrade += (originalRootLeftTreeRightSonExtra +
                                                          originalRootLeftTreeExtra);
        }
        currRoot->left_son = originalRootLeftTree;
        if (currRoot->left_son != nullptr) {
            currRoot->left_son->father = currRoot;
            currRoot->left_son->extraGrade -= (originalRootLeftTreeRightSonExtra +
                                               originalRootLeftTreeExtra);
        }
        currRoot->left_son->right_son = originalRootLeftTreeRightSonLeftSon;
        if (currRoot->left_son->right_son != nullptr) {
            currRoot->left_son->right_son->father = currRoot->left_son;
            currRoot->left_son->right_son->extraGrade += (originalRootLeftTreeRightSonExtra);
        }

        currRoot->right_son->extraGrade -= (originalRootLeftTreeRightSonExtra +
                                            originalRootLeftTreeExtra + originalRootExtra);
        currRoot->extraGrade += (originalRootLeftTreeExtra + originalRootExtra);

        currRoot->right_son->left_son->updateRanks();
        currRoot->right_son->right_son->updateRanks();
        currRoot->left_son->left_son->updateRanks();
        currRoot->left_son->right_son->updateRanks();

        currRoot->right_son->updateHeight();
        currRoot->left_son->updateHeight();
        currRoot->updateHeight();
        currRoot->right_son->updateRanks();
        currRoot->left_son->updateRanks();
        currRoot->updateRanks();
        currRoot->right_son->updateAllRanksToRoot();
        currRoot->left_son->updateAllRanksToRoot();
        currRoot->updateAllRanksToRoot();
    }

    void rollRightRight(Node currRoot) {

        Node originalRoot = currRoot;
        Node originalRootRightTree = currRoot->right_son;
        Node originalRootRightTreeLeftSon = originalRootRightTree->left_son;
        int originalRootExtra = originalRoot->extraGrade;
        int originalRootRightTreeExtra = originalRootRightTree->extraGrade;

        connectSubTreeToTree(originalRoot, originalRootRightTree);
        currRoot = originalRootRightTree;
        currRoot->left_son = originalRoot;
        currRoot->left_son->right_son = originalRootRightTreeLeftSon;
        if (currRoot->left_son->right_son != nullptr) {
            currRoot->left_son->right_son->father = currRoot->left_son;
            currRoot->left_son->right_son->extraGrade += originalRootRightTreeExtra;
        }

        currRoot->left_son->extraGrade -= (originalRootRightTreeExtra + originalRootExtra);
        currRoot->extraGrade += originalRootExtra;

        currRoot->left_son->right_son->updateRanks();
        currRoot->left_son->updateHeight();
        currRoot->updateHeight();
        currRoot->left_son->updateRanks();
        currRoot->updateRanks();
        currRoot->left_son->updateAllRanksToRoot();
        currRoot->updateAllRanksToRoot();
    }

    void rollRightLeft(Node currRoot) {
        Node originalRoot = currRoot;
        Node originalRootRightTree = currRoot->right_son;
        Node originalRootRightTreeLeftSon = originalRootRightTree->left_son;
        Node originalRootRightTreeLeftSonRightSon = originalRootRightTreeLeftSon->right_son;
        Node originalRootRightTreeLeftSonLeftSon = originalRootRightTreeLeftSon->left_son;

        int originalRootExtra = originalRoot->extraGrade;
        int originalRootRightTreeExtra = originalRootRightTree->extraGrade;
        int originalRootRightTreeLeftSonExtra = originalRootRightTreeLeftSon->extraGrade;

        connectSubTreeToTree(originalRoot, originalRootRightTreeLeftSon);
        currRoot = originalRootRightTreeLeftSon;
        currRoot->left_son = originalRoot;
        currRoot->left_son->right_son = originalRootRightTreeLeftSonLeftSon;
        if (currRoot->left_son->right_son != nullptr) {
            currRoot->left_son->right_son->father = currRoot->left_son;
            currRoot->left_son->right_son->extraGrade += (originalRootRightTreeLeftSonExtra +
                                                          originalRootRightTreeExtra);
        }
        currRoot->right_son = originalRootRightTree;
        if (currRoot->right_son) {
            currRoot->right_son->father = currRoot;
            currRoot->right_son->extraGrade -= (originalRootRightTreeLeftSonExtra +
                                                originalRootRightTreeExtra);
        }
        currRoot->right_son->left_son = originalRootRightTreeLeftSonRightSon;
        if (currRoot->right_son->left_son != nullptr) {
            currRoot->right_son->left_son->father = currRoot->right_son;
            currRoot->right_son->left_son->extraGrade += (originalRootRightTreeLeftSonExtra);
        }

        currRoot->left_son->extraGrade -= (originalRootRightTreeLeftSonExtra +
                                           originalRootRightTreeExtra + originalRootExtra);
        currRoot->extraGrade += (originalRootRightTreeExtra + originalRootExtra);

        currRoot->right_son->left_son->updateRanks();
        currRoot->right_son->right_son->updateRanks();
        currRoot->left_son->left_son->updateRanks();
        currRoot->left_son->right_son->updateRanks();

        currRoot->right_son->updateHeight();
        currRoot->left_son->updateHeight();
        currRoot->updateHeight();
        currRoot->right_son->updateRanks();
        currRoot->left_son->updateRanks();
        currRoot->updateRanks();
        currRoot->right_son->updateAllRanksToRoot();
        currRoot->left_son->updateAllRanksToRoot();
        currRoot->updateAllRanksToRoot();
    }


    void roll(Node node) {
        if (node->NodeGetBF() == 2) {
            if (node->nodeGetLeft()->NodeGetBF() >= 0)
                rollLeftLeft(node);
            else if (node->nodeGetLeft()->NodeGetBF() == -1)
                rollLeftRight(node);
        } else if (node->NodeGetBF() == -2) {
            if (node->nodeGetRight()->NodeGetBF() <= 0)
                rollRightRight(node);
            else if (node->nodeGetRight()->NodeGetBF() == 1)
                rollRightLeft(node);
        }
    }


    void clear(Node &root) {
        if (root == nullptr)
            return;
        if (root != nullptr) {
            clear(root->left_son);
            clear(root->right_son);
            delete root;
        }
        root = nullptr;
        num_of_nodes = 0;
    }

    void clear_pointer(Node &root) {
        if (root == nullptr) {
            return;
        }
        if (root->left_son) {
            clear_pointer(root->left_son);
        }
        if (root->right_son) {
            clear_pointer(root->right_son);
        }
        delete root;
        root = nullptr;
        num_of_nodes = 0;
    }

    Node findNode(const T &data) {
        return findNodeHelper(this->root, data);
    }


    Node findNodeHelper(Node node, const T &data) {
        if (node == nullptr)
            return nullptr;
        if (equal(*(node->data), data)) {
            return node;
        } else {
            if (compare(*(node->data), data)) {
                return findNodeHelper(node->right_son, data);
            } else {
                return findNodeHelper(node->left_son, data);
            }
        }
    }

    T *findData(const T &data) {
        if (findNode(data) == nullptr) {
            return nullptr;
        }
        return findNode(data)->data;
    }

    void insert(T data, int grade) {
        if (&data == nullptr) {
            return;
        }

        if (findNode(data) != nullptr) {
            throw NodeAlreadyExists();
        }
        Node node = nullptr;
        node = node->createNode(data);
        node->grade = grade;
        node->sumOfGradesInSubTree = grade;
        node->num_teams_in_sub_tree = 1;
        insertHelper(node, root, 0);
        num_of_nodes++;
    }

    void insertHelper(Node nodeToAdd, Node currRoot, int extra) {
        //the tree is empty
        if (currRoot == nullptr) {
            nodeToAdd->father = nullptr;
            root = nodeToAdd;
            root->height = 0;
            return;
        }

        //add the node to the left sub-tree if data is smaller
        //returns true if the first is smaller
        if (compare(*(nodeToAdd->data), *(currRoot->data))) {
            extra += currRoot->extraGrade;
            if (currRoot->left_son != nullptr) {
                insertHelper(nodeToAdd, currRoot->left_son, extra);
            } else {
                currRoot->left_son = nodeToAdd;
                nodeToAdd->father = currRoot;
                nodeToAdd->grade -= extra;
                nodeToAdd->sumOfGradesInSubTree -= extra;
                currRoot->updateRanks();
                currRoot->updateAllRanksToRoot();
            }
        }

            //add the node to the right sub-tree if data is bigger
        else {
            extra += currRoot->extraGrade;
            if (currRoot->right_son != nullptr) {
                insertHelper(nodeToAdd, currRoot->right_son, extra);
            } else {
                currRoot->right_son = nodeToAdd;
                nodeToAdd->father = currRoot;
                nodeToAdd->grade -= extra;
                nodeToAdd->sumOfGradesInSubTree -= extra;
                currRoot->updateRanks();
                currRoot->updateAllRanksToRoot();
            }
        }
        currRoot->updateHeight();
        currRoot->updateRanks();
        currRoot->updateAllRanksToRoot();
        if (!currRoot->isValidBF()) {
            roll(currRoot);
        }
    }


    void remove(const T &data) {

        if (&data == nullptr || num_of_nodes == 0)
            return;

        // if (num_of_nodes == 0)
        //     return;
        Node node = findNode(data);
        if (node == nullptr) {
            throw NodeDoesntExists();
        }
        removeHelper(node, root);
        num_of_nodes--;
    }


    void removeHelper(Node node_to_delete, Node currNode) {
        int extra = currNode->extraGrade;
        if (equal(*(node_to_delete->data), *(currNode->data))) {
            //if node_to_delete doesnt have sons
            if (currNode->left_son == nullptr && currNode->right_son == nullptr) {
                Node to_remove = currNode;
                currNode = currNode->father;
                if (currNode != nullptr) {
                    currNode->num_teams_in_sub_tree--;
                    currNode->sumOfGradesInSubTree -= (to_remove->grade + to_remove->extraGrade + currNode->extraGrade);
                }
                if (to_remove->isLeftSon()) {
                    currNode->left_son = nullptr;
                }
                if (to_remove->isRightSon()) {
                    currNode->right_son = nullptr;
                }
                currNode->updateAllRanksToRoot();
                delete to_remove;
                if (num_of_nodes == 1) {
                    this->root = nullptr;
                }
            }

                //if NODE_TO_DELETE has only left son
            else if (currNode->left_son && currNode->right_son == nullptr) {
                Node left = currNode->left_son;
                delete currNode->data;
                currNode->data = new T(*(left->data));
                currNode->num_teams_in_sub_tree = left->num_teams_in_sub_tree;
                currNode->sumOfGradesInSubTree = left->sumOfGradesInSubTree;
                currNode->grade = left->grade;
                currNode->extraGrade = left->extraGrade + extra;
                currNode->sumOfGradesInSubTree += (extra * left->num_teams_in_sub_tree);
                currNode->left_son = left->left_son;
                currNode->right_son = left->right_son;
                currNode->left_son->updateAllRanksToRoot();
                currNode->right_son->updateAllRanksToRoot();
                delete left;
            }

                //if node_to_delete has only right son
            else if (currNode->left_son == nullptr && currNode->right_son) {
                Node right = currNode->right_son;
                delete currNode->data;
                currNode->data = new T(*(right->data));
                currNode->num_teams_in_sub_tree = right->num_teams_in_sub_tree;
                currNode->sumOfGradesInSubTree = right->sumOfGradesInSubTree;
                currNode->grade = right->grade;
                currNode->extraGrade = right->extraGrade + extra;
                currNode->sumOfGradesInSubTree += (extra * right->num_teams_in_sub_tree);
                currNode->left_son = right->left_son;
                currNode->right_son = right->right_son;
                currNode->left_son->updateAllRanksToRoot();
                currNode->right_son->updateAllRanksToRoot();
                delete right;
            }

                //if node_to_delete has left and right son
            else {
                Node min_node = getMinNode(currNode->right_son);
                int temp_extra = getExtraSumToMinNode(currNode->right_son, 0);
                delete currNode->data;
                currNode->data = new T(*(min_node->data));

                currNode->grade = (temp_extra + min_node->grade);
                removeHelper(min_node, currNode->right_son);
            }
        }
     else if (compare(*(node_to_delete->data), *(currNode->data))) {

            removeHelper(node_to_delete, currNode->left_son);
        } else {
            removeHelper(node_to_delete, currNode->right_son);
        }
        if (num_of_nodes - 1 != 0) {
            currNode->updateHeight();
            currNode->updateRanks();
            currNode->updateAllRanksToRoot();
            if (!currNode->isValidBF()) {
                roll(currNode);
            }
        }
    }

    Node getMinNode(Node node) {
        if (node == nullptr) {
            return nullptr;
        }
        if (node->left_son == nullptr) {
            return node;
        }
        return getMinNode(node->left_son);
    }

    int getExtraSumToMinNode(Node node, int sum) {
        if (node == nullptr) {
            return sum;
        }
        sum += node->extraGrade;
        if (node->left_son == nullptr) {
            return sum;
        }
        return getExtraSumToMinNode(node->left_son, sum);
    }


    void storeInOrderToArray(Node *inorder) {
        int i = 0;
        storeInorderNodes(root, inorder, &i);
    }

    void storeInorderNodes(Node node, Node *inorder, int *index) {
        if (node == nullptr)
            return;
        storeInorderNodes(node->left_son, inorder, index);
        inorder[*index] = new GenericNode<T>(*node);
        (*index)++;
        storeInorderNodes(node->right_son, inorder, index);
    }

    void storeInOrderToArray(T inorder[]) {
        int i = 0;
        storeInorderNodes(root, inorder, &i);
    }

    void storeInorderNodes(Node node, T inorder[], int *index) {
        if (node == nullptr)
            return;
        storeInorderNodes(node->left_son, inorder, index);
        inorder[*index] = *(node->data);
        (*index)++;
        storeInorderNodes(node->right_son, inorder, index);
    }


    Node sortedArrayToAVL(Node arr[], int start, int end) {
        if (start > end) {
            return nullptr;
        }

        int mid = (start + end) / 2;
        Node node = arr[mid];

        node->father = nullptr;
        node->left_son = sortedArrayToAVL(arr, start, mid - 1);
        node->right_son = sortedArrayToAVL(arr, mid + 1, end);
        if (node->left_son != nullptr)
            node->left_son->father = node;
        if (node->right_son != nullptr)
            node->right_son->father = node;
        node->updateHeight();
        node->updateRanks();
        return node;
    }

    void setAllExtrasToZero(Node curr,int extra) {
        if (curr== nullptr)
            return;
        extra+=curr->extraGrade;
        curr->grade+=extra;

        setAllExtrasToZero(curr->left_son,extra);

        extra-=curr->extraGrade;
        setAllExtrasToZero(curr->right_son,extra);
    }


    void addExtraToAllUnder(Node curr, Node toFind, int extra) {
        if (toFind == nullptr) {
            return;
        }
        int lastTurnIsRight = 0;
        while (curr != nullptr) {
            if (compare(*(curr->data), *(toFind->data))) {
                if (lastTurnIsRight == 0) {
                    curr->extraGrade += extra;
                    curr->tempExtra = extra;
                }
                lastTurnIsRight = 1;
                curr = curr->right_son;
            } else if (compare(*(toFind->data), *(curr->data))) {
                if (lastTurnIsRight == 1) {
                    curr->extraGrade -= extra;
                    curr->tempExtra = (0 - extra);
                }
                lastTurnIsRight = 0;
                curr = curr->left_son;
            } else {
                if (lastTurnIsRight == 0) {
                    curr->extraGrade += extra;
                    curr->tempExtra = extra;
                }
                if (curr->right_son != nullptr) {
                    curr->right_son->extraGrade -= extra;
                    curr->right_son->tempExtra = (0 - extra);
                }
                break;
            }
        }
    }

    void fixSumGradesToRoot(Node curr) {
        if (curr == nullptr) {
            return;
        }
        int sum = 0;
        if (curr->right_son != nullptr) {
            curr->right_son->sumOfGradesInSubTree += (curr->right_son->tempExtra * curr->right_son->num_teams_in_sub_tree);
            sum += (curr->right_son->tempExtra * curr->right_son->num_teams_in_sub_tree);
            curr->right_son->tempExtra = 0;
        }

        while (curr != nullptr) {
            curr->sumOfGradesInSubTree += (curr->tempExtra * curr->num_teams_in_sub_tree) + sum;
            sum += curr->tempExtra * curr->num_teams_in_sub_tree;
            curr->tempExtra = 0;
            curr = (curr->father);
        }
    }

    long long sumOfGrades(Node node, const T &data) {
        long long sum = 0;
        if (data == nullptr) {
            return sum;
        }
        int extraSum = 0;
        while (node != nullptr) {
            extraSum += node->extraGrade;
            if (equal(*(node->data), data)) {
                break;
            }
            if (compare(*(node->data), data)) {
                if (node->left_son) {
                    sum += node->left_son->sumOfGradesInSubTree + node->left_son->num_teams_in_sub_tree * extraSum;
                }
                sum += (node->grade + extraSum);
                node = node->right_son;
            } else {
                node = node->left_son;
            }
        }
        if (node != nullptr && node->left_son != nullptr) {
            sum += (node->grade + extraSum + node->left_son->sumOfGradesInSubTree +
                    node->left_son->num_teams_in_sub_tree * extraSum);
        } else if (node != nullptr) {
            sum += (node->grade + extraSum);
        }
        return sum;
    }

    int numOfEmps(Node node, const T &data) {
        int num = 0;
        if (data == nullptr)
            return num;
        while (node != nullptr) {
            if (equal(*(node->data), data)) {
                break;
            }
            if (compare(*(node->data), data)) {
                if (node->left_son) {
                    num += node->left_son->num_teams_in_sub_tree;

                }
                num++;
                node = node->right_son;
            } else {
                node = node->left_son;
            }
        }
        if (node != nullptr && node->left_son != nullptr) {
            num += (1 + node->left_son->num_teams_in_sub_tree);
        } else if (node != nullptr) {
            num++;
        }
        return num;
    }

    int getExtraToGrade(const T &data){
        if (data == nullptr)
        {
            return 0;
        }
        Node node=root;
        int extra=0;
        while (node != nullptr) {
            if (equal(*(node->data), data)) {
                extra+=node->extraGrade;
                break;
            }
            if (compare(*(node->data), data)) {
                extra+=node->extraGrade;
                node = node->right_son;
            } else {
                extra+=node->extraGrade;
                node = node->left_son;
            }
        }
        return extra;
    }

    Node select(int i, Node curr){
        if(!curr){

             throw NodeDoesntExists();
        }
        // if(curr->GetNumInLeftSubTree()==0 && i==0){
        //         return curr;
        //}
        else if(curr->left_son->GetNumInSubTree()==i-1){
            return curr;
        }
        else if((curr->left_son->GetNumInSubTree())<i-1){
            return select(i-curr->left_son->GetNumInSubTree()-1, curr->right_son);
            // curr=curr->nodeGetRight();
        }
        else if((curr->left_son->GetNumInSubTree())>i-1){
            return select(i, curr->left_son);

            // curr=curr->nodeGetLeft();
        }
        
        return curr;
    }
    
   

//     Node Newselect(Node curr_node,int r){
//         while(curr_node){
//             if((curr_node->left_son) && (curr_node->left_son->GetNumInSubTree())==(r-1)){
//                 return curr_node;
//             }
//             if(curr_node->left_son && (curr_node->left_son->GetNumInSubTree())>(r-1)){
//                 curr_node=curr_node->left_son;
//                 continue;
//             }
//             if((curr_node->left_son) && (curr_node->left_son->GetNumInSubTree())<(r-1)){
//                 //we got here once we know there are right child m>size
//                 r=r-(curr_node->left_son->GetNumInSubTree())-1;///////////////////////////////////////////////////
//                 curr_node=curr_node->right_son;
//                 continue;
//             }
//             if(!curr_node->left_son && curr_node->GetNumInSubTree() == r){
//                 if(curr_node->right_son){
//                     return curr_node->right_son->getMax(curr_node);
//                 }
//                 else{
//                     return curr_node;
//                 }
//             }
//             if(!curr_node->left_son && 1 == r){
//                 return curr_node;
//             }
//             if(!(curr_node->left_son)){
//                 r=r-1;
//                 curr_node=curr_node->right_son;
//             }
//         }
//         return NULL;
//     }





};


#endif