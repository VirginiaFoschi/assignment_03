import arduino.CommChannel;
import arduino.SerialCommChannel;
import dashboard.VertxHTTPServerExample;
import io.vertx.core.Vertx;

public class App {

	public static void main(String[] args) throws Exception{
        ServiceContainer serviceContainer = new ServiceContainer();
		CommChannel channel=null;
		try {
            channel = new SerialCommChannel("COM4",9600);
        } catch (Exception e) {
            e.printStackTrace();
        }
        

        Vertx vertx = Vertx.vertx();
		VertxHTTPServerExample service = new VertxHTTPServerExample();
		vertx.deployVerticle(service);

	}

}
