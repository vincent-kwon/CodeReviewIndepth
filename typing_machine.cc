// Copyright 2018 <Author>

#include "typing_machine.h"
#include <iostream>
#include <sstream>

using namespace std;

TypingMachine::TypingMachine() {
  currentNode_ = nullptr;
  nonNullLeftMost = false;
  nonNullLeftMostNextPtr = nullptr;
  return;
}

void TypingMachine::HomeKey() {
  if (currentNode_ != nullptr) {
    while (true) {
      Node* temp = currentNode_->GetPreviousNode();
      if (temp != nullptr) {
        currentNode_ = temp;
      }
      else {
        break;
      }
    }
    // now it is the last node, treat specially
    nonNullLeftMost = true;
    nonNullLeftMostNextPtr = currentNode_;
    currentNode_ = nullptr;
  }
  return;
}

void TypingMachine::EndKey() {

  if (currentNode_ == nullptr && nonNullLeftMost == true) {
    currentNode_ = nonNullLeftMostNextPtr;
    nonNullLeftMost = false;
    nonNullLeftMostNextPtr = nullptr;
  }

  if (currentNode_ != nullptr) {
    while (true) {
      Node* temp = currentNode_->GetNextNode();
      if (temp != nullptr) {
        currentNode_ = temp;
      }
      else {
        break;
      }
    }
  }
  return;
}

void TypingMachine::LeftKey() {
  if (currentNode_ != nullptr) {
    Node *temp = currentNode_->GetPreviousNode();
    if (temp) {
      currentNode_ = temp;
    }
    else {
      // now left edge, treat specially
      nonNullLeftMost = true;
      nonNullLeftMostNextPtr = currentNode_;
      currentNode_ = nullptr;
    }
  }
  return;
}

void TypingMachine::RightKey() {
  if (currentNode_ != nullptr) {
    Node *temp = currentNode_->GetNextNode();
    if (temp) {
      currentNode_ = temp;
    }
  }
  else if (currentNode_ == nullptr && nonNullLeftMost == true) {
    currentNode_ = nonNullLeftMostNextPtr;
    nonNullLeftMost = false;
    nonNullLeftMostNextPtr = nullptr;
  }
  return;
}

bool TypingMachine::TypeKey(char key) {
  if ((key >= 32 && key <= 126) && (count < 100)) {
    if (currentNode_ == nullptr && nonNullLeftMost == false) {
      currentNode_ = new Node(key);
    }
    else if (currentNode_ == nullptr && nonNullLeftMost == true) {
      nonNullLeftMostNextPtr->InsertPreviousNode(key);
      currentNode_ = nonNullLeftMostNextPtr->GetPreviousNode();
      // recover
      nonNullLeftMostNextPtr = nullptr;
      nonNullLeftMost = false;
    }
    else {
      Node* returnValue = currentNode_->InsertNextNode(key);
      if (returnValue) {
        currentNode_ = currentNode_->GetNextNode();
      }
    }
    count++;
    return true;
  }
  else {
    return false;
  }
}

bool TypingMachine::EraseKey() {
  if (currentNode_ != nullptr) {
    Node* leftNode = currentNode_->GetPreviousNode();
    Node* rightNode = currentNode_->GetNextNode();
    count--;
    if (leftNode && rightNode) {
      currentNode_ = leftNode;
      return rightNode->ErasePreviousNode();
    }
    else if (leftNode) {
      // right edge
      currentNode_ = leftNode;
      return currentNode_->EraseNextNode();
    }
    else if (rightNode) {
      // left edge
      currentNode_ = nullptr;
      nonNullLeftMost = true;
      nonNullLeftMostNextPtr = rightNode;
      return rightNode->ErasePreviousNode();
    }
    else {
      // if no left and right 
      delete(currentNode_);
      currentNode_ = nullptr;
      nonNullLeftMost = false;
      nonNullLeftMostNextPtr = nullptr;
      return true;
    }
  }
  return false;
}

std::string TypingMachine::Print(char separator) {
  stringstream ss;
  ss << "";
  if (separator != 0) {
    ss << separator;
  }
  string cursorString = ss.str();

  // handle current node null
  if (currentNode_ == nullptr && nonNullLeftMost == false) {
    return cursorString;
  }
  else if (currentNode_ != nullptr) {
    // move cursor to the left edge
    Node* currentPrint;

    if (currentNode_ == nullptr && nonNullLeftMost == true) {

    }
    else {
      currentPrint = currentNode_;
    }

    while (true) {
      if (currentPrint->GetPreviousNode()) {
        currentPrint = currentPrint->GetPreviousNode();
      }
      else {
        break;
      }
    }

    // now currentPrint point to the start of link
    // iterate
    stringstream sReturn;
    sReturn << "";
    while (currentPrint) {
      sReturn << currentPrint->GetData();
      if (currentPrint == currentNode_) {
        sReturn << cursorString;
      }
      currentPrint = currentPrint->GetNextNode();
    }
    return sReturn.str();
  }
  else {
    stringstream sReturn;
    sReturn << "" << cursorString;
    Node* currentPrint = nonNullLeftMostNextPtr;
    while (currentPrint) {
      sReturn << currentPrint->GetData();
      if (currentPrint == currentNode_) {
        sReturn << cursorString;
      }
      currentPrint = currentPrint->GetNextNode();
    }
    return sReturn.str();
  }
}
