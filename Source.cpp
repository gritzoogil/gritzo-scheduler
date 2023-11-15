#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

#ifdef _WIN32
#define CLEAR_COMMAND "cls"
#else
#define CLEAR_COMMAND "clear"
#endif

using namespace std;

// Function to format time with leading zeros
string formatTime(int hour, int minute) {
    stringstream ss;
    ss << (hour < 10 ? "0" : "") << hour << ":" << (minute < 10 ? "0" : "") << minute;
    return ss.str();
}

int main() {
    vector<string> myTasks;

    // Input tasks
    cout << "List all of your tasks for the whole day. Type 'done' if you're done:" << endl;
    string task;
    while (getline(cin, task) && task != "done") {
        myTasks.push_back(task);
    }

    system(CLEAR_COMMAND);

    // Display tasks
    cout << "Your tasks:" << endl << endl;
    for (size_t i = 0; i < myTasks.size(); ++i) {
        cout << i + 1 << ": " << myTasks[i] << endl;
    }

    // Select an important task
    int timeImportant;
    while (true) {
        cout << "Which task do you need to finish immediately?: ";

        if (!(cin >> timeImportant)) {
            cout << "Invalid input. Please enter a number." << endl << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else if (timeImportant < 1 || timeImportant > static_cast<int>(myTasks.size())) {
            cout << "Invalid input. Choose a valid task number." << endl << endl;
        }
        else {
            // Consume the newline character in the buffer
            cin.ignore();
            break; // Valid input, exit the loop
        }
    }

    // Use an if statement to handle different tasks based on the user's choice
    string priority1;
    if (timeImportant >= 1 && timeImportant <= static_cast<int>(myTasks.size())) {
        priority1 = myTasks[timeImportant - 1];
        // Erase the selected task from myTasks
        myTasks.erase(myTasks.begin() + timeImportant - 1);
    }
    else {
        cout << "Invalid choice in the if statement." << endl;
    }

    system(CLEAR_COMMAND);

    // Display tasks
    cout << "Your tasks:" << endl << endl;
    for (size_t i = 0; i < myTasks.size(); ++i) {
        cout << i + 1 << ": " << myTasks[i] << endl;
    }

    int hardImportant;
    while (true) {
        cout << "Which task is the hardest? (not the same as the first option): ";

        if (!(cin >> hardImportant)) {
            cout << "Invalid input. Please enter a number." << endl << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else if (hardImportant < 1 || hardImportant > static_cast<int>(myTasks.size())) {
            cout << "Invalid input. Choose a valid task number." << endl << endl;
        }
        else {
            break; // Valid input, exit the loop
        }
    }

    // Use an if statement to handle different tasks based on the user's choice
    string priority2;
    if (hardImportant >= 1 && hardImportant <= static_cast<int>(myTasks.size())) {
        priority2 = myTasks[hardImportant - 1];
        // Erase the selected task from myTasks
        myTasks.erase(myTasks.begin() + hardImportant - 1);
    }
    else {
        cout << "Invalid choice in the if statement." << endl;
    }

    system(CLEAR_COMMAND);

    // Create a vector for remaining tasks and their ratings
    vector<pair<string, int>> remainingTasks;

    // Display remaining tasks
    cout << "Remaining tasks:" << endl << endl;
    for (size_t i = 0; i < myTasks.size(); ++i) {
        cout << i + 1 << ": " << myTasks[i] << endl;
    }

    // Collect ratings for remaining tasks
    for (size_t i = 0; i < myTasks.size(); ++i) {
        // Rate each remaining task out of 5
        int rating;
        while (true) {
            cout << "Rate Task " << i + 1 << " (1 - easy, 5 - hard): ";
            cin >> rating;

            if (cin.fail() || rating < 1 || rating > 5) {
                cout << "Invalid rating. Please enter a number between 1 and 5." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else {
                remainingTasks.push_back({ myTasks[i], rating });
                break;
            }
        }
    }


    // Sort remaining tasks by rating (highest to lowest)
    sort(remainingTasks.begin(), remainingTasks.end(),
        [](const pair<string, int>& a, const pair<string, int>& b) {
            return a.second > b.second;  // Sort in descending order based on rating
        });

    // Create a vector to store the task names
    vector<string> rankedTaskNames;

    // Add priority1 and priority2 to the rankedTaskNames vector
    rankedTaskNames.push_back(priority1);
    rankedTaskNames.push_back(priority2);

    // Add the remaining tasks to the rankedTaskNames vector
    for (const auto& task : remainingTasks) {
        rankedTaskNames.push_back(task.first);
    }

    system(CLEAR_COMMAND);

    string startTime;
    cout << "What time do you want to start? (example: 4:30): ";
    cin >> startTime;

    // ...

    // Asks the user how much time each task takes
    cout << "How much time will each task take? (example: 1hr30mins = 1.5)" << endl;

    vector<double> taskDurations;

    for (size_t i = 0; i < rankedTaskNames.size(); ++i) {
        double duration;
        cout << "Task " << i + 1 << ": " << rankedTaskNames[i] << ": ";
        cin >> duration;
        taskDurations.push_back(duration);
    }
    system(CLEAR_COMMAND);

    // Display each task with its designated time
    cout << "Your schedule:" << endl << endl;

    // Convert start time to hours and minutes
    int startHour, startMinute;
    sscanf_s(startTime.c_str(), "%d:%d", &startHour, &startMinute);

    for (size_t i = 0; i < rankedTaskNames.size(); ++i) {
        // Calculate end time
        int endHour = startHour + static_cast<int>(taskDurations[i]);
        int endMinute = startMinute + static_cast<int>((taskDurations[i] - static_cast<int>(taskDurations[i])) * 60);

        // Handle overflow
        if (endMinute >= 60) {
            endHour += 1;
            endMinute -= 60;
        }

        // Display task and time range
        cout << rankedTaskNames[i] << ": " << formatTime(startHour, startMinute)
            << " - " << formatTime(endHour, endMinute) << endl;

        // Update start time for the next task
        startHour = endHour;
        startMinute = endMinute;
    }

    return 0;
}
