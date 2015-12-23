package name.sburov.graph.algorithms.search;

import name.sburov.graph.VertexIndex;

import java.util.HashMap;
import java.util.Map;

/**
 * Created by ilion on 16.12.2015.
 */
public class SearchResult implements Cloneable {
    protected VertexIndex source = VertexIndex.UNDEFINED_INDEX;
    protected Map<VertexIndex, CostEntry> route = null;

    public VertexIndex getSource() {
        return source;
    }

    public Map<VertexIndex, CostEntry> getRoute() {
        return route;
    }

    @Override
    public Object clone() {
        SearchResult clone = null;
        try {
            clone = (SearchResult) super.clone();
            clone.route = new HashMap<>(route);
        }
        catch (CloneNotSupportedException e) {
            e.printStackTrace();
        }
        return clone;
    }

    public static SearchResult.Builder newBuilder() {
        return (new SearchResult()).new Builder();
    }

    public class Builder {
        public Builder() { }

        public SearchResult build() {
            return (SearchResult) SearchResult.this.clone();
        }

        public Builder setSource(VertexIndex source) {
            SearchResult.this.source = source;
            return this;
        }

        public Builder setRoute(Map<VertexIndex, CostEntry> route) {
            SearchResult.this.route = route;
            return this;
        }
    }
}
