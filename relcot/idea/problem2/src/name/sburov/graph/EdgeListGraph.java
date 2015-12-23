package name.sburov.graph;

import name.sburov.util.MapUtils;

import java.util.*;
import java.util.stream.Collectors;

/**
 * Created by ilion on 21.12.2015.
 */
public class EdgeListGraph implements Graph {

    public class EdgeListEdge implements Edge {

        private EdgeListGraph graph;

        private VertexIndex source;
        private VertexIndex destination;

        protected EdgeListEdge(VertexIndex source, VertexIndex destination, EdgeListGraph graph) {
            this.source = source;
            this.destination = destination;
            this.graph = graph;
        }

        @Override
        public EdgeListGraph getGraph() {
            return graph;
        }

        @Override
        public VertexIndex src() {
            return source;
        }

        @Override
        public VertexIndex dst() {
            return destination;
        }

        @Override
        public double getWeight() {
            return 1.0;
        }
    }

    public class EdgeListVertex implements Vertex {
        private EdgeListGraph graph;
        private VertexIndex index;
        private Set<VertexIndex> ingoingEdges = new HashSet<>();
        private Set<VertexIndex> outgoingEdges = new HashSet<>();

        protected EdgeListVertex(VertexIndex index, EdgeListGraph graph) {
            this.index = index;
            this.graph = graph;
        }

        protected EdgeListVertex addIngoingEdge(VertexIndex source) {
            ingoingEdges.add(source);
            return this;
        }

        protected EdgeListVertex addAllIngoingEdges(Set<VertexIndex> sources) {
            ingoingEdges.addAll(sources);
            return this;
        }

        protected EdgeListVertex addOutgoingEdge(VertexIndex destination) {
            outgoingEdges.add(destination);
            return this;
        }

        protected EdgeListVertex addAllOutgoingEdges(Set<VertexIndex> destimations) {
            outgoingEdges.addAll(destimations);
            return this;
        }

        @Override
        public EdgeListGraph getGraph() {
            return graph;
        }

        @Override
        public VertexIndex getIndex() {
            return index;
        }

        @Override
        public boolean hasIngoingEdge(VertexIndex index) {
            return ingoingEdges.contains(index);
        }

        @Override
        public boolean hasOutgoingEdge(VertexIndex index) {
            return outgoingEdges.contains(index);
        }

        public List<EdgeListEdge> getIngoingEdges() {
            return ingoingEdges.stream().map(incoming -> new EdgeListEdge(incoming, getIndex(), getGraph())).collect(Collectors.toList());
        }

        public List<EdgeListEdge> getOutgoingEdges() {
            return outgoingEdges.stream().map(outcoming -> new EdgeListEdge(getIndex(), outcoming, getGraph())).collect(Collectors.toList());
        }
    }




    private Map<VertexIndex, Set<VertexIndex>> edgeList = null;

    public EdgeListGraph() {
        edgeList = new HashMap<>();
    }

    @Override
    public EdgeListVertex getVertex(VertexIndex index) {
        if (!hasVertex(index))
            throw new VertexNotExistException(index, this);
        Set<VertexIndex> incomingEdges = new HashSet<>();
        for (Map.Entry<VertexIndex, Set<VertexIndex>> entry : edgeList.entrySet()) {
            if (entry.getValue().contains(index))
                incomingEdges.add(index);
        }
        EdgeListVertex v = new EdgeListVertex(index, this)
                .addAllIngoingEdges(incomingEdges)
                .addAllOutgoingEdges(edgeList.get(index));
        return v;
    }

    @Override
    public Map<VertexIndex, EdgeListVertex> getVertices() {
        Map<VertexIndex, EdgeListVertex> vertices = MapUtils.createMap(edgeList.keySet(), index -> new EdgeListVertex(index, this));

        try {
            for (Map.Entry<VertexIndex, Set<VertexIndex>> entry : edgeList.entrySet()) {
                VertexIndex source = entry.getKey();
                for (VertexIndex destination : entry.getValue()) {
                    vertices.get(source).addOutgoingEdge(destination);
                    vertices.get(destination).addIngoingEdge(source);
                }
            }
        }
        catch (NullPointerException e) {
            throw new IntegrityGraphException(this, e);
        }

        return vertices;
    }

    @Override
    public int size() {
        return edgeList.size();
    }

    @Override
    public boolean hasVertex(VertexIndex index) {
        return edgeList.containsKey(index);
    }

    @Override
    public boolean hasEdge(VertexIndex source, VertexIndex destination) {
        return hasVertex(source) && hasVertex(destination) && edgeList.get(source).contains(destination);
    }

    public EdgeListGraph addVertex(VertexIndex index) {
        if (hasVertex(index))
            throw new VertexAlreadyExistException(index, this);
        edgeList.put(index, new HashSet<>());
        return this;
    }

    public EdgeListGraph addEdge(VertexIndex source, VertexIndex destination) {
        if (!hasVertex(source))
            throw new VertexNotExistException(source, this);
        if (!hasVertex(destination))
            throw new VertexNotExistException(destination, this);
        if (hasEdge(source, destination))
            throw new EdgeAlreadyExistException(source, destination, this);
        edgeList.get(source).add(destination);
        return this;
    }

    public EdgeListGraph removeVertex(VertexIndex index) {
        if (!hasVertex(index))
            throw new VertexNotExistException(index, this);
        for (Map.Entry<VertexIndex, Set<VertexIndex>> entry : edgeList.entrySet()) {
            if (entry.getValue().contains(index))
                entry.getValue().remove(index);
        }
        edgeList.remove(index);
        return this;
    }

    public EdgeListGraph removeEdge(VertexIndex source, VertexIndex destination) {
        if (!hasEdge(source, destination))
            throw new EdgeNotExistException(source, destination, this);
        edgeList.get(source).remove(destination);
        return this;
    }
}
