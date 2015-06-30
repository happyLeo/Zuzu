public class Point {
    private float X,Y;

    public Point(float x, float y) {
        this.X = x;
        this.Y = y;
    }
    public Point(Point other) throws NullPointerException{
        if(other == null) {
            throw new NullPointerException();
        }
        this.X = other.getX();
        this.Y = other.getY();
    }

    public float getX() { return this.X;}
    public float getY() { return this.Y; }

    public String toString() {
        return "("+Float.toString(this.X)+","+Float.toString(this.Y)+")";
    }
}
