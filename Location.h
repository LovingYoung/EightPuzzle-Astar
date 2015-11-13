//
// Created by LovingYoung on 10/28/2015.
//

#ifndef ASTAR_LOCATION_H
#define ASTAR_LOCATION_H

#define NULL 0

#include <vector>
using namespace std;

namespace liuyang {
    class Location {
    public:
        Location(vector<int> init) {
            list = init;
            level = 0;
            parent = NULL;
        }

        Location(vector<int> init, Location * m_parent){
            list = init;
            level = m_parent->getLevel() + 1;
            parent = m_parent;
        }

        Location(const Location & b){
            this->list = b.getList();
            this->parent = b.getParent();
            this->level = b.getLevel();
        }

        int &operator[](int i) {
            return list[i];
        }

        bool operator<(Location &right) {
            return this->getPriority() < right.getPriority();
        }

        const int getPriority() const {
            int sum = 0;
            for (int i = 0; i < list.size(); i++) {
                if (list[i] != 0) {
                    int x1 = (list[i] - 1) % 3;
                    int y1 = (list[i] - 1) / 3;
                    int x2 = i % 3;
                    int y2 = i / 3;
                    sum += x2 > x1 ? (x2 - x1) : (x1 - x2);
                    sum += y2 > y1 ? (y2 - y1) : (y1 - y2);
                }
            }
            return sum;
        }

        const bool isComplete() const {
            return getPriority() == 0;
        }

        const int getLevel() const {
            return level;
        }

        Location* getParent() const{
            return parent;
        }

        void addLevel() {
            level += 1;
        }

        void decreaseLevel() {
            level -= 1;
        }

        const vector<int> getList() const {
            return list;
        }

        const bool operator< (const Location &b) const {
            vector<int> list1 = this->getList();
            vector<int> list2 = b.getList();
            return lexicographical_compare(list1.begin(), list1.end(), list2.begin(), list2.end());
        }

        const bool operator== (const Location &b) const{
            vector<int> list1 = this->getList();
            vector<int> list2 = b.getList();
            for (int i = 0; i < list1.size(); i++) {
                if (list1[i] != list2[i]) return false;
            }
            return true;
        }

        const bool operator != (const Location &b) const {
            return !(*this==(b));
        }

    private:
        vector<int> list;
        int level;
        Location *parent;
    };


    class CompareLocation {
    public:
        bool operator()(Location * a, Location * b) {
            return a->getPriority() + a->getLevel() > b->getPriority() + b->getLevel();
        }
    };
}


#endif //ASTAR_LOCATION_H
