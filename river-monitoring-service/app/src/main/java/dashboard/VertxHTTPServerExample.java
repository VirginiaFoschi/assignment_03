package dashboard;


import java.util.Random;

import com.google.errorprone.annotations.OverridingMethodsMustInvokeSuper;

import container.ServiceContainer;
import include.Observer;
import io.vertx.core.*;
import io.vertx.core.json.JsonObject;
import io.vertx.ext.web.Router;
import io.vertx.ext.web.handler.BodyHandler;
import io.vertx.ext.web.handler.CorsHandler;

/**
 * 
 * @author aricci
 *
 */

public class VertxHTTPServerExample extends AbstractVerticle implements Observer {

	private ServiceContainer service;
	private Router router;
	private String stop = "Stop";
	//
	private int priority;

	public VertxHTTPServerExample(ServiceContainer service, int priority) {
		this.service = service;
		this.priority = priority;
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


		router.post().handler(context -> {
			JsonObject body = context.getBodyAsJson(); // Verifica se il corpo è null
			if (body != null) {
				String value = body.getString("value"); // Verifica se "value" è correttamente estratto
				System.out.println("Valore ricevuto: " + value);
				if(value.contains(stop)) {
					//this.service.setManualMode(false);
					this.service.releaseLock();
				}
				else {
					//this.service.setManualMode(true);
					this.service.setValveOpening(Integer.parseInt(value), this.priority);
				}
				
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
			context.json(
					new JsonObject().put("Sonar", this.service.getWaterLevel()).put("Valve", this.service.getValveOpening()).put("State", this.service.getState()).put("canSend", this.priority>=this.service.getPriority()));
		});
	}

	@Override
	public void update() {
		this.sendData();
	}

	@Override 
	public int getPriority() {
		return this.priority;
	}

}