#pragma once

#include "INearestNeighborsDegree.h"

namespace graphpp
{
template <class Graph, class Vertex>
class WeightedNearestNeighborsDegree : public INearestNeighborsDegree<Graph, Vertex>
{
public:
    // TODO check if this method is implemented correctly
    virtual double meanDegree(Graph& g, typename Vertex::Degree d)
    {
        auto it = g.verticesIterator();
        unsigned int count = 0;
        double meanDegreeSums = 0.0;

        while (!it.end())
        {
            Vertex* v = *it;

            if (v->degree() == d)
            {
                ++count;
                meanDegreeSums += meanDegreeForVertex(v);
            }

            ++it;
        }

        return count == 0 ? 0 : meanDegreeSums / count;
    }

    virtual double meanDegreeForVertex(Vertex* v)
    {
        auto it = v->neighborsIterator();
        typename Vertex::Weight degreeSum = 0.0;
        while (!it.end())
        {
            Vertex* n = static_cast<Vertex*>(*it);

            degreeSum += n->degree() * v->edgeWeight(n);

            ++it;
        }

        return v->strength() == 0 ? 0 : double(degreeSum) / v->strength();
    }
};
}  // namespace graphpp
