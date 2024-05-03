import arduino.CommChannel;
import arduino.SerialCommChannel;
import container.ServiceContainer;
import dashboard.VertxHTTPServerExample;
import esp.MQTTAgent;
import io.vertx.core.Vertx;

public class App {

	public static void main(String[] args) throws Exception{
        ServiceContainer serviceContainer = new ServiceContainer();
		CommChannel channel=null;
		try {
            channel = new SerialCommChannel(serviceContainer,"COM4",9600);
        } catch (Exception e) {
            e.printStackTrace();
        }
        

        Vertx vertx = Vertx.vertx();
		VertxHTTPServerExample service = new VertxHTTPServerExample(serviceContainer);
		vertx.deployVerticle(service);

        Vertx vertx2 = Vertx.vertx(); /** vrtex make possibile to create reactive components: like threads but based on an event-loop-> when there's an event executes the handler */
		MQTTAgent agent = new MQTTAgent(serviceContainer);
		vertx2.deployVerticle(agent);

	}

}
