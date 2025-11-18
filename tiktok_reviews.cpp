#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

const int MAX_REVIEWS = 500;

// Arrays to store review data
string trends[MAX_REVIEWS];
int ratings[MAX_REVIEWS];
string reviewers[MAX_REVIEWS];
int reviewCount = 0;

// Convert string to lowercase for case-insensitive comparison
string toLower(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

// Load reviews from file
void loadReviews() {
    ifstream file("tiktok_reviews.txt");

    if (!file.is_open()) {
        cout << "No previous database found. Starting fresh.\n";
        return;
    }

    while (file >> ws && !file.eof()) {
        string trend;
        int rating;
        string reviewer;

        file >> trend >> rating >> reviewer;
        if (!file.fail() && reviewCount < MAX_REVIEWS) {
            trends[reviewCount] = trend;
            ratings[reviewCount] = rating;
            reviewers[reviewCount] = reviewer;
            reviewCount++;
        }
    }

    file.close();
}

// Display all reviews
void viewAllReviews() {
    if (reviewCount == 0) {
        cout << "No reviews found.\n";
        return;
    }

    cout << left << setw(20) << "TikTok Trend"
         << setw(10) << "Rating"
         << setw(15) << "Reviewer" << endl;

    cout << "---------------------------------------------\n";

    for (int i = 0; i < reviewCount; i++) {
        cout << left << setw(20) << trends[i]
             << setw(10) << ratings[i]
             << setw(15) << reviewers[i]
             << endl;
    }
}

// Search for a trend/influencer
void searchReview() {
    cout << "Enter trend name: ";
    string searchTrend;
    cin >> searchTrend;

    string searchLower = toLower(searchTrend);

    for (int i = 0; i < reviewCount; i++) {
        if (toLower(trends[i]) == searchLower) {
            cout << "Trend: " << trends[i]
                 << ", Rating: " << ratings[i]
                 << ", Reviewed by: " << reviewers[i] << endl;
            return;
        }
    }

    cout << "No review found for that trend/influencer.\n";
}

// Add a new review
void addReview() {
    if (reviewCount >= MAX_REVIEWS) {
        cout << "Database full. Cannot add more reviews.\n";
        return;
    }

    string trend, reviewer;
    int rating;

    cout << "Enter trend/influencer name: ";
    cin >> trend;

    cout << "Enter rating (1-10): ";
    cin >> rating;

    cout << "Enter reviewer name: ";
    cin >> reviewer;

    trends[reviewCount] = trend;
    ratings[reviewCount] = rating;
    reviewers[reviewCount] = reviewer;
    reviewCount++;

    // Append to file
    ofstream file("tiktok_reviews.txt", ios::app);
    file << trend << " " << rating << " " << reviewer << "\n";
    file.close();

    cout << "Review added successfully!\n";
}

int main() {
    loadReviews();

    int choice;

    while (true) {
        cout << "\nWelcome to the TikTok Review Database\n";
        cout << "1. View All Reviews\n";
        cout << "2. Search for a Trend/Influencer\n";
        cout << "3. Add a New Review\n";
        cout << "4. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        cout << "\n";

        switch (choice) {
            case 1:
                viewAllReviews();
                break;
            case 2:
                searchReview();
                break;
            case 3:
                addReview();
                break;
            case 4:
                cout << "Goodbye!\n";
                return 0;
            default:
                cout << "Invalid option. Try again.\n";
        }
    }

    return 0;
}


