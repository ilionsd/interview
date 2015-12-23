package name.sburov.graph;

import java.util.List;

/**
 * Created by ilion on 21.12.2015.
 */
public interface Vertex {
    Graph getGraph();
    VertexIndex getIndex();

    boolean hasIngoingEdge(VertexIndex index);
    boolean hasOutgoingEdge(VertexIndex index);

    List<? extends Edge> getIngoingEdges();
    List<? extends Edge> getOutgoingEdges();
}
