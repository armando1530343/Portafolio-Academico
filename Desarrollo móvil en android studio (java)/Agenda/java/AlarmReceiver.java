package com.example.armando.agenda;

import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.support.v4.app.NotificationCompat;
import android.widget.Toast;

import java.util.Random;

public class AlarmReceiver extends BroadcastReceiver {
	
	private static final int MY_NOTIFICATION_ID=1;
	NotificationManager notificationManager;
	Notification myNotification;

	@Override
	public void onReceive(Context context, Intent intent) {

        Integer I1= intent.getExtras().getInt("R");
        String C1= intent.getExtras().getString("E1");
		//Toast.makeText(context, "Alarm received!"+C1+C2+C3, Toast.LENGTH_LONG).show();

	    Intent myIntent = new Intent(context, DoSomething.class);
        //intent.setFlags(Intent.FLAG_ACTIVITY_PREVIOUS_IS_TOP); // NO ESTABA EN EL ORIGINAL
        //intent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP | Intent.FLAG_ACTIVITY_NEW_TASK);
        myIntent.putExtra("I1",I1);
        myIntent.putExtra("P1",C1);
	    PendingIntent pendingIntent = PendingIntent.getActivity(
	    	      context, 
	    	      I1,
	    	      myIntent,
                //PendingIntent.FLAG_CANCEL_CURRENT);
                  PendingIntent.FLAG_UPDATE_CURRENT);
                  //PendingIntent.FLAG_ONE_SHOT);
	    	      //Intent.FLAG_ACTIVITY_NEW_TASK); // ORIGINAL
	    
	    myNotification = new NotificationCompat.Builder(context)
	    		.setContentTitle("Evento Pendiente!")
	    		.setContentText(C1)
	    		.setTicker("Notification!")
	    		.setWhen(System.currentTimeMillis())
	    		.setContentIntent(pendingIntent)
	    		.setDefaults(Notification.DEFAULT_SOUND)
	    		.setAutoCancel(true)
	    		.setSmallIcon(R.mipmap.ic_launcher)
	    		.build();
	    
	    notificationManager = 
	    		(NotificationManager)context.getSystemService(Context.NOTIFICATION_SERVICE);
	    //notificationManager.notify(MY_NOTIFICATION_ID, myNotification);
        notificationManager.notify(I1, myNotification);
	}
}
