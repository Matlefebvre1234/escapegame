package com.example.javaee;

import javax.json.JsonObject;
import javax.websocket.Session;
import javax.ws.rs.*;
import javax.ws.rs.core.Response;
import com.example.javaee.HelloApplication;
import org.json.JSONObject;

import java.io.IOException;

@Path("/api")
public class API {



    @GET
    @Path("getEtatLed")
    @Produces("text/plain")
    public boolean getEtatLed() {
        Led led = Led.getInstance();
        return led.etat;
    }

    @POST
    @Consumes("application/json")
    @Path("setEtatLed")
    public String getEtatled(JsonObject object) {
        Led led = Led.getInstance();
        System.out.println(object.get("etat"));
        led.etat = Boolean.parseBoolean( object.get("etat").toString());
        JSONObject obj = new JSONObject();
        obj.put("etat", Led.getInstance().etat);
        String messageRetour = obj.toString();
        try {
            if(mySocket.session != null)
            {
                mySocket.session.getBasicRemote().sendText(messageRetour);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return "Les led sont a " + led.etat;


    }


    @POST
    @Path("login")
    @Consumes("application/json")
    @Produces("text/plain")
    public String login(JsonObject json) {
        JSONObject obj = new JSONObject();

        System.out.println(json.getString("username"));
        System.out.println(json.getString("password"));
        if(json.getString("username").equals("TerreurDeLOcean") && json.getString("password").equals("BakyJujube"))
        {
            obj.put("login", true);
        }
        else {
            obj.put("login", false);
        }


        String messageRetour = obj.toString();
        return messageRetour;
    }





}

