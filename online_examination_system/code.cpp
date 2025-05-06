// online examination system
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

// Structure for a Question
struct Question {
    string category;
    string question;
    string options[4];
    char correctAnswer;
};

// Class for User Authentication
class User {
    string username, password;

public:
    bool registerUser(string user, string pass) {
        ofstream outFile("users.txt", ios::app);
        if (!outFile) {
            cout << "Error opening user file!\n";
            return false;
        }
        outFile << user << " " << pass << endl;
        outFile.close();
        cout << "Registration successful!\n";
        return true;
    }

    bool loginUser(string user, string pass) {
        ifstream inFile("users.txt");
        if (!inFile) {
            cout << "Error opening user file!\n";
            return false;
        }
        string u, p;
        while (inFile >> u >> p) {
            if (u == user && p == pass) {
                inFile.close();
                return true;
            }
        }
        inFile.close();
        return false;
    }
};

// Class for Exam System
class Exam {
    vector<Question> questions;
    map<string, vector<Question>> categorizedQuestions;

public:
    // Load Questions
    void loadQuestions() {
        questions = {

            {"Math", "What is 2 + 2?", {"1", "2", "4", "5"}, 'C'},
            {"Math", "What is 5 * 3?", {"8", "15", "20", "10"}, 'B'},
            {"Math", "What is 5 * 4?", {"8", "15", "20", "10"}, 'C'},
            {"Science", "What is H2O?", {"Oxygen", "Water", "Hydrogen", "Nitrogen"}, 'B'},
            {"Science", "What is CO2?", {"Carbondioxide", "Water", "Hydrogen", "Nitrogen"}, 'A'},
            {"Science", "What planet is known as the Red Planet?", {"Earth", "Mars", "Jupiter", "Saturn"}, 'B'}
        };

        // Categorize Questions
        for (const auto& q : questions) {
            categorizedQuestions[q.category].push_back(q);
        }
    }

    // Conduct Exam
    void takeExam(string username) {
        if (questions.empty()) {
            cout << "No questions available!\n";
            return;
        }

        int score = 0, total = questions.size();
        cout << "\nExam Started! Choose the correct option (A/B/C/D).\n";

        for (const auto& q : questions) {
            cout << "\nCategory: " << q.category << "\n";
            cout << q.question << endl;
            cout << "A) " << q.options[0] << "  B) " << q.options[1] << "  C) " << q.options[2] << "  D) " << q.options[3] << endl;
            
            char ans;
            cout << "Your answer: ";
            cin >> ans;
            ans = toupper(ans);

            if (ans == q.correctAnswer) score++;
        }

        double percentage = (double)score / total * 100;
        cout << "\nExam Over! You scored " << score << "/" << total << " (" << percentage << "%).\n";

        // Save Result
        saveResult(username, score, total);
    }

    // Save Exam Result
    void saveResult(string username, int score, int total) {
        ofstream outFile("results.txt", ios::app);
        if (!outFile) {
            cout << "Error opening result file!\n";
            return;
        }
        outFile << username << " " << score << "/" << total << endl;
        outFile.close();
    }

    // Display Results
    void displayResults() {
        ifstream inFile("results.txt");
        if (!inFile) {
            cout << "No results found!\n";
            return;
        }

        string line;
        cout << "\nExam Results:\n";
        while (getline(inFile, line)) {
            cout << line << endl;
        }
        inFile.close();
    }
};

// Main Function
int main() {
    User user;
    Exam exam;
    exam.loadQuestions();

    int choice;
    string username, password;

    while (true) {
        cout << "\n--- Online Examination System ---\n";
        cout << "1. Register\n2. Login\n3. Take Exam\n4. View Results\n5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Username: ";
                cin >> username;
                cout << "Enter Password: ";
                cin >> password;
                user.registerUser(username, password);
                break;
            case 2:
                cout << "Enter Username: ";
                cin >> username;
                cout << "Enter Password: ";
                cin >> password;
                if (user.loginUser(username, password)) {
                    cout << "Login successful!\n";
                } else {
                    cout << "Invalid credentials!\n";
                }
                break;
            case 3:
                cout << "Enter Username: ";
                cin >> username;
                cout << "Enter Password: ";
                cin >> password;
                if (user.loginUser(username, password)) {
                    exam.takeExam(username);
                } else {
                    cout << "Invalid credentials! Please login first.\n";
                }
                break;
            case 4:
                exam.displayResults();
                break;
            case 5:
                cout << "Exiting system. Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}
