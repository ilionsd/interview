package name.sburov.graph;

/**
 * Created by ilion on 21.12.2015.
 */
public interface Edge {
    Graph getGraph();

    VertexIndex src();
    VertexIndex dst();

    double getWeight();
}
