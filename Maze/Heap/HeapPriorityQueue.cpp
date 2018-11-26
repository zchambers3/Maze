//HeapPriorityQueue.cpp
#ifndef _HEAPPRIORITYQUEUE_CPP
#define _HEAPPRIORITYQUEUE_CPP

#include "HeapPriorityQueue.hpp"
#include <cassert>
#include <cstdlib>//for NULL
#include <iostream>

HeapPriorityQueue::HeapPriorityQueue() {
    // Empty... nothing needs to be done.
}

HeapPriorityQueue::~HeapPriorityQueue() {
    // no clean-up to do, since the heap is not dynamically allocated
}

/**
 * Adds an element to the vector heap
 * @param elem a pointer to the MazeState element to be added to the heap priority queue.
 */
void HeapPriorityQueue::add(MazeState *elem) {
    // TODO:  Implement this!
    //insert new element at the end of the heap
    heap.push_back(elem);
    int insertedElem = (int) heap.size() - 1;
    int currentParent = parent(insertedElem);
    //swap as long as the inserted element is less than its parent and tje parent is greater than 0 (within the heap)
    while (currentParent >= 0 && heap[insertedElem]->getBadness() < heap[currentParent]->getBadness()) {
        std::swap(heap[insertedElem], heap[currentParent]);
        insertedElem = currentParent;
        currentParent = parent(insertedElem);
    }

}

/**
 * Removes the minimum element in the heap - the root, but still keeping heap property (swapping down)
 * @returns the removed element
 */
MazeState *HeapPriorityQueue::remove() {
// TODO:  Implement this!
    assert(!is_empty());
    int nextRoot;
    MazeState *ret = heap[0];
    //move last element to be the root
    heap[0] = heap[(int) heap.size() - 1];
    heap.pop_back();

    int currentRoot = 0;
    int currentFirstChild = first_child(currentRoot);
    //iterate through the heap
    while (currentFirstChild < (int) heap.size()) {
        nextRoot = currentFirstChild;
        //only one child, if root is larger need to swap with child
        if (num_children(currentRoot) == 1) {
            if (heap[currentRoot]->getBadness() > heap[currentFirstChild]->getBadness())
                std::swap(heap[currentRoot], heap[currentFirstChild]);
        }
            //2 children, if root is larger need to swap with smaller child
        else if (num_children(currentRoot) == 2) {
            int rightBadness = heap[currentFirstChild + 1]->getBadness();
            int leftBadness = heap[currentFirstChild]->getBadness();
            if (heap[currentRoot]->getBadness() > min(leftBadness, rightBadness)) {
                //swap is necessary, check for smaller badness
                if (leftBadness < rightBadness)
                    std::swap(heap[currentRoot], heap[currentFirstChild]);

                else {
                    std::swap(heap[currentRoot], heap[currentFirstChild + 1]);
                    //the next root will be the left child
                    nextRoot = currentFirstChild + 1;
                }
            }
        }
        currentRoot = nextRoot;
        currentFirstChild = first_child(currentRoot);
    }
    return ret;

}

/**
 * Checks whether the heap priority queue is empty or not
 * @returns true if empty and false if not
 */
bool HeapPriorityQueue::is_empty() {
    return ((int) heap.size() == 0);

}

// You might find these helper functions helpful...
int HeapPriorityQueue::parent(int index) {
    return (index - 1) / 2;
}

int HeapPriorityQueue::first_child(int index) {
    return 2 * index + 1;
}

bool HeapPriorityQueue::is_root(int index) {
    return index == 0;
}

bool HeapPriorityQueue::is_leaf(int index) {
    return num_children(index) == 0;
}

int HeapPriorityQueue::num_children(int index) {
    int fchild = first_child(index);
    return max(0, min(2, (int) heap.size() - fchild));
}

#endif
