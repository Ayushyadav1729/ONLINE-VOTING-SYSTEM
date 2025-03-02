#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

// Structure to store candidate details
struct Candidate {
    int id;
    string name;
    int votes = 0;
};

// Function prototypes
void registerVoter(vector<string>& voters, string voterID);
bool checkVoterEligibility(const vector<string>& voters, const string& voterID);
void vote(vector<Candidate>& candidates, int candidateID);
void displayResults(const vector<Candidate>& candidates);

int main() {
    vector<string> registeredVoters;
    vector<string> votersWhoVoted;
    vector<Candidate> candidates = {
        {1, "Candidate A"},
        {2, "Candidate B"},
        {3, "Candidate C"},
        {4, "Candidate D"},
        {5, "Candidate E"}
    };

    int choice;
    string voterID;
    do {
        cout << "\n--- Online Voting System ---\n";
        cout << "1. Register as a Voter\n";
        cout << "2. Cast Vote\n";
        cout << "3. Display Results\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "Enter your Voter ID: ";
                cin >> voterID;
                registerVoter(registeredVoters, voterID);
                break;
            }
            case 2: {
                cout << "Enter your Voter ID: ";
                cin >> voterID;
                if (find(votersWhoVoted.begin(), votersWhoVoted.end(), voterID) != votersWhoVoted.end()) {
                    cout << "You have already voted!\n";
                    break;
                }
                if (!checkVoterEligibility(registeredVoters, voterID)) {
                    cout << "You are not registered. Please register first.\n";
                    break;
                }
                cout << "\nAvailable Candidates:\n";
                for (const auto& candidate : candidates) {
                    cout << candidate.id << ". " << candidate.name << "\n";
                }
                int candidateID;
                cout << "Enter the Candidate ID to vote for: ";
                cin >> candidateID;
                vote(candidates, candidateID);
                votersWhoVoted.push_back(voterID);
                break;
            }
            case 3:
                displayResults(candidates);
                break;
            case 4:
                cout << "Thank you for using the Online Voting System.\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}

// Function to register a voter
void registerVoter(vector<string>& voters, string voterID) {
    if (find(voters.begin(), voters.end(), voterID) != voters.end()) {
        cout << "Voter ID already registered!\n";
        return;
    }
    voters.push_back(voterID);
    cout << "Voter registered successfully!\n";
}

// Function to check voter eligibility
bool checkVoterEligibility(const vector<string>& voters, const string& voterID) {
    return find(voters.begin(), voters.end(), voterID) != voters.end();
}

// Function to cast a vote
void vote(vector<Candidate>& candidates, int candidateID) {
    auto it = find_if(candidates.begin(), candidates.end(),
                      [candidateID](const Candidate& c) { return c.id == candidateID; });
    if (it != candidates.end()) {
        it->votes++;
        cout << "Vote cast successfully for " << it->name << "!\n";
    } else {
        cout << "Invalid Candidate ID. Please try again.\n";
    }
}

// Function to display results
void displayResults(const vector<Candidate>& candidates) {
    cout << "\n--- Election Results ---\n";
    for (const auto& candidate : candidates) {
        cout << candidate.name << ": " << candidate.votes << " votes\n";
    }
}