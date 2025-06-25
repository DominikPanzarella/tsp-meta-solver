#pragma once

#include <iostream>

struct Node {
    int id;
    double x;
    double y;
    double z = 0.0;

    Node(int id_, double x_, double y_) : id(id_), x(x_), y(y_), z(0.0) {}

    double distanceTo(const Node& other) const {
        double dx = x - other.x;
        double dy = y - other.y;
        return std::sqrt(dx * dx + dy * dy);
    }
};
