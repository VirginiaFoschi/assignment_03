package arduino;

import include.Observer;

/**
 * Simple interface for an async msg communication channel
 * @author aricci
 *
 */
public interface CommChannel extends Observer{
	
	/**
	 * Send a message represented by a string (without new line).
	 * 
	 * Asynchronous model.
	 * 
	 * @param msg
	 */
	void sendMsg(String msg);
	
	/**
	 * To receive a message. 
	 * 
	 * Blocking behaviour.
	 */
	String receiveMsg() throws InterruptedException;

	/**
	 * To check if a message is available.
	 * 
	 * @return
	 */
	boolean isMsgAvailable();

}
