
#include "LinkedList.h"

LinkedList::LinkedList() {
    head = nullptr;
    tail = nullptr;
    count = 0;
}

LinkedList::~LinkedList() {
    clear();
}

void LinkedList::addTile(Tile* tile) {
    Node* newNode = new Node(tile, nullptr);
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = new Node(tile, nullptr);
        tail = tail->next;
    }
    ++count;
}

//Front of list removal
Tile* LinkedList::removeFront() {
    Tile* retTile = nullptr;
    if (count > 0) {
        Node* toDelete = head;
        retTile = new Tile(*head->tile);
        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
        }
        delete toDelete;
        --count;
    }
    return retTile;
}

//
Tile* LinkedList::removeTile(Tile* tile) {
    bool tileNotFound = true;
    Node* prevNode = head;
    Node* currentNode = head;
    Tile* retTile = nullptr;

    if (count > 0) {
        if (head == tail && head->containsTile(tile)) {
            retTile = removeFront();
        } else {
            while (tileNotFound && currentNode != nullptr) {
                if (currentNode->containsTile(tile)) {
                    tileNotFound = true;
                    retTile = new Tile(*currentNode->tile);
                    prevNode->next = currentNode->next;
                    delete currentNode;
                } else {
                    prevNode = currentNode;
                    currentNode = currentNode->next;
                }
            }
            --count;
        }
    }
    return retTile;
}
int LinkedList::size() {
    return count;
}

bool LinkedList::contains(Tile tile) {
    return true;
}

std::string LinkedList::toString() {
    if (count > 0) {
        int index = 0;
        Node* currentNode = head;
        std::string listDetails = "";
        while (index < count) {
            Tile* tile = currentNode->tile;
            listDetails.append(tile->colour + tile->shape + ",");
            currentNode = currentNode->next;
            ++index;
        }
    }
}

void LinkedList::clear() {
    while (head != nullptr) {
        removeFront();
    }
}