// Copyright 2021
#include "LinkedList.h"

#include <iostream>
LinkedList::LinkedList() {
    this->head = nullptr;
    this->tail = nullptr;
}

LinkedList::~LinkedList() { clear(); }
LinkedList::LinkedList(LinkedList& list) {
    if (list.head != nullptr) {
        this->head = new Node(*list.head);
        Node* currentNode = head;
        while (currentNode->next != nullptr) {
            currentNode = currentNode->next;
        }
        this->tail = currentNode;
    } else {
        this->head = nullptr;
        this->tail = nullptr;
    }
}

Tile* LinkedList::getTile(Tile* tile) {
    bool tileNotFound = true;
    Tile* retTile = nullptr;
    if (size() > 0) {
        Node* currentNode = head;
        while (tileNotFound && currentNode != nullptr) {
            if (currentNode->containsTile(tile)) {
                tileNotFound = false;
                retTile = new Tile(*currentNode->tile);
                removeTile(retTile);
            } else {
                currentNode = currentNode->next;
            }
        }
    }
    return retTile;
}

void LinkedList::addTile(Tile* tile) {
    Node* newNode = new Node(new Tile(*tile), nullptr);
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = tail->next;
    }
    delete tile;
}

Tile* LinkedList::takeFront() {
    Tile* toReturn = nullptr;
    if (size() > 0) {
        toReturn = new Tile(*head->tile);
        removeFront();
    }
    return toReturn;
}

// Front of list removal
void LinkedList::removeFront() {
    if (size() > 0) {
        Node* toDelete = head;
        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
        }
        delete toDelete;
    }
}

// Remove tile, used for player hand.
void LinkedList::removeTile(Tile* tile) {
    bool tileNotFound = true;
    Node* prevNode = head;
    Node* currentNode = head;

    if (size() > 0) {
        if (head == tail || head->containsTile(tile)) {
            removeFront();
        } else {
            while (tileNotFound && currentNode != nullptr) {
                if (currentNode == tail) {
                    prevNode->next = nullptr;
                    tail = prevNode;
                }
                if (currentNode->containsTile(tile)) {
                    tileNotFound = false;
                    prevNode->next = currentNode->next;
                    delete currentNode;
                } else {
                    prevNode = currentNode;
                    currentNode = currentNode->next;
                }
            }
        }
    }
}
int LinkedList::size() {
    int count = 0;
    Node* currentNode = head;
    while (currentNode != nullptr) {
        currentNode = currentNode->next;
        ++count;
    }
    return count;
}

bool LinkedList::contains(Tile* tile) {
    Node* currentNode = head;
    bool containsTile = false;
    while (currentNode != nullptr && !containsTile) {
        if (currentNode->containsTile(tile)) {
            containsTile = true;
        }
        currentNode = currentNode->next;
    }
    return containsTile;
}

std::string LinkedList::toString() {
    std::string listDetails;
    if (true) {
        int index = 0;
        int count = size();
        Node* currentNode = head;
        listDetails = "";
        while (index < count) {
            Tile tile = *currentNode->tile;
            listDetails.append(tile.toString());
            if (index < count - 1) {
                listDetails.append(",");
            }
            currentNode = currentNode->next;
            ++index;
        }
        listDetails.append("\n");
    }
    return listDetails;
}

void LinkedList::clear() {
    while (head != nullptr) {
        removeFront();
    }
}
