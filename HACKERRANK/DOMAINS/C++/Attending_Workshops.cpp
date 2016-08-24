#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//Define the structs Workshops and Available_Workshops.
struct Workshop {
    int start_time;
    int duration;
    int end_time;
};

struct Available_Workshops {
    int n;
    vector<Workshop> workshops;
};

//Implement the functions initialize and CalculateMaxWorkshops
Available_Workshops* initialize (int start_time[], int duration[], int n){
    Available_Workshops* ptr = new Available_Workshops;
    ptr->workshops.resize(n);
    ptr->n = n;
    for(int i=0; i<n; ++i){
      ptr->workshops[i].start_time = start_time[i];
      ptr->workshops[i].duration = duration[i];
      ptr->workshops[i].end_time = start_time[i] + duration[i];
    }
    return ptr;
}

int compare (Workshop w1,Workshop w2){
    if(w1.end_time != w2.end_time){
        return w1.end_time < w2.end_time;
    }
    else{
      return w1.start_time < w2.start_time;
    }
}

int CalculateMaxWorkshops(Available_Workshops* ptr) {
    int attend = 0;
    sort(ptr->workshops.begin(), ptr->workshops.end(), compare);

    int prev = ptr->workshops[0].end_time;
    attend++;
    for(int i=1; i<ptr->n; ++i){
        if(ptr->workshops[i].start_time >= prev){
            prev = ptr->workshops[i].end_time;
            attend++;
        }
    }
    return attend;
}

int main(int argc, char *argv[]) {
    int n; // number of workshops
    cin >> n;
    // create arrays of unknown size n
    int* start_time = new int[n];
    int* duration = new int[n];

    for(int i=0; i < n; i++){
        cin >> start_time[i];
    }
    for(int i = 0; i < n; i++){
        cin >> duration[i];
    }

    Available_Workshops * ptr;
    ptr = initialize(start_time,duration, n);
    cout << CalculateMaxWorkshops(ptr) << endl;
    return 0;
}
