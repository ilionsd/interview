package name.sburov.graph.algorithms.search;

import name.sburov.graph.VertexIndex;

/**
 * Created by ilion on 22.12.2015.
 */
public class CostEntry implements Comparable<Double> {

    public static final double SOURCE_COST = 0.0;
    public static final double UNREACHEBLE_COST = Double.POSITIVE_INFINITY;

    protected double cost;
    protected VertexIndex source;

    public static CostEntry Source() {
        return new CostEntry(CostEntry.SOURCE_COST, VertexIndex.UNDEFINED_INDEX);
    }

    public static CostEntry Unreachable() {
        return new CostEntry(UNREACHEBLE_COST, VertexIndex.UNDEFINED_INDEX);
    }

    public CostEntry(double cost, VertexIndex source) {
        this.cost = cost;
        this.source = source;
    }

    public boolean isUnreacheble() {
        return Double.compare(cost, UNREACHEBLE_COST) == 0 && VertexIndex.compare(source, VertexIndex.UNDEFINED_INDEX) == 0;
    }

    public boolean isSource() {
        return Double.compare(cost, SOURCE_COST) == 0 && VertexIndex.compare(source, VertexIndex.UNDEFINED_INDEX) == 0;
    }

    public double getCost() {
        return cost;
    }

    public VertexIndex getSource() {
        return source;
    }

    @Override
    public int compareTo(Double o) {
        return Double.compare(cost, o);
    }
}
