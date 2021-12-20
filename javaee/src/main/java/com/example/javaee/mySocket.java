package com.example.javaee;

import javax.json.Json;
import javax.json.JsonArray;
import javax.json.JsonObject;
import javax.json.JsonObjectBuilder;
import javax.websocket.OnClose;
import javax.websocket.OnMessage;
import javax.websocket.OnOpen;
import javax.websocket.Session;
import javax.websocket.server.ServerEndpoint;
import javax.ws.rs.Consumes;
import javax.ws.rs.Produces;
import java.io.IOException;
import java.net.Socket;
import org.json.*;
@ServerEndpoint("/socketLed")
public class mySocket {
    public static Session session;

    @OnOpen
    public void connect(Session session)
    {
        mySocket.session = session;
        System.out.println( "ESP32:Connexion Reussi!");
    }

    @OnClose
    public void close()
    {
        mySocket.session = null;
        System.out.println("ESP32:Deconnexion");
    }

    @OnMessage
    public void message(String message, Session session) {
        JSONObject receive = new JSONObject(message);
        System.out.println(receive.get("led"));
        JSONObject obj = new JSONObject();
        obj.put("etat", Led.getInstance().etat);
        String messageRetour = obj.toString();
        try {
            session.getBasicRemote().sendText(messageRetour);
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

}
