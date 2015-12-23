package name.sburov.util;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;
import java.util.function.Function;
import java.util.stream.Collector;
import java.util.stream.Collectors;

/**
 * Created by ilion on 22.12.2015.
 */
public class MapUtils {
    public MapUtils() {}

    public static <K, V> Map<K, V> createMap(Set<? extends K> keySet, V initValue) {
        Map<K, V> map = keySet.stream().collect(Collectors.toMap(Function.identity(), key -> initValue));
        return map;
    }

    public static <K, V> Map<K, V> createMap(Set<? extends K> keySet, Function<K, V> valueMapper) {
        Map<K, V> map = keySet.stream().collect(Collectors.toMap(Function.identity(), valueMapper));
        return map;
    }
}
