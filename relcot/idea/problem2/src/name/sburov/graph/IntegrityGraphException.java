package name.sburov.graph;

/**
 * Created by ilion on 21.12.2015.
 */
public class IntegrityGraphException extends RuntimeException {

    public IntegrityGraphException() {
        super("Integrity exception");
    }

    public IntegrityGraphException(Graph graph) {
        super("Integrity exception in graph " + graph.toString());
    }

    public IntegrityGraphException(String message, Graph graph) {
        super(message.trim() + " In graph " + graph.toString());
    }

    public IntegrityGraphException(String message) {
        super(message);
    }

    public IntegrityGraphException(Throwable cause) {
        super(cause);
    }

    public IntegrityGraphException(Graph graph, Throwable cause) {
        super("Integrity exception in graph " + graph.toString(), cause);
    }

    public IntegrityGraphException(String message, Throwable cause) {
        super(message, cause);
    }

    public IntegrityGraphException(String message, Throwable cause, boolean enableSuppression, boolean writableStackTrace) {
        super(message, cause, enableSuppression, writableStackTrace);
    }
}
