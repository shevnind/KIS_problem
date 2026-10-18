#include <iostream>
#include <map>
#include <vector>

using cstr = const std::string;

struct edge {
    std::string u, v;
    double p;
    bool checked = false;
    bool is_broken = false;

    cstr& another_ver(cstr& cur_ver) const {
        if (cur_ver == u) return v;
        else return u;
    }
};

int day_cost;
std::map<std::string, int> cost;
std::map<std::string, bool> used;
std::map<std::string, edge> edges;
std::map<std::string, std::vector<std::string> > g;

void go_to_profitable(cstr& cur_ver, cstr& prev_edge = "-1") {
    used[cur_ver] = true;

    std::cout << "LOOK" << std::endl;
    std::string path, edge_name, next, broken;
    for (int i = 0; i < g[cur_ver].size(); ++i) {
        std::cin >> path >> edge_name >> next >> broken;
        if (used[next]) continue;

        edges[edge_name].checked = true;
        edges[edge_name].is_broken = (broken == "broken");
    }

    std::string res;
    for (cstr& edge_name : g[cur_ver]) {
        const edge& e = edges[edge_name];
        cstr& next_ver = e.another_ver(cur_ver);
        double pred_add = cost[next_ver] - e.is_broken *  day_cost;
        if (used[next_ver] || pred_add < 0) continue;

        if (e.is_broken) {
            std::cout << "CLEAR " << edge_name << std::endl;
            std::cin >> res;
        }
        std::cout << "MOVE " << edge_name << std::endl;
        std::cin >> res;

        go_to_profitable(next_ver, edge_name);

        std::cout << "MOVE " << edge_name << std::endl;
        std::cin >> res;
    }
}

int main() {
    std::cin >> day_cost;
    std::string start;
    std::cin >> start;

    std::string input;
    std::cin >> input;
    while (input == "vertex") {
        std::string ver;
        std::cin >> ver;
        std::cin >> cost[ver];

        std::cin >> input;
    }
    while (input == "edge") {
        std::string name;
        std::cin >> name;
        std::string ver1, ver2;
        double p;
        std::cin >> ver1 >> ver2 >> p;

        edges[name] = edge{ver1, ver2, p};
        g[ver1].push_back(name);
        g[ver2].push_back(name);

        std::cin >> input;
    }

    go_to_profitable(start);
    std::cout << "END" << std::endl;
}

