#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <cstdlib> // For system()
#include <windows.h> // For Windows API directory operations
#include <locale> // For ctype functions
#include<stack>
#include<queue>
using namespace std;

// Represents a web page
class WebPage {
public:
    string url;
    string content;
    string filePath;
    vector<string> outgoingLinks; // Store outgoing links


    WebPage(string u, string c, string fp) : url(u), content(c), filePath(fp) {}
    vector<string> getOutgoingLinks() {
        return outgoingLinks;
    }

};

// Inverted index for efficient searching
class InvertedIndex {
private:
    unordered_map<string, unordered_set<string>> index; // Map from token to set of filenames
    unordered_map<string, unordered_map<string, int>> tf; // Term Frequency
    unordered_map<string, int> df; // Document Frequency

public:
    void addPage(const string& filePath, const vector<string>& tokens) {
        // Stop words
        vector<string> stopWords = { "a", "an", "and", "are", "as", "at", "be", "by", "for", "from", "has", "he", "in", "is", "it", "its", "of", "on", "that", "the", "to", "was", "were", "will", "with" };
        unordered_set<string> uniqueTokens(tokens.begin(), tokens.end());
        for (const string& token : uniqueTokens) {
            if (find(stopWords.begin(), stopWords.end(), token) != stopWords.end()) {
                continue;
            }
            index[token].insert(filePath);
        }
        for (const string& token : tokens) {
            tf[filePath][token]++; // Update term frequency
        }
        for (const string& token : uniqueTokens) {
            df[token]++; // Update document frequency
        }
    }

    unordered_set<string> search(const string& token) const {
        if (index.find(token) != index.end()) {
            return index.at(token);
        }
        return unordered_set<string>();
    }

    double calculateTFIDF(const string& filePath, const string& token, size_t totalDocs) const {
        double tfValue = 0.0;
        double idfValue = 0.0;
        if (tf.find(filePath) != tf.end() && tf.at(filePath).find(token) != tf.at(filePath).end()) {
            tfValue = static_cast<double>(tf.at(filePath).at(token));
        }
        if (df.find(token) != df.end()) {
            idfValue = log(static_cast<double>(totalDocs) / static_cast<double>(df.at(token)));
        }
        return tfValue * idfValue;
    }
};

// Basic search engine with TF-IDF ranking and Boolean queries
class SearchEngine {
private:
    stack<string>forwardstack;
    stack<string>backstack;
    vector<WebPage> pages;
    InvertedIndex index;
    vector<pair<string, string>> history;
    // Maintain cache for the search results
    unordered_map<string, vector<string>> cache;
    unordered_map<string, vector<string>> graph;

    // Tokenize query into individual words
    vector<string> tokenizeQuery(const string& query) {
        vector<string> tokens;
        // Stop words
        vector<string> stopWords = { "a", "an", "and", "are", "as", "at", "be", "by", "for", "from", "has", "he", "in", "is", "it", "its", "of", "on", "that", "the", "to", "was", "were", "will", "with" };
        stringstream ss(query);
        string token;

        while (ss >> token) {
            // Check if the token is a boolean operator
            if (token != "AND" && token != "OR") {
                // Convert token to lowercase
                transform(token.begin(), token.end(), token.begin(), [](unsigned char c) { return tolower(c); });
            }

            if (!tokens.empty() && tokens.back() == "\"") {
                while (!token.empty() && ispunct(static_cast<unsigned char>(token.back()))) {
                    token.pop_back();
                }
            }

            // Remove trailing punctuation from tokens
            while (!token.empty() && ispunct(static_cast<unsigned char>(token.back()))) {
                token.pop_back();
            }
            // Remove leading punctuation from tokens
            while (!token.empty() && ispunct(static_cast<unsigned char>(token.front()))) {
                token.erase(0, 1);
            }
            // Remove double quotes from tokens
            if (!token.empty() && token.front() == '\"') {
                token.erase(0, 1);
            }
            if (!token.empty() && token.back() == '\"') {
                token.pop_back();
            }

            if (!token.empty() && find(stopWords.begin(), stopWords.end(), token) == stopWords.end()) {
                tokens.push_back(token);
            }
        }
        return tokens;
    }
  


public:
    void addPage(const WebPage& page) {
        pages.push_back(page);
        ifstream file(page.filePath);
        string line;
        string content;
        while (getline(file, line)) {
            content += line + "\n";
        }
        index.addPage(page.filePath, tokenizeQuery(content)); // Tokenize the content
        file.close();
    }

    vector<string> search(const string& query) {
        history.push_back({ getCurrentTimestamp(), query });
        // If it's a file path, simply open the file
        if (query.size() > 4 && query.substr(query.size() - 4) == ".txt") {
            openFile(query);
            return {};
        }

        if (cache.find(query) != cache.end()) {
            return cache[query];
        }
        auto queryTokens = tokenizeQuery(query); // Tokenize the query

        unordered_set<string> filenames;
        if (find(queryTokens.begin(), queryTokens.end(), "AND") != queryTokens.end() ||
            find(queryTokens.begin(), queryTokens.end(), "OR") != queryTokens.end()) {
            filenames = processBooleanQuery(queryTokens);
        }
        else {
            for (const auto& token : queryTokens) {
                auto result = index.search(token);
                filenames.insert(result.begin(), result.end());
            }
        }

        // Calculate TF-IDF scores for each file and rank them
        vector<pair<string, double>> rankedResults;
        size_t totalDocs = pages.size();
        for (const auto& filename : filenames) {
            double score = 0.0;
            for (const auto& token : queryTokens) {
                score += index.calculateTFIDF(filename, token, totalDocs);
            }
            rankedResults.emplace_back(filename, score);
        }

        // Sort results by TF-IDF score in descending order
        sort(rankedResults.begin(), rankedResults.end(), [](const pair<string, double>& a, const pair<string, double>& b) {
            return a.second > b.second;
            });

        // Collect sorted results
        vector<string> results;
        for (const auto& rankedResult : rankedResults) {
            results.push_back(rankedResult.first);
        }
        // Store the results in cache
        cache[query] = results;
        return results;
    }

