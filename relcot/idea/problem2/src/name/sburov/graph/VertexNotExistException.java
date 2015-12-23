package name.sburov.graph;

/**
 * Created by ilion on 21.12.2015.
 */
public class VertexNotExistException extends IntegrityGraphException {
    public VertexNotExistException() {
        super("Vertex does not exist");
    }

    public VertexNotExistException(VertexIndex index, Graph graph) {
        super("Vertex " + index + " does not exist.", graph);
    }
}
