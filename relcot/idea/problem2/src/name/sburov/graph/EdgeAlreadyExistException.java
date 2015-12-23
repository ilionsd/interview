package name.sburov.graph;

/**
 * Created by ilion on 21.12.2015.
 */
public class EdgeAlreadyExistException extends IntegrityGraphException {
    public EdgeAlreadyExistException() {
        super("Edge already exist");
    }

    public EdgeAlreadyExistException(VertexIndex source, VertexIndex destination, Graph graph) {
        super("Edge from " + source + " to " + destination + " already exist.", graph);
    }
}
