package include;

import container.ServiceContainer.State;

public interface Container {

    void addObserver(Observer observer);

    int getValveOpening();

    void setValveOpening(int valveOpening);

    String getState();

    void setState(State state);

    int getFreq();

    void setFreq(int freq);

    void updateState(float waterLevel);

    void notifyAllObserver();

    float getWaterLevel();
    
    void setManualMode(boolean manual);
    
}
