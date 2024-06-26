package container;

import java.util.ArrayList;
import java.util.List;

import include.Container;
import include.Observer;

public class ServiceContainer implements Container {

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

    private static final int F1 = 2000;
    private static final int F2 = 1000;
    private static final int WL1 = 9;
    private static final int WL2 = 7;
    private static final int WL3 = 5;
    private static final int WL4 = 4;

    private State state = State.NORMAL;
    private int freq = F1;
    private int valveOpening = 25;
    private List<Observer> observers = new ArrayList<>();
    private float waterLevel = 10;
    //private boolean manualMode = false;
    /* */
    private int priority=1;

    @Override
    public int getValveOpening() {
        return valveOpening;
    }

    @Override
    public void setValveOpening(int valveOpening, int priority) {
        if(priority>=this.priority) {
            this.priority = priority;
            System.out.println("Priority: "+this.priority);
            if(valveOpening!= this.valveOpening){
                this.valveOpening=valveOpening;
                this.observers.get(0).update();
            }
        }
    }

    @Override
    public String getState() {
        return state.toString();
    }

    @Override
    public void setState(State state) {
        this.state = state;
    }

    @Override
    public int getFreq() {
        return freq;
    }

    @Override
    public void setFreq(int freq) {
        this.freq = freq;
    }

    @Override
    public void updateState(float waterLevel, int priority) {
        this.waterLevel = waterLevel;
            if (waterLevel > WL1) {
                this.freq = F1;
                this.state = State.TOO_LOW;
                setValveOpening(0, priority);
            } else if (waterLevel > WL2 && waterLevel <= WL1) {
                this.freq = F1;
                this.state = State.NORMAL;
                setValveOpening(25, priority);
            } else {
                if (waterLevel > WL3 && waterLevel <= WL2) {
                    this.freq = F2;
                    this.state = State.PRE_ALARM_TOO_HIGH;
                    setValveOpening(25, priority);
                } else if (waterLevel > WL4 && waterLevel <= WL3) {
                    this.freq = F2;
                    this.state = State.ALARM_TOO_HIGH;
                    setValveOpening(50, priority);
                } else {
                    this.freq = F2;
                    this.state = State.ALARM_TOO_HIGH_CRITIC;
                    setValveOpening(100, priority);
                }
            }
            this.notifyAllObserver();
        
    }

    @Override
    public void addObserver(Observer observer) {
        this.observers.add(observer);
    }

    @Override
    public void notifyAllObserver() {
        this.observers.subList(1, observers.size()).forEach(el -> el.update());
    }

    @Override
    public float getWaterLevel() {
        return waterLevel;
    }

    public void releaseLock(){
        this.priority=1;
    }

    public int getPriority() {
        return this.priority;
    }

}
