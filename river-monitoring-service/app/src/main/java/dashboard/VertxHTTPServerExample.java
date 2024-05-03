package dashboard;


import java.util.Random;

import container.ServiceContainer;
import include.Observer;
import io.vertx.core.*;
import io.vertx.core.json.JsonObject;
import io.vertx.ext.web.Router;
import io.vertx.ext.web.handler.BodyHandler;
import io.vertx.ext.web.handler.CorsHandler;

public class VertxHTTPServerExample extends AbstractVerticle implements Observer {

	private ServiceContainer service;
	private Router router;

	public VertxHTTPServerExample(ServiceContainer service) {
		this.service = service;
	}

	@Override
	public void start() throws Exception {
		// Create a Router
		this.router = Router.router(vertx);

		// Imposta il BodyHandler per tutte le route
		router.route().handler(BodyHandler.create());

		// Setup CORS
		router.route().handler(CorsHandler.create("*")
				.allowedMethod(io.vertx.core.http.HttpMethod.GET)
				.allowedMethod(io.vertx.core.http.HttpMethod.POST)
				.allowedMethod(io.vertx.core.http.HttpMethod.OPTIONS)
				.allowedHeader("Access-Control-Allow-Origin")
				.allowedHeader("Content-Type"));

		// Mount the handler for all incoming requests at every path and HTTP method
		// router.get().handler(context -> {
		// 	Random random = new Random();
		// 	context.json(
		// 			new JsonObject().put("Sonar", random.nextInt(0, 200)).put("Valve", 180).put("State", "Tutto bene"));
		// });

		router.post().handler(context -> {
			JsonObject body = context.getBodyAsJson(); // Verifica se il corpo è null
			if (body != null) {
				String value = body.getString("value"); // Verifica se "value" è correttamente estratto
				System.out.println("Valore ricevuto: " + value);
			} else {
				System.out.println("Corpo della richiesta non disponibile o non è JSON valido.");
			}
			context.response()
					.putHeader("Content-Type", "application/json")
					.end(new JsonObject().put("status", "success").encode());
		});

		// Create the HTTP server
		vertx.createHttpServer()
				// Handle every request using the router
				.requestHandler(router)
				// Start listening
				.listen(8080)
				// Print the port
				.onSuccess(server -> System.out.println("HTTP server started on port " + server.actualPort()));
	}

	private void sendData(){
		this.router.get().handler(context -> {
			Random random = new Random();
			context.json(
					new JsonObject().put("Sonar", random.nextInt(0, 200)).put("Valve", 180).put("State", "Tutto bene"));
		});
	}

	@Override
	public void update() {
		this.sendData();
	}

	// public static void main(String[] args) {
	// 	Vertx vertx = Vertx.vertx();
	// 	VertxHTTPServerExample service = new VertxHTTPServerExample();
	// 	vertx.deployVerticle(service);

	// }

}