package com.example.armando.agenda;

import android.app.Activity;
import android.os.Bundle;
import android.widget.ImageView;
import android.widget.Toast;

public class DoSomething extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
        Bundle extras = getIntent().getExtras();
        String userName;
        //String P1 = savedInstanceState.getString("P1");

        if (extras!=null)
        {
            Integer I1 = extras.getInt("I1");
            String P1 = extras.getString("P1");
            Toast.makeText(getApplicationContext(),
                    "Mensanje Recibido: "+
                    "\n"+P1,
                    Toast.LENGTH_LONG).show();

        }
        else {
            Toast.makeText(getApplicationContext(),
                    "NO HAGAS NI MADRES ",
                    Toast.LENGTH_LONG).show();
        }

		ImageView image = new ImageView(this);
		image.setImageDrawable(getResources().getDrawable(R.mipmap.ic_launcher));
		setContentView(image);
	}

}
