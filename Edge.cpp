#include "Edge.hpp"

/*
 * Compares this Edge to another Edge. Suitable for
 * use with a priority queue where Edges with the lowest
 * weight have the highest priority.
 */
bool Edge::operator<(const Edge &right) const{
    return (this->cost > right.cost);
}