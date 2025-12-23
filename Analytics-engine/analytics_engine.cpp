#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

struct StorageEvent {
    string file_id;
    string event_type;
    long timestamp;
    int size_mb;
};

unordered_map<string, int> access_count;
unordered_map<string, int> storage_usage;

void processEvent(const StorageEvent& event) {
    if (event.event_type == "UPLOAD") {
        storage_usage[event.file_id] = event.size_mb;
        access_count[event.file_id] = 1;
    } else if (event.event_type == "READ") {
        access_count[event.file_id]++;
    } else if (event.event_type == "DELETE") {
        storage_usage.erase(event.file_id);
        access_count.erase(event.file_id);
    }
}

void printAnalytics() {
    cout << "\n=== Storage Analytics ===\n";
    for (auto& entry : access_count) {
        string file_id = entry.first;
        int accesses = entry.second;
        string status = accesses >= 3 ? "HOT" : "COLD";

        cout << "File: " << file_id
             << " | Accesses: " << accesses
             << " | Status: " << status << endl;
    }
}

int main() {
    vector<StorageEvent> events = {
        {"file_1", "UPLOAD", time(nullptr), 10},
        {"file_1", "READ", time(nullptr), 10},
        {"file_1", "READ", time(nullptr), 10},
        {"file_2", "UPLOAD", time(nullptr), 20},
        {"file_2", "READ", time(nullptr), 20}
    };

    for (const auto& event : events) {
        processEvent(event);
    }

    printAnalytics();
    return 0;
}
