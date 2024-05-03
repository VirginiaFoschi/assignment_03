public class ServiceContainer {

    public enum State {
        NORMAL("Normal"),
        PRE_ALARM_TOO_HIGH("Pre alarm too high"),
        ALARM_TOO_HIGH("Alarm too high"),
        ALARM_TOO_HIGH_CRITIC("Alarm too high critic"),
        TOO_LOW("Too low");

        private final String description;

        State(String description) {
            this.description = description;
        }

        @Override
        public String toString() {
            return description;
        }
    }

    private static final int F1 = 3000;
    private static final int F2 = 2000;
    private static final int WL1 = 3000; // da modificare valori di wl (tutti)
    private static final int WL2 = 2000;
    private static final int WL3 = 3000;
    private static final int WL4 = 2000;

    private State state = State.NORMAL;
    private int freq = F1;
    private int valveOpening = 25;

    public int getValveOpening() {
        return valveOpening;
    }

    public void setValveOpening(int valveOpening) {
        this.valveOpening = valveOpening;
    }

    public String getState() {
        return state.toString();
    }

    public void setState(State state) {
        this.state = state;
    }

    public int getFreq() {
        return freq;
    }

    public void setFreq(int freq) {
        this.freq = freq;
    }

    public void updateState(int waterLevel) {
        if (waterLevel < WL1) {
            this.freq = F1;
            this.state = State.TOO_LOW;
            this.valveOpening = 0;
        } else if (waterLevel >= WL1 && waterLevel <= WL2) {
            this.freq = F1;
            this.state = State.NORMAL;
            this.valveOpening = 25;
        } else {
            if (waterLevel > WL2 && waterLevel <= WL3) {
                this.freq = F2;
                this.state = State.PRE_ALARM_TOO_HIGH;
            } else if (waterLevel > WL3 && waterLevel <= WL4) {
                this.freq = F2;
                this.state = State.ALARM_TOO_HIGH;
                this.valveOpening = 50;
            } else {
                this.freq = F2;
                this.state = State.ALARM_TOO_HIGH_CRITIC;
                this.valveOpening = 100;
            }
        }
    }

}
