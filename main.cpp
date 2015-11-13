#include <queue>
#include <set>
#include <vector>
#include "Location.h"
#include <fstream>

using namespace std;


ifstream fin("data.in");
ofstream cout("data.out");
ofstream fout("data1.out");

void swap(int & a, int & b){
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
}
bool HaveSolution(liuyang::Location & st)
{
    vector<int> list = st.getList();
    int tar[9] = {1,2,3,4,5,6,7,8,0};
    vector<int> target(tar, tar+9);
    int i,j,sum2 = 0,sum1 = 0;
    for( i = 0; i < list.size(); i++ )
        for( j = 0; j < i; j++ )
        {
            if(( list[i] - 48) * (list[j] - 48))
            {
                if( list[j] < list[i] )
                    sum1++;
            }
        }
    for( i = 0; i< list.size(); i++ )
        for( j = 0; j < i; j++ )
        {
            if( (target[i] - 48) * ( target[j] - 48 ) )
            {
                if( target[j] < target[i] )
                    sum2++;
            }
        }

    if( sum1 % 2 == sum2 % 2 )
        return true;
    return false;
}
vector<vector<int> > solution(liuyang::Location in){
    if(HaveSolution(in)) {
        cout << 1 << endl;
        fout << 1 << endl;
    }
    else{
        cout << 0 << endl;
        fout << 0 << endl;
        vector<vector<int> > n;
        return n;
    }
    vector<vector<int> > ans;
    liuyang::Location * pre = NULL;
    liuyang::Location * current= NULL;
    liuyang::Location * all = NULL;
    set<liuyang::Location> locationSet;
    priority_queue<liuyang::Location *, vector<liuyang::Location *>, liuyang::CompareLocation> q;
    q.push(&in);
    while(!q.top()->isComplete() && !q.empty()){
        liuyang::Location a = *(q.top());
        if(locationSet.find(a) != locationSet.end()){
            q.pop();
            continue;
        }
        current = q.top();
        locationSet.insert(*q.top());
        liuyang::Location * temp = new liuyang::Location(*q.top());

        if((pre == NULL && current->getParent() != NULL) || (pre != NULL && current->getParent() == NULL) || (pre != NULL && current->getParent() != NULL && *pre != *(current->getParent()))){
            //find
            liuyang::Location * tempPointer1 = pre;
            liuyang::Location * tempPointer2 = current->getParent();

            while(tempPointer1 != NULL){
		    int flag = 1;
                while(tempPointer2 != NULL){
                    if(tempPointer1 == tempPointer2 && flag){
			    all = tempPointer1;
			    flag = 0;
		    }
                    tempPointer2 = tempPointer2->getParent();
                }
                tempPointer1 = tempPointer1->getParent();
            }

            vector<vector<int> > up;
            tempPointer1 = pre->getParent();
            while(tempPointer1 != all){
                vector<int> tempList = tempPointer1->getList();
                tempList.push_back(0);
                up.push_back(tempList);
                tempPointer1 = tempPointer1->getParent();
            }

            vector<vector<int> > down;
            tempPointer2 = current->getParent();
            while(tempPointer2 != all){
                vector<int> tempList = tempPointer2->getList();
                tempList.push_back(0);
                down.push_back(tempList);
                tempPointer2 = tempPointer2->getParent();
            }

            ans.insert(ans.end(), up.begin(), up.end());
            ans.insert(ans.end(), down.rbegin(), down.rend());
        }
        vector<int> tempList = temp->getList();
        tempList.push_back(1);
        ans.push_back(tempList);
        pre = current;
        q.pop();
        int index = 0;

        //find the index of the blank;
        for(; index < 8; index++){
            if((*temp)[index] == 0) break;
        }

        //if there is an element on its left;
        int change[4] = {-1, 1, 3, -3};
        int flag[4] = {0};
        if(index % 3 != 0) flag[0] = 1;
        if(index % 3 != 2) flag[1] = 1;
        if(index / 3 != 2) flag[2] = 1;
        if(index / 3 != 0) flag[3] = 1;

        for(int i = 0; i < 4; i++){
            if(flag[i]){
                swap((*temp)[index + change[i]], (*temp)[index]);
                liuyang::Location * st1 = new liuyang::Location(temp->getList(), temp);
                q.push(st1);
                swap((*temp)[index + change[i]], (*temp)[index]);
            }
        }

//        if(index % 3 != 0){ //have element: swap
//            temp[index - 1] = temp[index - 1] ^ temp[index];
//            temp[index] = temp[index - 1] ^ temp[index];
//            temp[index - 1] = temp[index - 1] ^ temp[index];
//            swap(temp[index], temp[index-1]);
//            temp.addLevel();
//            q.push(temp);
//            temp.decreaseLevel();
//
//            //turn back
//            temp[index - 1] = temp[index - 1] ^ temp[index];
//            temp[index] = temp[index - 1] ^ temp[index];
//            temp[index - 1] = temp[index - 1] ^ temp[index];
//        }
//
//        //if there is an element on its right;
//        if(index % 3 != 2){// just the same as above
//            temp[index + 1] = temp[index + 1] ^ temp[index];
//            temp[index] = temp[index + 1] ^ temp[index];
//            temp[index + 1] = temp[index + 1] ^ temp[index];
//            temp.addLevel();
//            q.push(temp);
//            temp.decreaseLevel();
//
//            //turn back
//            temp[index + 1] = temp[index + 1] ^ temp[index];
//            temp[index] = temp[index + 1] ^ temp[index];
//            temp[index + 1] = temp[index + 1] ^ temp[index];
//        }
//
//        //if there is an element on its bottom;
//        if(index / 3 != 2){// just the same as above
//            temp[index + 3] = temp[index + 3] ^ temp[index];
//            temp[index] = temp[index + 3] ^ temp[index];
//            temp[index + 3] = temp[index + 3] ^ temp[index];
//            temp.addLevel();
//            q.push(temp);
//            temp.decreaseLevel();
//
//            //turn back
//            temp[index + 3] = temp[index + 3] ^ temp[index];
//            temp[index] = temp[index + 3] ^ temp[index];
//            temp[index + 3] = temp[index + 3] ^ temp[index];
//        }
//
//        //if there is an element on its above;
//        if(index / 3 != 0){// just the same as above
//            temp[index - 3] = temp[index - 3] ^ temp[index];
//            temp[index] = temp[index - 3] ^ temp[index];
//            temp[index - 3] = temp[index - 3] ^ temp[index];
//            temp.addLevel();
//            q.push(temp);
//            temp.decreaseLevel();
//
//            //turn back
//            temp[index - 3] = temp[index - 3] ^ temp[index];
//            temp[index] = temp[index - 3] ^ temp[index];
//            temp[index - 3] = temp[index - 3] ^ temp[index];
//        }
    }
    liuyang::Location * root = NULL;
    if(!q.empty()) {
        ans.push_back(q.top()->getList());
	ans[ans.size() - 1].push_back(1);
        root = q.top();
    } else {
        cout << "No Answer" << endl;
    }

    vector<vector<int> > reverse;
    while(root != NULL){
        reverse.push_back(root->getList());
        root = root->getParent();
    }

    vector<vector<int> > shortest;
    shortest.insert(shortest.end(), reverse.rbegin(), reverse.rend());
    for(int i = 0; i < shortest.size(); i++){
        for(int j = 0; j < shortest[i].size(); j++){
            fout << (shortest[i])[j] << ' ';
        }
        fout << endl;
    }

    return ans;
}

int main(){
    vector<int> myList(9);
//    myList.push_back(0);
//    myList.push_back(1);
//    myList.push_back(3);
//    myList.push_back(4);
//    myList.push_back(2);
//    myList.push_back(8);
//    myList.push_back(5);
//    myList.push_back(7);
//    myList.push_back(6);

    for(int i = 0; i < 9; i++)
        fin >> myList[i];

    liuyang::Location in(myList);
    vector<vector<int> > ans = solution(in);
    for(int i = 0; i < ans.size(); i++) {
        for (int j = 0; j < ans[i].size(); j++) {
            cout << ans[i][j] << ' ';
        }
        cout << endl;
    }
}



