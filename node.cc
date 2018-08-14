// Copyright 2018 <Author>

#include "node.h"

Node::Node(char data) {
  data_ = data;
  right_ = nullptr;
  left_ = nullptr;
  return;
}

char Node::GetData() {
  return data_;
}

Node* Node::GetPreviousNode() {
  return left_;
}

Node* Node::GetNextNode() {
  return right_;
}

Node* Node::InsertPreviousNode(char data) {
  Node* newNode = new Node(data);
  if (left_ == nullptr) {
    newNode->right_ = this;
    this->left_ = newNode;
  }
  else {
    Node* currentPrevNode = left_;
    currentPrevNode->right_ = newNode;
    newNode->left_ = currentPrevNode;
    this->left_ = newNode;
    newNode->right_ = this;
  }

  // check nullptr case
  return newNode;
}

Node* Node::InsertNextNode(char data) {
  // 현재 노드 오른쪽에 넣는다
  // 만약 이미 오른쪽 노드가 있다면 현재 노드와 사이에 넣는다. 
  Node* newNode = new Node(data);
  if (right_ == nullptr) {
    newNode->left_ = this;
    this->right_ = newNode;
  }
  else {
    // handle current prev
    Node* currentNextNode = right_;
    currentNextNode->left_ = newNode;
    newNode->right_ = currentNextNode;

    // handle this
    this->right_ = newNode;
    newNode->left_ = this;
  }
  // check nullptr case
  return newNode;
}

bool Node::ErasePreviousNode() {
  if (left_ == nullptr) return false;
  else {
    Node* currentPrev = left_;
    Node* previousPrev = currentPrev->left_;
    if (previousPrev == nullptr) {
      // just delete it
      left_ = nullptr;
    }
    else {
      // prevPrev is alive
      previousPrev->right_ = this;
      this->left_ = previousPrev;
    }
    delete (currentPrev);
    return true;
  }
}

bool Node::EraseNextNode() {
  if (right_ == nullptr) return false;
  else {
    Node* currentNext = right_;
    Node* nextNext = currentNext->right_;
    if (nextNext == nullptr) {
      // just delete it
      right_ = nullptr;
    }
    else {
      // prevPrev is alive
      nextNext->left_ = this;
      this->right_ = nextNext;
    }
    delete (currentNext);
    return true;
  }
}