    unordered_set<string> processBooleanQuery(const vector<string>& queryTokens) {
        unordered_set<string> result;
        bool prevAnd = false;
        bool firstToken = true;

        for (const auto& token : queryTokens) {
            if (token == "AND" || token == "OR") {
                prevAnd = (token == "AND");
            }
            else {
                auto tempSet = index.search(token);

                if (firstToken) {
                    result = tempSet;
                }
                else {
                    if (prevAnd) {
                        // Convert unordered_set to vector
                        vector<string> resultVec(result.begin(), result.end());
                        vector<string> tempVec(tempSet.begin(), tempSet.end());
                        // Sort the vectors
                        sort(resultVec.begin(), resultVec.end());
                        sort(tempVec.begin(), tempVec.end());
                        // Perform intersection
                        vector<string> intersection;
                        set_intersection(resultVec.begin(), resultVec.end(), tempVec.begin(), tempVec.end(),
                            back_inserter(intersection));
                        result = unordered_set<string>(intersection.begin(), intersection.end());
                    }
                    else {
                        // Convert unordered_set to vector
                        vector<string> resultVec(result.begin(), result.end());
                        vector<string> tempVec(tempSet.begin(), tempSet.end());
                        // Sort the vectors
                        sort(resultVec.begin(), resultVec.end());
                        sort(tempVec.begin(), tempVec.end());
                        // Perform union
                        vector<string> unionVec;
                        set_union(resultVec.begin(), resultVec.end(), tempVec.begin(), tempVec.end(),
                            back_inserter(unionVec));
                        result = unordered_set<string>(unionVec.begin(), unionVec.end());
                    }
                }
                firstToken = false;
            }
        }

        return result;
    }

    // Save search history to file with timestamps
    void saveHistoryToFile() {
        ofstream outFile("search_history.txt");
        if (outFile.is_open()) {
            for (const auto& entry : history) {
                outFile << entry.first << " - " << entry.second << endl;
            }
            outFile.close();
            //cout << "Search history saved to file: " << filename << endl;
        }
        else {
            //cerr << "Error: Unable to open file for writing: " << filename << endl;
        }
    }

    // Retrieve search history from file
    vector<string> loadHistoryFromFile() {
        vector<string> historyLines;
        ifstream inFile("search_history.txt");
        if (inFile.is_open()) {
            string line;
            while (getline(inFile, line)) {
                historyLines.push_back(line);
            }
            inFile.close();
            return historyLines;
        }
        else {
            cerr << "Error: Unable to open file for reading: " << endl;
        }
    }

    void clearHistory() {
        history.clear();
        // Clear history from file
        ofstream outFile("search_history.txt");
        outFile.close();
    }

    // Get current timestamp as string
    string getCurrentTimestamp() {
        auto now = chrono::system_clock::now();
        auto now_c = chrono::system_clock::to_time_t(now);
        tm local_tm;

        #ifdef _WIN32
                localtime_s(&local_tm, &now_c); // Use localtime_s on Windows
        #else
                localtime_r(&now_c, &local_tm); // Use localtime_r on Unix-like systems
        #endif

        stringstream ss;
        ss << put_time(&local_tm, "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }

    // Open file based on the file path
    void openFile(const string& filePath) {
        string command = "start " + filePath; // For Windows
        if (system(command.c_str()) != 0) {
            cerr << "Error: Unable to open file: " << filePath << endl;
        }
    }
    void maintainbackstack(string query) {
        backstack.push(query);
    }
    void maintainforstack(string q) {
        forwardstack.push(q);
    }
    string displaybackstack() {
        string b = backstack.top();
        backstack.pop();
        return b;
    }
    string displayfrontstack() {
        string b = forwardstack.top();
        forwardstack.pop();
        return b;
    }
   

    void workofmain() {
        WIN32_FIND_DATA findFileData;
        HANDLE hFind = FindFirstFile(L"data\\*", &findFileData); // Use wide character strings
        

        if (hFind != INVALID_HANDLE_VALUE) {
            do {
                wstring fileOrDir = findFileData.cFileName; // Use wstring for wide character strings
                wstring fullPath = L"data\\" + fileOrDir; // Combine directory and file name

                if (fileOrDir != L"." && fileOrDir != L"..") {
                    // Process the file here
                    addPage(WebPage("", "", string(fullPath.begin(), fullPath.end())));
                   
                }
               
            } while (FindNextFile(hFind, &findFileData) != 0);
            FindClose(hFind);
        }
        else {
            cerr << "Error: Unable to open directory: data\\*" << endl;
             // Exit with error code
        }
    }
};
