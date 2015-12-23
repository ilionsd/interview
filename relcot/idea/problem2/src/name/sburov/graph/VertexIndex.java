package name.sburov.graph;

import name.sburov.util.BooleanUtils;

import java.util.Objects;

/**
 * Created by ilion on 22.12.2015.
 */
public class VertexIndex extends Number{
    public static final int UNDEFINED_INDEX_VALUE = Integer.MIN_VALUE;
    public static final VertexIndex UNDEFINED_INDEX = new VertexIndex(UNDEFINED_INDEX_VALUE);

    private int index;

    public static boolean checkIndex(int index) {
        if (index < 0)
            return false;
        return true;
    }

    public VertexIndex newInstance(int index) {
        if (!checkIndex(index))
            throw new IllegalArgumentException("Require non negative index, given " + index);
        return new VertexIndex(index);
    }

    private VertexIndex(int index) {
        this.index = index;
    }

    @Override
    public boolean equals(Object other) {
        if (other instanceof VertexIndex)
            return compareTo((VertexIndex) other) == 0;
        if (other instanceof Integer)
            return compareTo((int)other) == 0;
        return false;
    }

    public int compareTo(VertexIndex other) {
        return Integer.compare(index, other.index);
    }

    public int compareTo(int other) {
        return Integer.compare(index, other);
    }

    public static int compare(VertexIndex o1, VertexIndex o2) {
        return Integer.compare(o1.index, o2.index);
    }

    @Override
    public String toString() {
        return Integer.toString(index);
    }

    @Override
    public int hashCode() {
        return Integer.hashCode(index);
    }

    @Override
    public int intValue() {
        return index;
    }

    @Override
    public long longValue() {
        return (long)index;
    }

    @Override
    public float floatValue() {
        return (float)index;
    }

    @Override
    public double doubleValue() {
        return (double)index;
    }
}
