package name.sburov.graph;

/**
 * Created by ilion on 21.12.2015.
 */
public class VertexAlreadyExistException extends IntegrityGraphException {
    public VertexAlreadyExistException() {
        super("Vertex already exist");
    }

    public VertexAlreadyExistException(VertexIndex index, Graph graph) {
        super("Vertex " + index + " already exist.", graph);
    }
}
