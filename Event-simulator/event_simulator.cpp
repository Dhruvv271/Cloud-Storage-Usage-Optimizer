#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

struct StorageEvent {
    string file_id;
    string event_type;
    long timestamp;
    int size_mb;
};

string randomEventType() {
    vector<string> events = {"UPLOAD", "READ", "DELETE"};
    return events[rand() % events.size()];
}

int main() {
    srand(time(nullptr));

    for (int i = 0; i < 10; i++) {
        StorageEvent event;
        event.file_id = "file_" + to_string(rand() % 100);
        event.event_type = randomEventType();
        event.timestamp = time(nullptr);
        event.size_mb = (rand() % 100) + 1;

        cout << "{ "
             << "\"file_id\": \"" << event.file_id << "\", "
             << "\"event_type\": \"" << event.event_type << "\", "
             << "\"timestamp\": " << event.timestamp << ", "
             << "\"size_mb\": " << event.size_mb
             << " }" << endl;
    }

    return 0;
}
