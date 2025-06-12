#include <iostream>
#include <climits>   // For INT_MAX
#include <string>
#include <fstream>
#include <sstream>
#include <map>

const int MAX_SIZE = 100; // Maximum number of vertices allowed

// Graph class using adjacency matrix
class Graph {
private:
    int adj_matrix[MAX_SIZE][MAX_SIZE];      // 2D matrix to hold edge weights
    std::string vertex_data[MAX_SIZE];       // Maps vertex index to a name (e.g., 0 -> "A")
    int size;                  
    int cycle[MAX_SIZE];        // Number of vertices in the graph

public:
    // Constructor initializes graph with given size
    Graph(int sz) {
        size = sz;
        for (int i = 0; i < size; ++i) {
            vertex_data[i] = ""; // Initialize vertex labels to empty strings
            for (int j = 0; j < size; ++j) {
                adj_matrix[i][j] = 0; // No edge between i and j initially
            }
        }
    }

    // Add an undirected edge with weight between u and v
    void add_edge(int u, int v, int weight) {
        if (u >= 0 && u < size && v >= 0 && v < size) {
            adj_matrix[u][v] = weight;
            adj_matrix[v][u] = weight; // Undirected: mirror the edge
        }
    }

    // Associate a label (like "A", "B") to a vertex index
    void add_vertex_data(int vertex, const std::string& data, const int cycleTime) {
        if (vertex >= 0 && vertex < size) {
            vertex_data[vertex] = data;
            cycle[vertex] = cycleTime;
        }
    }

    // Utility: Get index by vertex label (e.g., "A" -> 0)
    int get_index_by_label(const std::string& label) {
        for (int i = 0; i < size; ++i) {
            if (vertex_data[i] == label) return i;
        }
        return -1; // Label not found
    }

    // Dijkstra’s algorithm: find shortest distances from start vertex
    void dijkstra(const std::string& start_vertex_data, const std::string& end_vertex_data, std::ostream& out){
        int start = get_index_by_label(start_vertex_data);
        if (start == -1) {
            std::cout << "Invalid start vertex.\n";
            return;
        }

        int dist[MAX_SIZE];         // Distance from start to each vertex
        bool visited[MAX_SIZE];     // Whether shortest distance to vertex is finalized
        int parent[MAX_SIZE];       // To reconstruct the shortest path

        // Initialize arrays
        for (int i = 0; i < size; ++i) {
            dist[i] = INT_MAX;
            visited[i] = false;
            parent[i] = -1;
        }

        dist[start] = 0;

        // Dijkstra loop
        for (int count = 0; count < size - 1; ++count) {
            int min_dist = INT_MAX, u = -1;

            // Select the unvisited node with the smallest distance
            for (int i = 0; i < size; ++i) {
                if (!visited[i] && dist[i] < min_dist) {
                    min_dist = dist[i];
                    u = i;
                }
            }

            if (u == -1) break;

            visited[u] = true;

            for (int v = 0; v < size; ++v) {
                if (!visited[v] && adj_matrix[u][v] > 0 && dist[u] != INT_MAX) {
                    int arrivalTime = dist[u] + adj_matrix[u][v];
                    int waitTime = (arrivalTime % cycle[v] == 0) ? 0 : (cycle[v] - (arrivalTime % cycle[v]));
                    int totalTime = arrivalTime + waitTime;

                    if (totalTime < dist[v]) {
                        dist[v] = totalTime;
                        parent[v] = u;
                    }
                }
            }
        }

        // Print shortest distances from start
        std::cout << "Shortest distances from " << start_vertex_data << ":\n";
        for (int i = 0; i < size; ++i) {
            std::cout << vertex_data[i] << ": ";
            if (dist[i] == INT_MAX)
                std::cout << "INF\n";
            else
                std::cout << dist[i] << "\n";
        }

        // Find goal vertex
        int goal = get_index_by_label(end_vertex_data);
        if (goal == -1 || dist[goal] == INT_MAX) {
            out << "INF\nNo path\n";
            std::cout << "INF\nNo path\n";
            return;
        }

        // Reconstruct path from goal to start
        std::string path = vertex_data[goal];
        std::string path_only[MAX_SIZE];
        int path_len = 0;

        path_only[path_len++] = vertex_data[goal];
        for (int v = parent[goal]; v != -1; v = parent[v]) {
            path_only[path_len++] = vertex_data[v];
        }

        // Output total time
        out << dist[goal] << "\n";
        std::cout << dist[goal] << "\n";

        // Output path from start to goal (in correct order)
        for (int i = path_len - 1; i >= 0; --i) {
            out << path_only[i];
            std::cout << path_only[i];
            if (i > 0) {
                out << " ";
                std::cout << " ";
            }
        }
        out << "\n";
        std::cout << "\n";

    }
};


// Manually remove all whitespace characters from a string (in-place)
void strip_whitespace(std::string& s) {
    std::string result = "";
    for (char c : s) {
        if (!isspace(c)) {
            result += c;
        }
    }
    s = result;
}

void processGraphsFromFile(const std::string& filename, const std::string& outputFile) {
    std::ifstream infile(filename);
    std::ofstream outfile(outputFile);

    if (!infile.is_open() || !outfile.is_open()) {
        std::cerr << "Failed to open input or output file.\n";
        return;
    }

    int numGraphs;
    infile >> numGraphs;
    std::string line;
    std::getline(infile, line); // Consume newline

    for (int g = 0; g < numGraphs; ++g) {
        std::getline(infile, line);
        while (line.empty()) std::getline(infile, line);
        int n = std::stoi(line);

        Graph graph(n);
        std::map<std::string, int> labelToIndex;

        for (int i = 0; i < n; ++i) {
            std::getline(infile, line);
            std::stringstream ss(line);
            std::string label;
            int cycle;
            std::getline(ss, label, ',');
            ss >> cycle;
            strip_whitespace(label);
            labelToIndex[label] = i;
            graph.add_vertex_data(i, label, cycle);
        }

        while (std::getline(infile, line)) {
            if (line.empty()) continue;
            size_t pos = line.find_first_not_of(" \t");
            if (pos != std::string::npos && isdigit(line[pos])) {
                infile.seekg(-(line.length() + 1), std::ios_base::cur);
                break;
            }

            std::stringstream ss(line);
            std::string u_str, v_str;
            int weight;
            std::getline(ss, u_str, ',');
            std::getline(ss, v_str, ',');
            ss >> weight;
            strip_whitespace(u_str);
            strip_whitespace(v_str);

            int u = labelToIndex[u_str];
            int v = labelToIndex[v_str];

            graph.add_edge(u, v, weight);
        }

        graph.dijkstra("A", "G", outfile);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " input_file output_file\n";
        return 1;
    }

    std::string inputFile = argv[1];
    std::string outputFile = argv[2];

    processGraphsFromFile(inputFile, outputFile);
    return 0;
}
