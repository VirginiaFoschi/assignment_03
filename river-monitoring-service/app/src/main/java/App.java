/**
 * Balzoni Margherita
 * Castiglioni Chiara
 * Foschi Virginia
*/

import arduino.CommChannel;
import arduino.SerialCommChannel;
import container.ServiceContainer;
import dashboard.VertxHTTPServerExample;
import esp.MQTTAgent;
import io.vertx.core.Vertx;

public class App {

	private static final int MAX_PRIORITY=10;
	private static final int INTERMEDIATE_PRIORITY=5;
	private static final int MIN_PRIORITY = 2;

	public static void main(String[] args) throws Exception{
        ServiceContainer serviceContainer = new ServiceContainer();
		CommChannel channel=null;
		try {
            channel = new SerialCommChannel(serviceContainer,"COM4",9600, MAX_PRIORITY);
			serviceContainer.addObserver(channel);
        } catch (Exception e) {
            e.printStackTrace();
        }

		/*dashBoard */
        Vertx vertx = Vertx.vertx();
		VertxHTTPServerExample service = new VertxHTTPServerExample(serviceContainer,INTERMEDIATE_PRIORITY);
		vertx.deployVerticle(service);
		serviceContainer.addObserver(service);

		/*Esp */
        Vertx vertx2 = Vertx.vertx(); /** vrtex make possibile to create reactive components: like threads but based on an event-loop-> when there's an event executes the handler */
		MQTTAgent agent = new MQTTAgent(serviceContainer,MIN_PRIORITY);
		vertx2.deployVerticle(agent);

		while (true){
			if(channel.isMsgAvailable()) {
				String msg = channel.receiveMsg();
				System.out.println(msg);
				if(Integer.parseInt(msg) < 0) {
					if(serviceContainer.getPriority()==MAX_PRIORITY){
						serviceContainer.releaseLock();
					}
				} else {
					serviceContainer.setValveOpening(Integer.parseInt(msg), MAX_PRIORITY);
				}
			}
		}

	}

}
