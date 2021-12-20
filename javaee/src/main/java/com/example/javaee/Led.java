package com.example.javaee;

public class Led {

    private static Led ledinstance;
    public boolean etat;

    private Led()
    {
        etat = false;
    }

    public static Led getInstance()
    {
        if(ledinstance == null)
        {
            ledinstance = new Led();
        }
        return ledinstance;
    }



}
