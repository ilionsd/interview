package name.sburov.util;

/**
 * Created by ilion on 22.12.2015.
 */
public class BooleanUtils {
    public BooleanUtils() {}

    public static boolean xor(boolean a, boolean b) {
        return (!a || !b) && (a || b);
    }
}
