package name.sburov.graph.algorithms.search;


import name.sburov.graph.Edge;
import name.sburov.util.MapUtils;
import name.sburov.graph.Vertex;
import name.sburov.graph.VertexIndex;

import java.util.*;

/**
 * Created by ilion on 16.12.2015.
 */
public class WideSearch {

    private Map<VertexIndex, ? extends Vertex> vertices = null;

    public WideSearch(){}

    public Map<VertexIndex, ? extends Vertex> getVertices() {
        return vertices;
    }

    public WideSearch setVertices(Map<VertexIndex, ? extends Vertex> vertices) {
        this.vertices = vertices;
        return this;
    }

    public SearchResult search(VertexIndex source) {
        return search(source, VertexIndex.UNDEFINED_INDEX);
    }

    public SearchResult search(VertexIndex source, VertexIndex destination) {
        Objects.requireNonNull(vertices);
        if (!vertices.containsKey(source))
            throw new IllegalArgumentException("Can not find key " + source + " in " + vertices.toString());

        Map<VertexIndex, CostEntry> route = MapUtils.createMap(vertices.keySet(), CostEntry.Unreachable());
        route.put(source, CostEntry.Source());

        Map<VertexIndex, Boolean> used = MapUtils.createMap(vertices.keySet(), false);
        VertexIndex key = source;

        do {
            used.put(key, true);
            Vertex v = vertices.get(key);
            for (Edge e : v.getOutgoingEdges()) {
                double cost = route.get(key).getCost() + e.getWeight();
                if (route.get(e.dst()).compareTo(cost) > 0)
                    route.put(e.dst(), new CostEntry(cost, key));
            }
            double minCost = CostEntry.UNREACHEBLE_COST;
            VertexIndex minCostKey = VertexIndex.UNDEFINED_INDEX;
            for (Map.Entry<VertexIndex, CostEntry> entry : route.entrySet()) {
                if (!used.get(entry.getKey()) && entry.getValue().compareTo(minCost) < 0) {
                    minCost = entry.getValue().getCost();
                    minCostKey = entry.getKey();
                }
            }
            key = minCostKey;
        }
        while (VertexIndex.compare(key, destination) != 0);

        SearchResult.Builder builder = SearchResult.newBuilder()
                .setSource(source)
                .setRoute(route);

        return builder.build();
    }
}
