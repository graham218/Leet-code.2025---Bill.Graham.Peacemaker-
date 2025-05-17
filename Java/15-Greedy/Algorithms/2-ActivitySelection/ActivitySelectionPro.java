// Class to represent an activity
class Activity {
    int start, finish;
    String name; // Added name for better identification

    public Activity(int start, int finish, String name) {
        this.start = start;
        this.finish = finish;
        this.name = name;
    }

    // Override toString() method for easy printing of Activity objects
    @Override
    public String toString() {
        return "Activity{" +
                "name='" + name + '\'' +
                ", start=" + start +
                ", finish=" + finish +
                '}';
    }
}