package name.sburov.graph;

import java.util.Map;

/**
 * Created by ilion on 16.12.2015.
 */
public interface Graph {
    int size();

    boolean hasVertex(VertexIndex index);
    boolean hasEdge(VertexIndex source, VertexIndex destination);

    Vertex getVertex(VertexIndex index);
    Map<VertexIndex, ? extends Vertex> getVertices();

}
