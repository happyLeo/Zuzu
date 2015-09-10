import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Parser {

    private static final String POINT_REGEX = "\\((\\d+\\.\\d+).(\\d+\\.\\d+)\\)";
    private Pattern pattern = null;

    public Parser() {
        pattern = Pattern.compile(POINT_REGEX);
    }

    /**
     * Converts a string to a Point instance
     * @param str
     * @return Point instance if input string matches POINT_REGEX. null otherwise
     */
    public Point parsePoint(String str) {
        Matcher m = pattern.matcher(str);

        if(m.matches()) {
            float x = Float.parseFloat(m.group(1));
            float y = Float.parseFloat(m.group(2));
            return new Point(x,y);
        }
        else {
            return null;
        }
    }
}
