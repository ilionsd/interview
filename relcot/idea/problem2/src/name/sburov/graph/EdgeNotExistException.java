package name.sburov.graph;

/**
 * Created by ilion on 21.12.2015.
 */
public class EdgeNotExistException extends IntegrityGraphException {
    public EdgeNotExistException() {
        super("Edge does not exist");
    }

    public EdgeNotExistException(VertexIndex source, VertexIndex destination, Graph graph) {
        super("Edge from " + source + " to " + destination + " does not exist.", graph);
    }
}
