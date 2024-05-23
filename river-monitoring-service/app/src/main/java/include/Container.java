package include;

import container.ServiceContainer.State;

public interface Container {

    void addObserver(Observer observer);

    int getValveOpening();

    void setValveOpening(int valveOpening, int priority);

    String getState();

    void setState(State state);

    int getFreq();

    void setFreq(int freq);

    void updateState(float waterLevel, int priority);

    void notifyAllObserver();

    float getWaterLevel();
    
    //void setManualMode(boolean manual);

    void releaseLock();

    int getPriority();
    
}
