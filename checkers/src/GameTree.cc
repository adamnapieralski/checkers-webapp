/**
 * @file GameTree.h
 * @brief Source file for GameTree class, representing the game tree for minimax alfa beta algorithm.
 * 
 * @author Patrycja Cieplicka
 * @author Adam Napieralski
 */

#include "GameTree.h"
#include "Board.h"

GameTree::GameTree(Move m, Board b){
    root_ = std::make_shared<TNode>(b,m);
    currentHead_ = root_;
}

void GameTree::addChildren(Move m, Board b){
    currentHead_.lock()->children_.push_back(std::make_shared<TNode>(b,m));
    currentHead_ = currentHead_.lock() -> children_.back();
}

void GameTree::changeCurrentHeadToParent(){
    currentHead_ = currentHead_.lock()->parent_;
}


