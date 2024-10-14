/*-------------------------------------------
Program 6: Graphs
Course: CS 141, Fall 2022, UIC
System: C++ on Replit
Author: Hiba Mirza
------------------------------------------- */

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

class Node {
public:
    int value;
    Node* next;
    Node(int v) : value(v), next(nullptr){}
};

class LinkedList{
public:
    Node* head;
    LinkedList() : head(nullptr) {}
    void insert(int value){
        Node* new_node = new Node(value);
        new_node->next = head;
        head = new_node;
    }
};

void read_graph(const string& filename, vector<LinkedList*>& adjacency_list, int& num_nodes, int& num_edges, int& max_degree) {
    ifstream input(filename);

    string line;
    while (getline(input, line)) {
        int from, to;
        stringstream ss(line);
        ss >> from >> to;

        int max_length = max(from, to) + 1;
        if (adjacency_list.size() < max_length) {
            adjacency_list.resize(max_length, nullptr);
        }
        
        if (adjacency_list[from] == nullptr) {
            adjacency_list[from] = new LinkedList;
            num_nodes++;
        }
        if (adjacency_list[to] == nullptr) {
            adjacency_list[to] = new LinkedList;
            num_nodes++;
        }

        bool duplicate = false;
        for (Node* ptr = adjacency_list[from]->head; ptr != nullptr; ptr = ptr->next) {
            if (ptr->value == to) {
                duplicate = true;
                break;
            }
        }

        if (!duplicate) {
            adjacency_list[from]->insert(to);
            adjacency_list[to]->insert(from);
            num_edges++;
        }
    }

    input.close();

    max_degree = 0;
    for (auto list : adjacency_list) {
        if (list != nullptr) {
            vector<int> nodes;
            int degree = 0;
            for (Node* ptr = list->head; ptr != nullptr; ptr = ptr->next) {
                nodes.push_back(ptr->value);
                degree++;
            }
            max_degree = max(max_degree, degree);
            sort(nodes.begin(), nodes.end());
            cout << list->head->value << ": ";
            for (auto node : nodes) {
                cout << node << " ";
            }
            cout << endl;
        }
    }

    for (LinkedList* list : adjacency_list) {
        if (list != nullptr) {
            Node* current = list->head;
            while (current != nullptr) {
                Node* next = current->next;
                delete current;
                current = next;
            }
            delete list;
        }
    }
}

void run(const string& src_path, const string& dst_path) {
    vector<LinkedList*> adjacency_list(1000, nullptr);
    int num_nodes = 0, num_edges = 0, max_degree = 0;
    read_graph(src_path, adjacency_list, num_nodes, num_edges, max_degree);

    ofstream output(dst_path);

    output << "Number of nodes: " << num_nodes << endl;
    output << "Number of edges: " << num_edges << endl;
    output << "Maximum degree: " << max_degree << endl;
    output.close();

    cout << "Number of nodes: " << num_nodes << endl;
    cout << "Number of edges: " << num_edges << endl;
    cout << "Maximum degree: " << max_degree << endl;
}

int main() {
    run("karate.txt", "toy.txt");
    return 0;
}