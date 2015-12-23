package name.sburov.graph;

import java.util.HashMap;

/**
 * Created by ilion on 17.12.2015.
 */
public class LinkGraph {
    public class Edge {
        LinkGraph.Vertex source;
        LinkGraph.Vertex destination;

        Edge(LinkGraph.Vertex source, LinkGraph.Vertex destination) {
            this.source = source;
            this.destination = destination;
        }

        public LinkGraph.Vertex getSource() {
            return source;
        }

        public LinkGraph.Vertex getDestination() {
            return destination;
        }
    }

    public class Vertex {

        LinkGraph graph;
        int index;

        HashMap<Integer, LinkGraph.Edge> incoming = new HashMap<>();
        HashMap<Integer, LinkGraph.Edge> outcoming = new HashMap<>();

        Vertex(LinkGraph graph, int index) {
            this.graph = graph;
            this.index = index;
        }

        boolean addEdge(LinkGraph.Vertex destination) {
            if (outcoming.containsKey(destination.getIndex()))
                return false;
            LinkGraph.Edge e = new LinkGraph.Edge(this, destination);
            outcoming.put(e.getDestination().getIndex(), e);
            destination.incoming.put(e.getSource().getIndex(), e);
            return true;
        }

        boolean hasOutcomingEdge(LinkGraph.Vertex destination) {
            return outcoming.containsKey(destination.getIndex());
        }

        boolean hasIncomingEdge(LinkGraph.Vertex destination) {
            return incoming.containsKey(destination.getIndex());
        }

        public LinkGraph getGraph() {
            return graph;
        }

        public int getIndex() {
            return index;
        }

        public HashMap<Integer, LinkGraph.Edge> getIncoming() {
            return incoming;
        }

        public HashMap<Integer, LinkGraph.Edge> getOutcoming() {
            return outcoming;
        }
    }

    private int vertexIncrement = 0;

    HashMap<Integer, LinkGraph.Vertex> vertices = new HashMap<>();

    public LinkGraph(){ }

    public LinkGraph.Vertex getVertex(int index) {
        return vertices.get(index);
    }

    public int size() {
        return vertices.size();
    }

    private int getNextVertexIndex() {
        int tryVertexIncrement;
        do {
            tryVertexIncrement = vertexIncrement++;
        } while (!vertices.containsKey(tryVertexIncrement));
        return tryVertexIncrement;
    }

    public LinkGraph addEdge(int source, int destination) {
        getVertex(source).addEdge(getVertex(destination));
        return this;
    }

    public LinkGraph addVertex() {
        LinkGraph.Vertex v = new LinkGraph.Vertex(this, getNextVertexIndex());
        vertices.put(v.getIndex(), v);
        return this;
    }

    public boolean removeEdge(int source, int destination) {

        return false;
    }

    public boolean removeVertex(int index) {
        return false;
    }
}
