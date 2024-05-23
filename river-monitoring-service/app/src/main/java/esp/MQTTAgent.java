package esp;

import io.netty.handler.codec.mqtt.MqttQoS;
import io.vertx.core.AbstractVerticle;
import io.vertx.core.Vertx;
import io.vertx.core.buffer.Buffer;
import io.vertx.core.http.HttpServerResponse;
import io.vertx.core.json.JsonArray;
import io.vertx.core.json.JsonObject;
import io.vertx.ext.web.Router;
import io.vertx.ext.web.RoutingContext;
import io.vertx.ext.web.handler.BodyHandler;
import io.vertx.mqtt.MqttClient;

import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Map;

import container.ServiceContainer;

/**
 * MQTT Agent
 * @author aricci
 *
 */
public class MQTTAgent extends AbstractVerticle {
	
	private static final String BROKER_ADDRESS = "broker.mqtt-dashboard.com"; //we can create topic over there
	private static final String TOPIC_NAME = "esiot-2023Sonar";
	private static final String TOPIC_NAMEFREQ = "esiot-2023Freq";
	private MqttClient client;  // MqttClient è ora un attributo della classe
	private ServiceContainer service;

	//
	private int priority;

	public MQTTAgent(ServiceContainer service, int priority) {
		this.service = service;
		this.priority = priority;
	}

	@Override
	public void start() {		
		client = MqttClient.create(vertx);
		client.connect(1883, BROKER_ADDRESS, c -> {	//collegami al broker
			log("connected");
			
			log("subscribing...");
			client.publishHandler(s -> {
			  String waterLevel = s.payload().toString();
			  this.service.updateState(Float.parseFloat(waterLevel), this.priority);
			  // Pubblica un messaggio sul topic TOPIC_NAMEFREQ ogni volta che un messaggio è ricevuto
			   publishToFrequencyTopic(Integer.toString(this.service.getFreq()));
			})
			.subscribe(TOPIC_NAME, 2);		

		});
	}

	private void publishToFrequencyTopic(String message) {
        if (client.isConnected()) {
            client.publish(TOPIC_NAMEFREQ,
                Buffer.buffer(message),
                MqttQoS.AT_LEAST_ONCE,
                false,
                false
			);
        } else {
            log("Client is not connected, cannot publish message");
        }
    }
	

	private void log(String msg) {
		System.out.println("[MQTT AGENT] "+msg);
	}

}